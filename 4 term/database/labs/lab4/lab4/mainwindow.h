#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase dbconn;
private slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();
    void edit();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
