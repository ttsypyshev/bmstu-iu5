/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_menuwindow
{
public:

    void setupUi(QDialog *menuwindow)
    {
        if (menuwindow->objectName().isEmpty())
            menuwindow->setObjectName(QString::fromUtf8("menuwindow"));
        menuwindow->resize(400, 300);

        retranslateUi(menuwindow);

        QMetaObject::connectSlotsByName(menuwindow);
    } // setupUi

    void retranslateUi(QDialog *menuwindow)
    {
        menuwindow->setWindowTitle(QApplication::translate("menuwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menuwindow: public Ui_menuwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
