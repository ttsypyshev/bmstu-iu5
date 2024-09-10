/********************************************************************************
** Form generated from reading UI file 'onb4.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB4_H
#define UI_ONB4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_onb4
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *btnReport;
    QTableWidget *tw;
    QTextEdit *teResult;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLineEdit *le2;
    QLineEdit *le3;
    QLabel *lbPrice;
    QLabel *lbStaff;
    QPushButton *btn3;
    QComboBox *cmb1;
    QPushButton *btn4;
    QPushButton *btn1;
    QLineEdit *le1;
    QLabel *lbFinishdata;
    QLabel *lbStartdata;
    QPushButton *btnSearch;
    QLineEdit *leSearch;
    QPushButton *btnExit;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *onb4)
    {
        if (onb4->objectName().isEmpty())
            onb4->setObjectName(QString::fromUtf8("onb4"));
        onb4->resize(687, 409);
        gridLayout_2 = new QGridLayout(onb4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnReport = new QPushButton(onb4);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));

        gridLayout_2->addWidget(btnReport, 4, 0, 1, 1);

        tw = new QTableWidget(onb4);
        tw->setObjectName(QString::fromUtf8("tw"));

        gridLayout_2->addWidget(tw, 2, 1, 1, 3);

        teResult = new QTextEdit(onb4);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 3, 0, 1, 4);

        frame = new QFrame(onb4);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        le2 = new QLineEdit(frame);
        le2->setObjectName(QString::fromUtf8("le2"));

        gridLayout->addWidget(le2, 2, 2, 1, 2);

        le3 = new QLineEdit(frame);
        le3->setObjectName(QString::fromUtf8("le3"));

        gridLayout->addWidget(le3, 3, 2, 1, 2);

        lbPrice = new QLabel(frame);
        lbPrice->setObjectName(QString::fromUtf8("lbPrice"));

        gridLayout->addWidget(lbPrice, 3, 0, 1, 2);

        lbStaff = new QLabel(frame);
        lbStaff->setObjectName(QString::fromUtf8("lbStaff"));

        gridLayout->addWidget(lbStaff, 4, 0, 1, 2);

        btn3 = new QPushButton(frame);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 5, 2, 1, 2);

        cmb1 = new QComboBox(frame);
        cmb1->setObjectName(QString::fromUtf8("cmb1"));

        gridLayout->addWidget(cmb1, 4, 2, 1, 2);

        btn4 = new QPushButton(frame);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 0, 2, 1, 2);

        btn1 = new QPushButton(frame);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout->addWidget(btn1, 5, 0, 1, 1);

        le1 = new QLineEdit(frame);
        le1->setObjectName(QString::fromUtf8("le1"));

        gridLayout->addWidget(le1, 1, 3, 1, 1);

        lbFinishdata = new QLabel(frame);
        lbFinishdata->setObjectName(QString::fromUtf8("lbFinishdata"));

        gridLayout->addWidget(lbFinishdata, 2, 0, 1, 2);

        lbStartdata = new QLabel(frame);
        lbStartdata->setObjectName(QString::fromUtf8("lbStartdata"));

        gridLayout->addWidget(lbStartdata, 1, 1, 1, 2);


        gridLayout_2->addWidget(frame, 1, 0, 2, 1);

        btnSearch = new QPushButton(onb4);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        gridLayout_2->addWidget(btnSearch, 0, 3, 2, 1);

        leSearch = new QLineEdit(onb4);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        gridLayout_2->addWidget(leSearch, 0, 1, 1, 1);

        btnExit = new QPushButton(onb4);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_2->addWidget(btnExit, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        retranslateUi(onb4);

        QMetaObject::connectSlotsByName(onb4);
    } // setupUi

    void retranslateUi(QDialog *onb4)
    {
        onb4->setWindowTitle(QApplication::translate("onb4", "Dialog", nullptr));
        btnReport->setText(QApplication::translate("onb4", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        lbPrice->setText(QApplication::translate("onb4", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        lbStaff->setText(QApplication::translate("onb4", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        btn3->setText(QApplication::translate("onb4", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btn4->setText(QApplication::translate("onb4", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        btn1->setText(QApplication::translate("onb4", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        lbFinishdata->setText(QApplication::translate("onb4", "\320\244\320\230\320\236", nullptr));
        lbStartdata->setText(QApplication::translate("onb4", "id", nullptr));
        btnSearch->setText(QApplication::translate("onb4", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnExit->setText(QApplication::translate("onb4", "\320\222\321\213\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb4: public Ui_onb4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB4_H
