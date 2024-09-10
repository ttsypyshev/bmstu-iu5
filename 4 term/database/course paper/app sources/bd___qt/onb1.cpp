#include "onb1.h"
#include "ui_onb1.h"
#include "menuwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QDebug>
#include "authenticationmanager.h"
#include "databasehelper.h"
#include <QSqlError>
#include <QFile>
#include <QTextStream>


onb1::onb1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::onb1)
{
    ui->setupUi(this);
    connect(ui->btn1, SIGNAL(clicked(bool)), this, SLOT(add()));  // Подключаем кнопку добавления
    connect(ui->btn2, SIGNAL(clicked(bool)), this, SLOT(edit()));  // Подключаем кнопку обновления
    connect(ui->btn3, SIGNAL(clicked(bool)), this, SLOT(remove()));  // Подключаем кнопку удаления
    connect(ui->btn4, SIGNAL(clicked(bool)), this, SLOT(clean()));
    connect(ui->btnSearch, &QPushButton::clicked, this, &onb1::search);
    connect(ui->btnReport, &QPushButton::clicked, this, &onb1::generateReportRequest);
    AuthenticationManager authenticationManager;
    QString currentUser = authenticationManager.getCurrentUserLogin();
    if(currentUser == "bd___user")
    {
        ui->btn1->setVisible(false); // Скрыть кнопку 1
        ui->btn2->setVisible(false);
        ui->btn3->setVisible(false);
    }
    // Вызываем метод selectAll() через таймер с нулевой задержкой, чтобы он выполнился после инициализации интерфейса
    QTimer::singleShot(0, this, &onb1::selectAll);
    // Устанавливаем количество столбцов в компоненте таблицы
    ui->tw->setColumnCount(6);

    // Задаем заголовки столбцов таблицы
    ui->tw->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->tw->setHorizontalHeaderItem(1, new QTableWidgetItem("Название"));
    ui->tw->setHorizontalHeaderItem(2, new QTableWidgetItem("Адресс"));
    ui->tw->setHorizontalHeaderItem(3, new QTableWidgetItem("Телефон"));
    ui->tw->setHorizontalHeaderItem(4, new QTableWidgetItem("Почта"));
    ui->tw->setHorizontalHeaderItem(5, new QTableWidgetItem("Часы работы"));


    // Устанавливаем растягивание последнего столбца при изменении размера формы
    ui->tw->horizontalHeader()->setStretchLastSection(true);

    // Включаем возможность прокрутки содержимого таблицы
    ui->tw->setAutoScroll(true);

    // Устанавливаем режим выделения ячеек: только одна строка
    ui->tw->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Разрешаем пользователю сортировать данные по столбцам
    //ui->tw->setSortingEnabled(true);
    //ui->tw->sortByColumn(0, Qt::AscendingOrder);

    // Запрещаем редактирование ячеек таблицы
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

onb1::~onb1()
{
    delete ui;
}

void onb1::on_btnExit_clicked()
{
    // Создаем объект AuthenticationManager
    AuthenticationManager authenticationManager;

    // Получаем логин текущего пользователя через созданный объект
    QString currentUser = authenticationManager.getCurrentUserLogin();

    // Получаем список разрешенных кнопок для текущего пользователя
    QStringList allowedButtons = authenticationManager.getAllowedButtons(currentUser);

    // Закрываем текущее окно гостей
    close();

    // Создаем и отображаем новое окно главного меню с передачей списка разрешенных кнопок
    menuwindow *menuWindow = new menuwindow(allowedButtons);
    menuWindow->show();
}

void onb1::selectAll()
{
    // Проверяем, открыто ли соединение с базой данных
    if (!DatabaseHelper::isDatabaseConnected())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена.");
        return;
    }

    // Создаем объект запроса с привязкой к установленному соединению с базой данных
    QSqlQuery query(DatabaseHelper::getDatabaseConnection());


    QString sqlstr = "SELECT * FROM offices ORDER BY office_id";

    if (!query.exec(sqlstr))
    {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    // Очищаем таблицу перед обновлением
    ui->tw->clearContents();

    // Подгоняем количество строк таблицы под количество записей в результате запроса
    ui->tw->setRowCount(0); // Очищаем все строки

    int rowCount = 0;

    // Прочитать в цикле все строки результата (курсора)
    while (query.next())
    {
        // Добавляем новую строку в таблицу
        ui->tw->insertRow(rowCount);

        // Устанавливаем идентификатор строки
        QTableWidgetItem *idItem = new QTableWidgetItem(query.value("office_id").toString());
        ui->tw->setItem(rowCount, 0, idItem);

        // Заполняем значениями из базы данных
        ui->tw->setItem(rowCount, 1, new QTableWidgetItem(query.value("name_office").toString()));
        ui->tw->setItem(rowCount, 2, new QTableWidgetItem(query.value("location").toString()));
        ui->tw->setItem(rowCount, 3, new QTableWidgetItem(query.value("phone_number").toString()));
        ui->tw->setItem(rowCount, 4, new QTableWidgetItem(query.value("email").toString()));
        ui->tw->setItem(rowCount, 5, new QTableWidgetItem(query.value("working_hours").toString()));
        // Устанавливаем выравнивание содержимого ячеек по центру
        for (int j = 0; j < ui->tw->columnCount(); ++j)
        {
            ui->tw->item(rowCount, j)->setTextAlignment(Qt::AlignCenter);
        }

        rowCount++;
    }

    // Подгоняем размер столбцов под содержимое
    ui->tw->resizeColumnsToContents();
}

void onb1::add()
{
    // Проверяем, открыто ли соединение с базой данных
    if (!DatabaseHelper::isDatabaseConnected())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена.");
        return;
    }

    QString pu1 = ui->le2->text();
    QString pu2 = ui->le3->text();
    QString pu3 = ui->le4->text();
    QString pu4 = ui->le5->text();
    QString pu5 = ui->le6->text();

    QSqlQuery query;  // Создаем объект запроса

    QString sqlstr = "INSERT INTO offices(name_office, location, phone_number, email, working_hours ) VALUES (?, ?, ?, ?, ?)"; // Формируем строку SQL-запроса для вставки данных в таблицу

    query.prepare(sqlstr); // Подготавливаем запрос к выполнению
    query.bindValue(0, pu1);
    query.bindValue(1, pu2);
    query.bindValue(2, pu3);
    query.bindValue(3, pu4);
    query.bindValue(4, pu5);

    // Выполняем запрос
    if (!query.exec())
    {
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }
    // Если запрос выполнен успешно, выводим сообщение о добавлении строки
    ui->teResult->append(QString("Added %1 rows").arg(query.numRowsAffected()));
    // Обновляем записи в компоненте таблицы
    selectAll();
}

void onb1::on_tw_itemSelectionChanged()
{
    // Получаем выбранную строку
    int curRow = ui->tw->currentRow();

    // Проверяем, что выбранная строка действительно существует
    if (curRow < 0 || curRow >= ui->tw->rowCount()) {
        // Если выбранная строка не существует, сбрасываем значения полей ввода и выходим из функции
        ui->le1->clear();
        ui->le2->clear();
        ui->le3->clear();
        ui->le4->clear();
        ui->le5->clear();
        ui->le6->clear();
        return;
    }
    // Получаем значения из выбранной строки
    QString pu1 = ui->tw->item(curRow, 0) ? ui->tw->item(curRow, 0)->text() : "";
    QString pu2 = ui->tw->item(curRow, 1) ? ui->tw->item(curRow, 1)->text() : "";
    QString pu3 = ui->tw->item(curRow, 2) ? ui->tw->item(curRow, 2)->text() : "";
    QString pu4 = ui->tw->item(curRow, 3) ? ui->tw->item(curRow, 3)->text() : "";
    QString pu5 = ui->tw->item(curRow, 4) ? ui->tw->item(curRow, 4)->text() : "";
    QString pu6 = ui->tw->item(curRow, 5) ? ui->tw->item(curRow, 5)->text() : "";
    // Заполняем поля ввода значениями из выбранной строки
    ui->le1->setText(pu1);
    ui->le2->setText(pu2);
    ui->le3->setText(pu3);
    ui->le4->setText(pu4);
    ui->le5->setText(pu5);
    ui->le6->setText(pu6);
}

void onb1::remove()
{
    // Проверяем, открыто ли соединение с базой данных
    if (!DatabaseHelper::isDatabaseConnected())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена.");
        return;
    }
    // Получаем текущую выбранную строку
    int currow = ui->tw->currentRow();
    // Проверяем, что выбранная строка действительно существует
    if (currow < 0)
    {
        QMessageBox::critical(this, "Ошибка", "Не выбрана строка!");
        return;
    }
    // Просим пользователя подтвердить удаление строки
    if (QMessageBox::question(this, "Удалить", "Удалить строку?", QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Cancel)
        return;
    // Создать объект запроса
    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    QString pu1 = ui->tw->item(currow, 0)->text();
    QString sqlstr = "DELETE FROM offices WHERE office_id = '" + pu1 + "'";
    // Выполняем запрос
    if (!query.exec(sqlstr))
    {
        // Проверяем текст ошибки на наличие фразы "foreign key"
        if (query.lastError().text().contains("foreign key", Qt::CaseInsensitive))
        {
            QMessageBox::critical(this, "Ошибка", "Невозможно удалить, так как есть связанные.");
        }
        else
        {
            // Если запрос не выполнен по другой причине, выводим сообщение об ошибке
            QMessageBox::critical(this, "Ошибка", query.lastError().text());
        }
        return;
    }

    // Выводим сообщение об удалении строки
    ui->teResult->append(QString("Deleted %1 rows").arg(query.numRowsAffected()));

    // Обновляем содержимое компонента таблицы
    selectAll();
}

void onb1::clean()
{
    ui->le1->clear();
    ui->le2->clear();
    ui->le3->clear();
    ui->le4->clear();
    ui->le5->clear();
    ui->le6->clear();
}

void onb1::edit()
{
    // Проверяем, открыто ли соединение с базой данных
    if (!DatabaseHelper::isDatabaseConnected())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена.");
        return;
    }

    // Получаем текущую выбранную строку
    int curRow = ui->tw->currentRow();

    // Проверяем, что выбранная строка действительно существует
    if (curRow < 0)
    {
        QMessageBox::critical(this, "Ошибка", "Строка не выбрана!");
        return;
    }

    // Получаем значения из полей ввода
    QString pu1 = ui->le1->text();
    QString pu2 = ui->le2->text();
    QString pu3 = ui->le3->text();
    QString pu4 = ui->le4->text();
    QString pu5 = ui->le5->text();
    QString pu6 = ui->le6->text();

    // Создаем объект запроса с привязкой к установленному соединению с базой данных
    QSqlQuery query(DatabaseHelper::getDatabaseConnection());

    // Подготавливаем строку запроса для обновления данных в таблице
    QString sqlstr = "UPDATE offices SET name_office = ?, location = ?, phone_number = ?, email= ?, working_hours = ? WHERE office_id = ?";

    query.prepare(sqlstr);
    query.bindValue(0, pu2);
    query.bindValue(1, pu3);
    query.bindValue(2, pu4);
    query.bindValue(3, pu5);
    query.bindValue(4, pu6);
    query.bindValue(5, pu1);
    // Выполняем запрос
    if (!query.exec())
    {
        // Если запрос не выполнен, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }
    // Выводим сообщение об успешном обновлении записи
    ui->teResult->append(QString("Updated %1 rows").arg(query.numRowsAffected()));
    // Обновляем соответствующие ячейки в таблице после успешного выполнения запроса
    ui->tw->item(curRow, 1)->setText(pu2);
    ui->tw->item(curRow, 2)->setText(pu3);
    ui->tw->item(curRow, 3)->setText(pu4);
    ui->tw->item(curRow, 4)->setText(pu5);
    ui->tw->item(curRow, 5)->setText(pu6);

    // Обновляем содержимое таблицы после успешного обновления записи
    selectAll();
}

void onb1::search()
{
    // Получаем текст из поля поиска
    QString currentSearchQuery = ui->leSearch->text().trimmed(); // Обрезаем начальные и конечные пробелы

    // Проверяем, пусто ли поле ввода
    if (currentSearchQuery.isEmpty())
    {
        // Если поле ввода пустое, вызываем функцию selectAll для выделения всех строк
        selectAll();
        return; // Завершаем выполнение функции
    }
    // Проверяем, изменилось ли значение поиска с предыдущего запроса
    if (currentSearchQuery != m_lastSearchQuery)
    {
        // Если значение изменилось, обновляем переменную с последним значением поиска
        m_lastSearchQuery = currentSearchQuery;
        // Сбрасываем индекс последнего найденного совпадения
        m_lastFoundIndex = -1;
    }

    // Очищаем выделение в таблице
    ui->tw->clearSelection();
    // Флаг для отслеживания найденных результатов
    bool foundMatch = false;
    // Проходим по всем строкам таблицы и ищем нужную строку
    for (int row = m_lastFoundIndex + 1; row < ui->tw->rowCount(); ++row)
    {
        // Получаем текст в каждой ячейке строки таблицы
        QString rowData;
        for (int col = 0; col < ui->tw->columnCount(); ++col)
        {
            QTableWidgetItem *item = ui->tw->item(row, col);
            if (item)
                rowData += item->text() + " ";
        }

        // Проверяем, содержит ли текст строки искомую подстроку
        if (rowData.contains(currentSearchQuery, Qt::CaseInsensitive))
        {
            // Выделяем найденную строку
            ui->tw->selectRow(row);

            // Прокручиваем таблицу к найденной строке
            ui->tw->scrollToItem(ui->tw->item(row, 0));

            // Устанавливаем флаг найденного элемента в true
            foundMatch = true;

            // Обновляем индекс последнего найденного совпадения
            m_lastFoundIndex = row;

            // Выходим из цикла, так как строка найдена
            break;
        }
    }

    // Если совпадение не было найдено, выводим сообщение об этом
    if (!foundMatch)
    {
        QMessageBox::information(this, "Поиск", "Больше совпадений не найдено.");
        // Сбрасываем индекс последнего найденного совпадения
        m_lastFoundIndex = -1;
    }
}

void onb1::generateReportRequest() {
    // Вызываем функцию selectAll для получения данных о гостях из таблицы
    selectAll();

    QString reportText = "Запрос на формирование отчета - об офисах:\n\n";
    reportText += "Уважаемые коллеги,\n\n";
    reportText += "Подготовлен отчет об офисах нашей компании:\n";

    // Добавляем информацию
    for (int row = 0; row < ui->tw->rowCount(); ++row) {
        QString pu1 = ui->tw->item(row, 1)->text();
        reportText +=  "Название офиса" + pu1 + ";\n";
    }

    reportText += "\nС уважением,\n";
    reportText += "Управляющий отдела";

    QString fileName = "offices_report_request.txt"; // Имя файла для сохранения отчета

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << reportText;
        file.close();
        QMessageBox::information(this, "Успех", "Запрос на формирование отчета успешно сохранен в файле " + fileName);
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать файл для сохранения отчета.");
    }
}


