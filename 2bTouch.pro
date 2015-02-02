#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T06:20:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2bTouch
    target.files = 2bTouch
    target.path = /home/root
INSTALLS += target
TEMPLATE = app
CONFIG += serialport


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
