/********************************************************************************
** Form generated from reading UI file 'onb7.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONB7_H
#define UI_ONB7_H

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

class Ui_onb7
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *btnExit;
    QLineEdit *leSearch;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *le3;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *cmb1;
    QLineEdit *le2;
    QComboBox *cmb2;
    QLineEdit *le4;
    QLabel *label;
    QLineEdit *le1;
    QPushButton *btn2;
    QPushButton *btnSearch;
    QTextEdit *teResult;
    QTableWidget *tw;
    QPushButton *btn1;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *onb7)
    {
        if (onb7->objectName().isEmpty())
            onb7->setObjectName(QString::fromUtf8("onb7"));
        onb7->resize(623, 453);
        gridLayout_2 = new QGridLayout(onb7);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnExit = new QPushButton(onb7);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_2->addWidget(btnExit, 5, 6, 1, 1);

        leSearch = new QLineEdit(onb7);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        gridLayout_2->addWidget(leSearch, 2, 4, 1, 1);

        frame = new QFrame(onb7);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        le3 = new QLineEdit(frame);
        le3->setObjectName(QString::fromUtf8("le3"));

        gridLayout->addWidget(le3, 4, 1, 1, 2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cmb1 = new QComboBox(frame);
        cmb1->setObjectName(QString::fromUtf8("cmb1"));

        gridLayout->addWidget(cmb1, 1, 1, 1, 2);

        le2 = new QLineEdit(frame);
        le2->setObjectName(QString::fromUtf8("le2"));

        gridLayout->addWidget(le2, 3, 1, 1, 2);

        cmb2 = new QComboBox(frame);
        cmb2->setObjectName(QString::fromUtf8("cmb2"));

        gridLayout->addWidget(cmb2, 2, 1, 1, 2);

        le4 = new QLineEdit(frame);
        le4->setObjectName(QString::fromUtf8("le4"));

        gridLayout->addWidget(le4, 5, 1, 1, 2);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le1 = new QLineEdit(frame);
        le1->setObjectName(QString::fromUtf8("le1"));

        gridLayout->addWidget(le1, 0, 1, 1, 2);


        gridLayout_2->addWidget(frame, 0, 0, 3, 2);

        btn2 = new QPushButton(onb7);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout_2->addWidget(btn2, 5, 0, 1, 1);

        btnSearch = new QPushButton(onb7);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        gridLayout_2->addWidget(btnSearch, 2, 6, 1, 1);

        teResult = new QTextEdit(onb7);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(teResult->sizePolicy().hasHeightForWidth());
        teResult->setSizePolicy(sizePolicy);
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 4, 0, 1, 7);

        tw = new QTableWidget(onb7);
        tw->setObjectName(QString::fromUtf8("tw"));

        gridLayout_2->addWidget(tw, 1, 2, 1, 5);

        btn1 = new QPushButton(onb7);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout_2->addWidget(btn1, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 5, 1, 1);


        retranslateUi(onb7);

        QMetaObject::connectSlotsByName(onb7);
    } // setupUi

    void retranslateUi(QDialog *onb7)
    {
        onb7->setWindowTitle(QCoreApplication::translate("onb7", "Dialog", nullptr));
        btnExit->setText(QCoreApplication::translate("onb7", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        label_5->setText(QCoreApplication::translate("onb7", "\320\224\320\260\321\202\320\260 \320\276\321\202\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_6->setText(QCoreApplication::translate("onb7", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("onb7", "\320\224\320\260\321\202\320\260 \320\267\320\260\320\272\320\260\320\267\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("onb7", "\320\236\321\204\320\270\321\201", nullptr));
        label_3->setText(QCoreApplication::translate("onb7", "\320\241\320\265\321\200\320\262\320\270\321\201\320\275\321\213\320\271 \321\206\320\265\320\275\321\202\321\200", nullptr));
        label->setText(QCoreApplication::translate("onb7", "id", nullptr));
        btn2->setText(QCoreApplication::translate("onb7", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnSearch->setText(QCoreApplication::translate("onb7", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btn1->setText(QCoreApplication::translate("onb7", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class onb7: public Ui_onb7 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONB7_H
