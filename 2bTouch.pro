#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T06:20:11
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 

TARGET = 2bTouch
    target.files = 2bTouch
    target.path = /home/armadillo
INSTALLS += target
TEMPLATE = app
CONFIG += serialport


SOURCES += main.cpp\
        mainwindow.cpp \
    serialthread.cpp \
    qcustomplot.cpp \
    showstats.cpp \
    displaygraph.cpp

HEADERS  += mainwindow.h \
    serialthread.h \
    defines.h \
    model_pom.h \
    qcustomplot.h \
    showstats.h \
    displaygraph.h

FORMS    += mainwindow.ui \
    showstats.ui \
    displaygraph.ui

RESOURCES += \
    res.qrc
