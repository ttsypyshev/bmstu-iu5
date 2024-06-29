/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registrationwindow
{
public:
    QLabel *lbPassword;
    QLabel *lbLogin;
    QLineEdit *leLogin;
    QLineEdit *lePassword;
    QLabel *lbRegistration;
    QPushButton *btnWelcome;

    void setupUi(QDialog *registrationwindow)
    {
        if (registrationwindow->objectName().isEmpty())
            registrationwindow->setObjectName(QString::fromUtf8("registrationwindow"));
        registrationwindow->resize(335, 298);
        lbPassword = new QLabel(registrationwindow);
        lbPassword->setObjectName(QString::fromUtf8("lbPassword"));
        lbPassword->setGeometry(QRect(40, 130, 46, 16));
        lbLogin = new QLabel(registrationwindow);
        lbLogin->setObjectName(QString::fromUtf8("lbLogin"));
        lbLogin->setGeometry(QRect(40, 80, 58, 16));
        leLogin = new QLineEdit(registrationwindow);
        leLogin->setObjectName(QString::fromUtf8("leLogin"));
        leLogin->setGeometry(QRect(110, 80, 125, 21));
        lePassword = new QLineEdit(registrationwindow);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setGeometry(QRect(110, 130, 125, 21));
        lbRegistration = new QLabel(registrationwindow);
        lbRegistration->setObjectName(QString::fromUtf8("lbRegistration"));
        lbRegistration->setGeometry(QRect(120, 30, 101, 16));
        btnWelcome = new QPushButton(registrationwindow);
        btnWelcome->setObjectName(QString::fromUtf8("btnWelcome"));
        btnWelcome->setGeometry(QRect(120, 190, 100, 32));

        retranslateUi(registrationwindow);

        QMetaObject::connectSlotsByName(registrationwindow);
    } // setupUi

    void retranslateUi(QDialog *registrationwindow)
    {
        registrationwindow->setWindowTitle(QCoreApplication::translate("registrationwindow", "registrationwindow", nullptr));
        lbPassword->setText(QCoreApplication::translate("registrationwindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        lbLogin->setText(QCoreApplication::translate("registrationwindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        lbRegistration->setText(QCoreApplication::translate("registrationwindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        btnWelcome->setText(QCoreApplication::translate("registrationwindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registrationwindow: public Ui_registrationwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H
