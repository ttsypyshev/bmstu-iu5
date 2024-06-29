/********************************************************************************
** Form generated from reading UI file 'onb2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB2_H
#define UI_ONB2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_onb2
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tw;
    QLineEdit *leSearch;
    QPushButton *btnExit;
    QSpacerItem *horizontalSpacer;
    QTextEdit *teResult;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *btn4;
    QPushButton *btn2;
    QPushButton *btn1;
    QLabel *lbFinishdata;
    QLabel *label_2;
    QLabel *lbPrice;
    QPushButton *btn3;
    QLabel *label;
    QLineEdit *le4;
    QLineEdit *le5;
    QLineEdit *le3;
    QLineEdit *le2;
    QLabel *lbStartdata;
    QLineEdit *le1;
    QPushButton *btnReport;
    QPushButton *btnSearch;

    void setupUi(QDialog *onb2)
    {
        if (onb2->objectName().isEmpty())
            onb2->setObjectName(QString::fromUtf8("onb2"));
        onb2->resize(676, 432);
        gridLayout_2 = new QGridLayout(onb2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tw = new QTableWidget(onb2);
        tw->setObjectName(QString::fromUtf8("tw"));

        gridLayout_2->addWidget(tw, 1, 1, 1, 3);

        leSearch = new QLineEdit(onb2);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        gridLayout_2->addWidget(leSearch, 0, 1, 1, 1);

        btnExit = new QPushButton(onb2);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_2->addWidget(btnExit, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        teResult = new QTextEdit(onb2);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 3, 0, 1, 4);

        frame = new QFrame(onb2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn4 = new QPushButton(frame);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 0, 2, 1, 2);

        btn2 = new QPushButton(frame);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout->addWidget(btn2, 7, 2, 1, 1);

        btn1 = new QPushButton(frame);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout->addWidget(btn1, 7, 0, 1, 2);

        lbFinishdata = new QLabel(frame);
        lbFinishdata->setObjectName(QString::fromUtf8("lbFinishdata"));

        gridLayout->addWidget(lbFinishdata, 2, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 6, 0, 1, 1);

        lbPrice = new QLabel(frame);
        lbPrice->setObjectName(QString::fromUtf8("lbPrice"));

        gridLayout->addWidget(lbPrice, 3, 0, 1, 1);

        btn3 = new QPushButton(frame);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 7, 3, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        le4 = new QLineEdit(frame);
        le4->setObjectName(QString::fromUtf8("le4"));

        gridLayout->addWidget(le4, 4, 2, 1, 2);

        le5 = new QLineEdit(frame);
        le5->setObjectName(QString::fromUtf8("le5"));

        gridLayout->addWidget(le5, 6, 2, 1, 2);

        le3 = new QLineEdit(frame);
        le3->setObjectName(QString::fromUtf8("le3"));

        gridLayout->addWidget(le3, 3, 2, 1, 2);

        le2 = new QLineEdit(frame);
        le2->setObjectName(QString::fromUtf8("le2"));

        gridLayout->addWidget(le2, 2, 2, 1, 2);

        lbStartdata = new QLabel(frame);
        lbStartdata->setObjectName(QString::fromUtf8("lbStartdata"));

        gridLayout->addWidget(lbStartdata, 1, 0, 1, 1);

        le1 = new QLineEdit(frame);
        le1->setObjectName(QString::fromUtf8("le1"));

        gridLayout->addWidget(le1, 1, 2, 1, 2);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        btnReport = new QPushButton(onb2);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));

        gridLayout_2->addWidget(btnReport, 4, 0, 1, 1);

        btnSearch = new QPushButton(onb2);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        gridLayout_2->addWidget(btnSearch, 0, 3, 1, 1);


        retranslateUi(onb2);

        QMetaObject::connectSlotsByName(onb2);
    } // setupUi

    void retranslateUi(QDialog *onb2)
    {
        onb2->setWindowTitle(QCoreApplication::translate("onb2", "Dialog", nullptr));
        btnExit->setText(QCoreApplication::translate("onb2", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        btn4->setText(QCoreApplication::translate("onb2", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        btn2->setText(QCoreApplication::translate("onb2", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btn1->setText(QCoreApplication::translate("onb2", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        lbFinishdata->setText(QCoreApplication::translate("onb2", "\320\220\320\264\321\200\320\265\321\201\321\201", nullptr));
        label_2->setText(QCoreApplication::translate("onb2", "\320\247\320\260\321\201\321\213 \321\200\320\260\320\261\320\276\321\202\321\213", nullptr));
        lbPrice->setText(QCoreApplication::translate("onb2", "\320\235\320\276\320\274\320\265\321\200", nullptr));
        btn3->setText(QCoreApplication::translate("onb2", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("onb2", "\320\237\320\276\321\207\321\202\320\260", nullptr));
        lbStartdata->setText(QCoreApplication::translate("onb2", "id", nullptr));
        btnReport->setText(QCoreApplication::translate("onb2", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        btnSearch->setText(QCoreApplication::translate("onb2", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb2: public Ui_onb2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB2_H
