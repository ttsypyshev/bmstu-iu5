#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

class DatabaseHelper
{
public:
    static bool connectToDatabase(const QString &hostName, const QString &databaseName,
                                  const QString &userName, const QString &password);
    static bool isDatabaseConnected();
    static QSqlError lastError();

    static QSqlDatabase getDatabaseConnection();
    static bool checkUser(const QString &login, const QString &password); // Объявление функции checkUser
private:
    static bool databaseConnected;
    static QSqlError lastDbError;

};

#endif // DATABASEHELPER_H
