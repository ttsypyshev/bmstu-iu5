#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include "menuwindow.h"


namespace Ui {
class registrationwindow;
}

class registrationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit registrationwindow(QWidget *parent = nullptr);
    ~registrationwindow();

private slots:
    void on_btnWelcome_clicked();

private:
    Ui::registrationwindow *ui;
    QSqlDatabase dbconn;
    menuwindow *menuWindow;
};

#endif // REGISTRATIONWINDOW_H
