#include "onb7.h"
#include "ui_onb7.h"
#include "menuwindow.h"
#include "databasehelper.h"
#include "authenticationmanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QFile>


onb7::onb7(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::onb7)
{
    ui->setupUi(this);

    connect(ui->btn1, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btn2, SIGNAL(clicked(bool)), this, SLOT(remove()));
    connect(ui->btnSearch, &QPushButton::clicked, this, &onb7::search);


    AuthenticationManager authenticationManager;
    QString currentUser = authenticationManager.getCurrentUserLogin();
    if(currentUser == "bd_user")
    {
        ui->btn1->setVisible(false); // Скрыть кнопку 1
        ui->btn2->setVisible(false);
    }

    // Вызываем метод selectAll() через таймер с нулевой задержкой
    QTimer::singleShot(0, this, SLOT(selectAll()));

    // Устанавливаем количество столбцов в таблице
    ui->tw->setColumnCount(6); // Измените на количество столбцов в вашей таблице

    // Задаем заголовки столбцов таблицы
    ui->tw->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->tw->setHorizontalHeaderItem(1, new QTableWidgetItem("Офис"));
    ui->tw->setHorizontalHeaderItem(2, new QTableWidgetItem("Серфисный центр"));
    ui->tw->setHorizontalHeaderItem(3, new QTableWidgetItem("Дата заказа"));
    ui->tw->setHorizontalHeaderItem(4, new QTableWidgetItem("Дата отправки"));
    ui->tw->setHorizontalHeaderItem(5, new QTableWidgetItem("Стоимость"));


    // Добавьте заголовки для остальных столбцов, если они есть

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

    // Populate combo boxes
    populate1ComboBox();
    populate2ComboBox();


}

onb7::~onb7()
{
    delete ui;
}

void onb7::selectAll()
{

    if (!DatabaseHelper::isDatabaseConnected())
    {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена.");
        return;
    }

    ui->tw->clearContents();

    QString sqlstr = "SELECT ord.Order_ID, o.Name_Office , s.Location , ord.Order_Date, ord.Ship_Date, ord.Total_Amount "
                     "FROM  Orders ord "
                     "JOIN Offices o ON ord.Office_ID = o.Office_ID "
                     "JOIN Service_Centers s ON ord.ServiceCenter_ID = s.ServiceCenter_ID";

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    if (!query.exec(sqlstr))
    {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    ui->tw->setRowCount(query.size());

    int row = 0;
    while (query.next())
    {
        QString id = query.value("Order_ID").toString();
        QString Discipline = query.value("Name_Office").toString();

        QString coachName = query.value("Location").toString();
        QString groupName = query.value("Order_Date").toString();
        QString dateOfLesson = query.value("Ship_Date").toString();
        QString Duration = query.value("Total_Amount" ).toString();

        QTableWidgetItem *idItem = new QTableWidgetItem(id);
        QTableWidgetItem *DisciplineItem = new QTableWidgetItem(Discipline);

        QTableWidgetItem *coachItem = new QTableWidgetItem(coachName);
        QTableWidgetItem *groupItem = new QTableWidgetItem(groupName);
        QTableWidgetItem *dateItem = new QTableWidgetItem(dateOfLesson);
        QTableWidgetItem *DurationItem = new QTableWidgetItem(Duration);

        ui->tw->setItem(row, 0, idItem);
        ui->tw->setItem(row, 1, DisciplineItem);

        ui->tw->setItem(row, 2, coachItem);
        ui->tw->setItem(row, 3, groupItem);
        ui->tw->setItem(row, 4, dateItem);
        ui->tw->setItem(row, 5, DurationItem);


        ++row;
    }

    ui->tw->resizeColumnsToContents();
}

void onb7::add()
{
    QString cmb1 = ui->cmb1->currentText();
    QString cmb2 = ui->cmb2->currentText();

    QString pu1 = ui->le2->text();
    QString pu2 = ui->le3->text();
    QString pu3 = ui->le4->text();
    // Подготавливаем SQL запрос для вставки данных
    QSqlQuery query;
    query.prepare ("INSERT INTO orders (Office_ID, ServiceCenter_ID, Order_Date, Ship_Date, Total_Amount) "
                  "VALUES ((SELECT Office_ID FROM Offices WHERE Name_Office = :1 LIMIT 1), (SELECT ServiceCenter_ID FROM Service_Centers WHERE Location = :2 LIMIT 1), :3, :4, :5)");

//(SELECT Client_ID FROM Clients WHERE First_Name = :3 LIMIT 1 ),


    // Привязываем значения к параметрам запроса
    query.bindValue(":1", cmb1);
    query.bindValue(":2", cmb2);

    query.bindValue(":3", pu1);
    query.bindValue(":4", pu2);
    query.bindValue(":5", pu3);

    // Выполняем SQL запрос для вставки данных
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        ui->teResult->append("Error: " + query.lastError().text());
        return;
    }

    qDebug() << "Данные успешно добавлены в базу данных.";

    ui->teResult->append("Успех: данные успешно добавлены.");
    selectAll(); // Обновить таблицу, чтобы отобразить новые данные
}

void onb7::remove()
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
        QMessageBox::critical(this, "Ошибка", "Не выбрана строка!");
        return;
    }

    // Просим пользователя подтвердить удаление строки
    if (QMessageBox::question(this, "Удалить", "Удалить строку?", QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Cancel)
        return;

    // Создать объект запроса
    QSqlQuery query(DatabaseHelper::getDatabaseConnection());

    QString pu1 = ui->tw->item(curRow, 0)->text();

    query.prepare("DELETE FROM orders WHERE order_id = :pupu");
    query.bindValue(":pupu", pu1);

    // Выполняем запрос
    if (!query.exec())
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка выполнения запроса DELETE");
        return;
    }

    // Выводим сообщение об удалении строки
    ui->teResult->append(QString("Deleted %1 rows").arg(query.numRowsAffected()));

    // Обновляем содержимое компонента таблицы
    selectAll();
}

void onb7::populate1ComboBox()
{
    ui->cmb1->clear();
    QSqlQuery query("SELECT Office_ID, Name_Office FROM Offices ORDER BY Office_ID");
    while (query.next()) {
        QString pu1 = query.value("Office_ID").toString();
        QString pu2 = query.value("Name_Office").toString();
        ui->cmb1->addItem(pu2, pu1);
    }
}

void onb7::populate2ComboBox()
{
    ui->cmb2->clear();
    QSqlQuery query("SELECT ServiceCenter_ID, Location FROM Service_Centers ORDER BY ServiceCenter_ID");
    while (query.next()) {
        QString pu1 = query.value("ServiceCenter_ID").toString();
        QString pu2 = query.value("Location").toString();
        ui->cmb2->addItem(pu2, pu1);
    }
}

void onb7::on_btnExit_clicked()
{

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

void onb7::search()
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



