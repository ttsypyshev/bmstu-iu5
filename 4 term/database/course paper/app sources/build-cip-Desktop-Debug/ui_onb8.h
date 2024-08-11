/********************************************************************************
** Form generated from reading UI file 'onb8.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB8_H
#define UI_ONB8_H

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

class Ui_onb8
{
public:
    QPushButton *btnFilter;
    QPushButton *btn1;
    QFrame *frame;
    QComboBox *cmb2;
    QComboBox *cmb1;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnReport;
    QPushButton *btnExit;
    QTableWidget *tw;
    QLineEdit *leSearch;
    QPushButton *btnSearch;
    QTextEdit *teResult;

    void setupUi(QDialog *onb8)
    {
        if (onb8->objectName().isEmpty())
            onb8->setObjectName(QString::fromUtf8("onb8"));
        onb8->resize(649, 407);
        btnFilter = new QPushButton(onb8);
        btnFilter->setObjectName(QString::fromUtf8("btnFilter"));
        btnFilter->setGeometry(QRect(220, 350, 83, 29));
        btn1 = new QPushButton(onb8);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(130, 350, 81, 32));
        frame = new QFrame(onb8);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 30, 311, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        cmb2 = new QComboBox(frame);
        cmb2->setObjectName(QString::fromUtf8("cmb2"));
        cmb2->setGeometry(QRect(190, 110, 101, 31));
        cmb1 = new QComboBox(frame);
        cmb1->setObjectName(QString::fromUtf8("cmb1"));
        cmb1->setGeometry(QRect(191, 70, 101, 28));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 70, 111, 20));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 110, 91, 20));
        btnReport = new QPushButton(onb8);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));
        btnReport->setGeometry(QRect(27, 350, 100, 32));
        btnExit = new QPushButton(onb8);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(540, 350, 100, 32));
        tw = new QTableWidget(onb8);
        tw->setObjectName(QString::fromUtf8("tw"));
        tw->setGeometry(QRect(337, 40, 301, 221));
        leSearch = new QLineEdit(onb8);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));
        leSearch->setGeometry(QRect(370, 20, 113, 21));
        btnSearch = new QPushButton(onb8);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setGeometry(QRect(500, 10, 100, 32));
        teResult = new QTextEdit(onb8);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setGeometry(QRect(10, 270, 631, 74));
        teResult->setReadOnly(true);

        retranslateUi(onb8);

        QMetaObject::connectSlotsByName(onb8);
    } // setupUi

    void retranslateUi(QDialog *onb8)
    {
        onb8->setWindowTitle(QApplication::translate("onb8", "Dialog", nullptr));
        btnFilter->setText(QApplication::translate("onb8", "\320\244\320\270\320\273\321\214\321\202\321\200", nullptr));
        btn1->setText(QApplication::translate("onb8", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("onb8", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        label_3->setText(QApplication::translate("onb8", "\320\224\320\270\321\201\321\206\320\270\320\277\320\273\320\270\320\275\320\260", nullptr));
        btnReport->setText(QApplication::translate("onb8", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        btnExit->setText(QApplication::translate("onb8", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        btnSearch->setText(QApplication::translate("onb8", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb8: public Ui_onb8 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB8_H
