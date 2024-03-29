#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T17:41:30
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MLBproj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    database.cpp \
    adminwindow.cpp \
    graph.cpp \
    souvenirwindow.cpp \
    checkoutwindow.cpp \
    form.cpp \
    adminlogin.cpp \
    souvs.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    database.h \
    adminwindow.h \
    graph.h \
    souvenirwindow.h \
    checkoutwindow.h \
    form.h \
    adminlogin.h \
    souvs.h

FORMS += \
        mainwindow.ui \
    login.ui \
    adminwindow.ui \
    souvenirwindow.ui \
    checkoutwindow.ui \
    form.ui \
    adminlogin.ui \
    souvs.ui

RESOURCES += \
    resources.qrc
