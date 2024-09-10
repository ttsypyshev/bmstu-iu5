/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *btnConnect;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSelectAll;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLineEdit *leAbbr;
    QLineEdit *leCity;
    QLabel *lbAbbr;
    QLabel *lbTitle;
    QLineEdit *leInn;
    QLabel *lbInn;
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QPushButton *btnEdit;
    QLabel *lbCity;
    QTextEdit *teTitle;
    QSpacerItem *verticalSpacer;
    QTableWidget *twOrg;
    QTextEdit *teResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1065, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        gridLayout_2->addWidget(btnConnect, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(355, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        btnSelectAll = new QPushButton(centralwidget);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));

        gridLayout_2->addWidget(btnSelectAll, 0, 3, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(511, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        leAbbr = new QLineEdit(frame);
        leAbbr->setObjectName(QString::fromUtf8("leAbbr"));

        gridLayout->addWidget(leAbbr, 0, 1, 1, 3);

        leCity = new QLineEdit(frame);
        leCity->setObjectName(QString::fromUtf8("leCity"));

        gridLayout->addWidget(leCity, 2, 1, 1, 3);

        lbAbbr = new QLabel(frame);
        lbAbbr->setObjectName(QString::fromUtf8("lbAbbr"));

        gridLayout->addWidget(lbAbbr, 0, 0, 1, 1);

        lbTitle = new QLabel(frame);
        lbTitle->setObjectName(QString::fromUtf8("lbTitle"));

        gridLayout->addWidget(lbTitle, 1, 0, 1, 1);

        leInn = new QLineEdit(frame);
        leInn->setObjectName(QString::fromUtf8("leInn"));

        gridLayout->addWidget(leInn, 3, 1, 1, 3);

        lbInn = new QLabel(frame);
        lbInn->setObjectName(QString::fromUtf8("lbInn"));

        gridLayout->addWidget(lbInn, 3, 0, 1, 1);

        btnAdd = new QPushButton(frame);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout->addWidget(btnAdd, 5, 1, 1, 1);

        btnDel = new QPushButton(frame);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));

        gridLayout->addWidget(btnDel, 5, 3, 1, 1);

        btnEdit = new QPushButton(frame);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        gridLayout->addWidget(btnEdit, 5, 2, 1, 1);

        lbCity = new QLabel(frame);
        lbCity->setObjectName(QString::fromUtf8("lbCity"));

        gridLayout->addWidget(lbCity, 2, 0, 1, 1);

        teTitle = new QTextEdit(frame);
        teTitle->setObjectName(QString::fromUtf8("teTitle"));

        gridLayout->addWidget(teTitle, 1, 1, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 3);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        twOrg = new QTableWidget(centralwidget);
        twOrg->setObjectName(QString::fromUtf8("twOrg"));

        gridLayout_2->addWidget(twOrg, 1, 1, 1, 3);

        teResult = new QTextEdit(centralwidget);
        teResult->setObjectName(QString::fromUtf8("teResult"));
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 2, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1065, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
        lbAbbr->setText(QCoreApplication::translate("MainWindow", "Abbr", nullptr));
        lbTitle->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        lbInn->setText(QCoreApplication::translate("MainWindow", "INN", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        btnDel->setText(QCoreApplication::translate("MainWindow", "Del", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        lbCity->setText(QCoreApplication::translate("MainWindow", "City", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
