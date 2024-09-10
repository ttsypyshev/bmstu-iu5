#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class menuwindow;
}

class menuwindow : public QDialog
{
    Q_OBJECT

public:
    explicit menuwindow(const QStringList &allowedButtons, QWidget *parent = nullptr);
    ~menuwindow();

private slots:
    void onb11();
    void onb22();
    void onb33();
    void onb55();
    void onb77();
    void onExitButtonClicked();
    void onReturnToRegistrationClicked();

private:
    Ui::menuwindow *ui;
    QPushButton *exitButton;
    QPushButton *returnToRegistrationButton;
};

#endif // MENUWINDOW_H
