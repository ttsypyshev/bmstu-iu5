#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

class AuthenticationManager : public QObject
{
    Q_OBJECT

public:
    explicit AuthenticationManager(QObject *parent = nullptr);

    // Метод для аутентификации пользователя
    static bool authenticate(const QString &login, const QString &password);

    // Метод для сохранения информации о текущем пользователе
    static bool saveUserInfo(const QString &login);

    // Метод для получения логина текущего пользователя
    QString getCurrentUserLogin() const;

    // Метод для получения списка разрешенных кнопок в зависимости от роли пользователя
    static QStringList getAllowedButtons(const QString &login);

private:
    // Логин текущего пользователя
    static QString currentUserLogin;
};

#endif // AUTHENTICATIONMANAGER_H
