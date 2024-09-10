#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "databasehelper.h"
#include "registrationwindow.h"
#include "onb1.h"
#include "onb2.h"
#include "onb3.h"
#include "onb5.h"
#include "onb7.h"
#include <QMessageBox>
#include <QVBoxLayout>

menuwindow::menuwindow(const QStringList &allowedButtons, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuwindow)
{
    ui->setupUi(this); // Подключение формы

    QVBoxLayout *layout = new QVBoxLayout(this); // Создание layout
    layout->setContentsMargins(20, 20, 20, 20); // Установка отступов
    layout->setSpacing(15); // Установка расстояния между элементами

    // Добавляем кнопки в меню
    for (const QString &buttonText : allowedButtons) {
        QPushButton *button = new QPushButton(buttonText, this);
        button->setStyleSheet("QPushButton {"
                              "    background-color: #A5A5A5;" // Зеленый цвет фона
                              "    color: white;" // Белый цвет текста
                              "    border-radius: 10px;" // Закругленные углы
                              "    padding: 10px 20px;" // Внутренние отступы
                              "    font-size: 16px;" // Размер шрифта
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #808080;" // Цвет при наведении
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #474A51;" // Цвет при нажатии
                              "}");
        layout->addWidget(button);

        // Подключение слотов к сигналу clicked() каждой кнопки
        if (buttonText == "Офисы") {
            connect(button, &QPushButton::clicked, this, &menuwindow::onb11);
        } else if (buttonText == "Сервисные центры") {
            connect(button, &QPushButton::clicked, this, &menuwindow::onb22);
        } else if (buttonText == "Клиенты") {
            connect(button, &QPushButton::clicked, this, &menuwindow::onb33);
        } else if (buttonText == "Техника") {
            connect(button, &QPushButton::clicked, this, &menuwindow::onb55);
        } else if (buttonText == "Заказы") {
            connect(button, &QPushButton::clicked, this, &menuwindow::onb77);
        }
    }

    // Создаем кнопку возврата в окно регистрации
    returnToRegistrationButton = new QPushButton("Вернуться к регистрации", this);
    returnToRegistrationButton->setStyleSheet("QPushButton {"
                                              "    background-color: #4682B4;" // Синий цвет фона
                                              "    color: white;" // Белый цвет текста
                                              "    border-radius: 10px;" // Закругленные углы
                                              "    padding: 10px 20px;" // Внутренние отступы
                                              "    font-size: 16px;" // Размер шрифта
                                              "}"
                                              "QPushButton:hover {"
                                              "    background-color: #5F9EA0;" // Цвет при наведении
                                              "}"
                                              "QPushButton:pressed {"
                                              "    background-color: #4682B4;" // Цвет при нажатии
                                              "}");
    layout->addWidget(returnToRegistrationButton);
    connect(returnToRegistrationButton, &QPushButton::clicked, this, &menuwindow::onReturnToRegistrationClicked);

    // Создаем кнопку выхода только один раз
    exitButton = new QPushButton("Выход", this);
    exitButton->setStyleSheet("QPushButton {"
                              "    background-color: #B22222;" // Красный цвет фона
                              "    color: white;" // Белый цвет текста
                              "    border-radius: 10px;" // Закругленные углы
                              "    padding: 10px 20px;" // Внутренние отступы
                              "    font-size: 16px;" // Размер шрифта
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #CD5C5C;" // Цвет при наведении
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #B22222;" // Цвет при нажатии
                              "}");
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &menuwindow::onExitButtonClicked);
}

menuwindow::~menuwindow()
{
    delete ui;
    // Не удаляйте layout здесь, он будет удален автоматически при удалении родительского виджета
}

// Реализация слотов для каждой кнопки
void menuwindow::onb11()
{
    // Проверяем подключение к базе данных
    if (DatabaseHelper::isDatabaseConnected()) {
        // Если подключение успешно, открываем окно
        onb1 *onbDialog = new onb1(this);
        onbDialog->show();
        this->hide(); // Скрываем текущее окно MenuWindow
    } else {
        // Если подключение не установлено, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
}

void menuwindow::onb22()
{
    // Проверяем подключение к базе данных
    if (DatabaseHelper::isDatabaseConnected()) {
        // Если подключение успешно, открываем окно
        onb2 *onbDialog = new onb2(this);
        onbDialog->show();
        this->hide(); // Скрываем текущее окно MenuWindow
    } else {
        // Если подключение не установлено, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
}

void menuwindow::onb33()
{
    // Проверяем подключение к базе данных
    if (DatabaseHelper::isDatabaseConnected()) {
        // Если подключение успешно, открываем окно
        onb3 *onbDialog = new onb3(this);
        onbDialog->show();
        this->hide(); // Скрываем текущее окно MenuWindow
    } else {
        // Если подключение не установлено, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
}

void menuwindow::onb55()
{
    // Проверяем подключение к базе данных
    if (DatabaseHelper::isDatabaseConnected()) {
        // Если подключение успешно, открываем окно
        onb5 *onbDialog = new onb5(this);
        onbDialog->show();
        this->hide(); // Скрываем текущее окно MenuWindow
    } else {
        // Если подключение не установлено, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
}

void menuwindow::onb77()
{
    // Проверяем подключение к базе данных
    if (DatabaseHelper::isDatabaseConnected()) {
        // Если подключение успешно, открываем окно
        onb7 *onbDialog = new onb7(this);
        onbDialog->show();
        this->hide(); // Скрываем текущее окно MenuWindow
    } else {
        // Если подключение не установлено, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
}

void menuwindow::onReturnToRegistrationClicked()
{
    close(); // Закрываем текущее окно меню
    registrationwindow *registrationWindow = new registrationwindow(); // Создаем новое окно регистрации
    registrationWindow->show(); // Отображаем окно регистрации
}

void menuwindow::onExitButtonClicked()
{
    // Обработка нажатия кнопки выхода
    close();
}
