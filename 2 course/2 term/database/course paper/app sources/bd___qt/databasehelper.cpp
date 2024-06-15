#include "databasehelper.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "authenticationmanager.h"

// Initialize static members
bool DatabaseHelper::databaseConnected = false;
QSqlError DatabaseHelper::lastDbError;

bool DatabaseHelper::connectToDatabase(const QString &hostName, const QString &databaseName,
                                       const QString &userName, const QString &password)
{
    // Add paths to database drivers
    QCoreApplication::addLibraryPath("/opt/homebrew/share/qt/plugins");
    QCoreApplication::addLibraryPath("/usr/local/lib/qt/plugins/sqldrivers");

    // Connect to the database
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);

    if (db.open()) {
        databaseConnected = true;
        return true;
    } else {
        lastDbError = db.lastError();
        databaseConnected = false;
        return false;
    }
}

bool DatabaseHelper::isDatabaseConnected()
{
    return databaseConnected;
}

QSqlError DatabaseHelper::lastError()
{
    return lastDbError;
}

QSqlDatabase DatabaseHelper::getDatabaseConnection()
{
    // Get the database connection object
    QSqlDatabase db = QSqlDatabase::database();

    // Check if the connection is open
    if (!db.isOpen()) {
        // If the connection is not open, output an error message
        qDebug() << "Database is not open. Error: " << db.lastError().text();
    }

    return db;
}

bool DatabaseHelper::checkUser(const QString &login, const QString &password)
{
    // Ensure the database is connected
    if (!isDatabaseConnected()) {
        qDebug() << "Database is not connected.";
        return false;
    }

    QSqlDatabase db = getDatabaseConnection();

    // Prepare the SQL query
    QSqlQuery query(db);
    query.prepare("SELECT password FROM users WHERE login = :login");
    query.bindValue(":login", login);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        return false;
    }

    // Check if user exists and validate password
    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == password) {
            return true;
        } else {
            qDebug() << "Invalid password.";
            return false;
        }
    } else {
        qDebug() << "User not found.";
        return false;
    }
}
