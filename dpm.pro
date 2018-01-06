#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T18:03:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dpm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qsqlconnectiondialog.cpp \
    tablemodel.cpp \
    checkboxdelegate.cpp \
    sortfilterproxymodel.cpp \
    additemdialog.cpp \
    responsewidget.cpp \
    respopup.cpp \
    adduser.cpp \
    mysqlrelationaldelegate.cpp \
    edit.cpp

HEADERS  += mainwindow.h \
    qsqlconnectiondialog.h \
    tablemodel.h \
    checkboxdelegate.h \
    sortfilterproxymodel.h \
    additemdialog.h \
    responsewidget.h \
    respopup.h \
    adduser.h \
    mysqlrelationaldelegate.h \
    edit.h

FORMS    += mainwindow.ui \
    qsqlconnectiondialog.ui \
    additemdialog.ui \
    responsewidget.ui \
    respopup.ui \
    adduser.ui \
    edit.ui

RESOURCES += \
    resource.qrc
