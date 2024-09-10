/********************************************************************************
** Form generated from reading UI file 'onb1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB1_H
#define UI_ONB1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_onb1
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *btnSearch;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *btn4;
    QLineEdit *le4;
    QPushButton *btn1;
    QPushButton *btn3;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *le2;
    QLineEdit *le3;
    QPushButton *btn2;
    QLabel *label_4;
    QLineEdit *le5;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *le6;
    QLabel *lbId_2;
    QLineEdit *le1;
    QTableWidget *tw;
    QTextEdit *teResult;
    QPushButton *btnReport;
    QPushButton *btnExit;
    QLineEdit *leSearch;

    void setupUi(QDialog *onb1)
    {
        if (onb1->objectName().isEmpty())
            onb1->setObjectName(QString::fromUtf8("onb1"));
        onb1->resize(678, 428);
        gridLayout_2 = new QGridLayout(onb1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnSearch = new QPushButton(onb1);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        gridLayout_2->addWidget(btnSearch, 0, 3, 1, 1);

        frame = new QFrame(onb1);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn4 = new QPushButton(frame);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 0, 2, 1, 3);

        le4 = new QLineEdit(frame);
        le4->setObjectName(QString::fromUtf8("le4"));

        gridLayout->addWidget(le4, 4, 2, 1, 3);

        btn1 = new QPushButton(frame);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout->addWidget(btn1, 7, 0, 1, 1);

        btn3 = new QPushButton(frame);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 7, 4, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 2);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 2);

        le2 = new QLineEdit(frame);
        le2->setObjectName(QString::fromUtf8("le2"));

        gridLayout->addWidget(le2, 2, 2, 1, 3);

        le3 = new QLineEdit(frame);
        le3->setObjectName(QString::fromUtf8("le3"));

        gridLayout->addWidget(le3, 3, 2, 1, 3);

        btn2 = new QPushButton(frame);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout->addWidget(btn2, 7, 1, 1, 2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        le5 = new QLineEdit(frame);
        le5->setObjectName(QString::fromUtf8("le5"));

        gridLayout->addWidget(le5, 5, 2, 1, 3);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 2);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        le6 = new QLineEdit(frame);
        le6->setObjectName(QString::fromUtf8("le6"));

        gridLayout->addWidget(le6, 6, 2, 1, 3);

        lbId_2 = new QLabel(frame);
        lbId_2->setObjectName(QString::fromUtf8("lbId_2"));

        gridLayout->addWidget(lbId_2, 1, 0, 1, 1);

        le1 = new QLineEdit(frame);
        le1->setObjectName(QString::fromUtf8("le1"));

        gridLayout->addWidget(le1, 1, 2, 1, 3);


        gridLayout_2->addWidget(frame, 1, 0, 1, 2);

        tw = new QTableWidget(onb1);
        tw->setObjectName(QString::fromUtf8("tw"));

        gridLayout_2->addWidget(tw, 1, 2, 1, 2);

        teResult = new QTextEdit(onb1);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 2, 0, 1, 4);

        btnReport = new QPushButton(onb1);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));

        gridLayout_2->addWidget(btnReport, 3, 0, 1, 1);

        btnExit = new QPushButton(onb1);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_2->addWidget(btnExit, 3, 3, 1, 1);

        leSearch = new QLineEdit(onb1);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        gridLayout_2->addWidget(leSearch, 0, 2, 1, 1);


        retranslateUi(onb1);

        QMetaObject::connectSlotsByName(onb1);
    } // setupUi

    void retranslateUi(QDialog *onb1)
    {
        onb1->setWindowTitle(QCoreApplication::translate("onb1", "Dialog", nullptr));
        btnSearch->setText(QCoreApplication::translate("onb1", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btn4->setText(QCoreApplication::translate("onb1", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        btn1->setText(QCoreApplication::translate("onb1", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btn3->setText(QCoreApplication::translate("onb1", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("onb1", "\320\220\320\264\321\200\320\265\321\201\321\201", nullptr));
        label->setText(QCoreApplication::translate("onb1", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        btn2->setText(QCoreApplication::translate("onb1", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("onb1", "\320\237\320\276\321\207\321\202\320\260 ", nullptr));
        label_3->setText(QCoreApplication::translate("onb1", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        label_5->setText(QCoreApplication::translate("onb1", "\320\247\320\260\321\201\321\213 \321\200\320\260\320\261\320\276\321\202\321\213 ", nullptr));
        lbId_2->setText(QCoreApplication::translate("onb1", "id", nullptr));
        btnReport->setText(QCoreApplication::translate("onb1", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        btnExit->setText(QCoreApplication::translate("onb1", "\320\222\321\213\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb1: public Ui_onb1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB1_H
