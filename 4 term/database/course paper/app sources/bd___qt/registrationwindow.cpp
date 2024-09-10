#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>
#include "databasehelper.h"
#include "authenticationmanager.h"

registrationwindow::registrationwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registrationwindow)
{
    ui->setupUi(this);

    ui->lePassword->setEchoMode(QLineEdit::Password);
}

registrationwindow::~registrationwindow()
{
    delete ui;
}

void registrationwindow::on_btnWelcome_clicked()
{
    // Получение логина и пароля из полей ввода
    QString login = ui->leLogin->text();
    QString password = ui->lePassword->text();

    // Проверка, что логин и пароль не пусты
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите логин и пароль.");
        return;
    }

    // Сохранение информации о пользователе
    AuthenticationManager::saveUserInfo(login);

    // Получение списка разрешенных кнопок из AuthenticationManager
    QStringList allowedButtons = AuthenticationManager::getAllowedButtons(login);

    // Попытка подключения к базе данных
    if (DatabaseHelper::connectToDatabase("localhost", "postgres", login, password)) {
        // Если подключение успешно, переходим в меню
        menuwindow *menuWindow = new menuwindow(allowedButtons);
        menuWindow->show();
        this->close(); // Закрываем текущее окно регистрации
    } else {
        // Если подключение не удалось, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Ошибка подключения:\n" + DatabaseHelper::lastError().text());
    }
}
