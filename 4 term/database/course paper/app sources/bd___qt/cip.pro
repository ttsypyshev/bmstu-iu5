QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authenticationmanager.cpp \
    databasehelper.cpp \
    main.cpp \
    menuwindow.cpp \
    onb1.cpp \
    onb2.cpp \
    onb3.cpp \
    onb5.cpp \
    onb7.cpp \
    registrationwindow.cpp

HEADERS += \
    authenticationmanager.h \
    databasehelper.h \
    menuwindow.h \
    onb1.h \
    onb2.h \
    onb3.h \
    onb5.h \
    onb7.h \
    registrationwindow.h

FORMS += \
    menuwindow.ui \
    onb1.ui \
    onb2.ui \
    onb3.ui \
    onb5.ui \
    onb7.ui \
    registrationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
