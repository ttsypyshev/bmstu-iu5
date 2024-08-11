/********************************************************************************
** Form generated from reading UI file 'onb6.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB6_H
#define UI_ONB6_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_onb6
{
public:
    QTextEdit *teResult;
    QFrame *frame;
    QLineEdit *le1;
    QLineEdit *le2;
    QLineEdit *le3;
    QPushButton *btn3;
    QPushButton *btn2;
    QPushButton *btn1;
    QPushButton *btn4;
    QLabel *lbStartdata;
    QLabel *lbPrice;
    QLabel *lbStaff;
    QComboBox *cmb1;
    QLabel *lbStaff_2;
    QLineEdit *le4;
    QLabel *label;
    QPushButton *btnSearch;
    QLineEdit *leSearch;
    QPushButton *btnReport;
    QTableWidget *tw;
    QPushButton *btnExit;

    void setupUi(QDialog *onb6)
    {
        if (onb6->objectName().isEmpty())
            onb6->setObjectName(QString::fromUtf8("onb6"));
        onb6->resize(680, 423);
        teResult = new QTextEdit(onb6);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setGeometry(QRect(20, 290, 631, 74));
        teResult->setReadOnly(true);
        frame = new QFrame(onb6);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 50, 311, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        le1 = new QLineEdit(frame);
        le1->setObjectName(QString::fromUtf8("le1"));
        le1->setGeometry(QRect(240, 40, 51, 21));
        le2 = new QLineEdit(frame);
        le2->setObjectName(QString::fromUtf8("le2"));
        le2->setGeometry(QRect(90, 70, 201, 21));
        le3 = new QLineEdit(frame);
        le3->setObjectName(QString::fromUtf8("le3"));
        le3->setGeometry(QRect(90, 100, 201, 21));
        btn3 = new QPushButton(frame);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(220, 200, 81, 32));
        btn2 = new QPushButton(frame);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(110, 200, 91, 32));
        btn1 = new QPushButton(frame);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(20, 200, 81, 32));
        btn4 = new QPushButton(frame);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(200, 0, 100, 32));
        lbStartdata = new QLabel(frame);
        lbStartdata->setObjectName(QString::fromUtf8("lbStartdata"));
        lbStartdata->setGeometry(QRect(170, 40, 58, 16));
        lbPrice = new QLabel(frame);
        lbPrice->setObjectName(QString::fromUtf8("lbPrice"));
        lbPrice->setGeometry(QRect(10, 70, 71, 16));
        lbStaff = new QLabel(frame);
        lbStaff->setObjectName(QString::fromUtf8("lbStaff"));
        lbStaff->setGeometry(QRect(10, 170, 71, 16));
        cmb1 = new QComboBox(frame);
        cmb1->setObjectName(QString::fromUtf8("cmb1"));
        cmb1->setGeometry(QRect(90, 160, 211, 32));
        lbStaff_2 = new QLabel(frame);
        lbStaff_2->setObjectName(QString::fromUtf8("lbStaff_2"));
        lbStaff_2->setGeometry(QRect(10, 130, 71, 16));
        le4 = new QLineEdit(frame);
        le4->setObjectName(QString::fromUtf8("le4"));
        le4->setGeometry(QRect(90, 130, 201, 21));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 71, 20));
        btnSearch = new QPushButton(onb6);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setGeometry(QRect(520, 20, 100, 32));
        leSearch = new QLineEdit(onb6);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));
        leSearch->setGeometry(QRect(390, 30, 113, 21));
        btnReport = new QPushButton(onb6);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));
        btnReport->setGeometry(QRect(30, 370, 100, 32));
        tw = new QTableWidget(onb6);
        tw->setObjectName(QString::fromUtf8("tw"));
        tw->setGeometry(QRect(347, 60, 301, 221));
        btnExit = new QPushButton(onb6);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(550, 370, 100, 32));

        retranslateUi(onb6);

        QMetaObject::connectSlotsByName(onb6);
    } // setupUi

    void retranslateUi(QDialog *onb6)
    {
        onb6->setWindowTitle(QApplication::translate("onb6", "Dialog", nullptr));
        btn3->setText(QApplication::translate("onb6", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btn2->setText(QApplication::translate("onb6", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btn1->setText(QApplication::translate("onb6", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btn4->setText(QApplication::translate("onb6", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        lbStartdata->setText(QApplication::translate("onb6", "id", nullptr));
        lbPrice->setText(QApplication::translate("onb6", "\320\244\320\230\320\236", nullptr));
        lbStaff->setText(QApplication::translate("onb6", "\320\232\320\260\321\204\320\265\320\264\321\200\320\260", nullptr));
        lbStaff_2->setText(QApplication::translate("onb6", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        label->setText(QApplication::translate("onb6", "\320\227\320\260\321\200\320\277\320\273\320\260\321\202\320\260", nullptr));
        btnSearch->setText(QApplication::translate("onb6", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnReport->setText(QApplication::translate("onb6", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        btnExit->setText(QApplication::translate("onb6", "\320\222\321\213\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb6: public Ui_onb6 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB6_H
