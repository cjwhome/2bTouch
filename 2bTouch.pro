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
#CONFIG += serialport


SOURCES += main.cpp\
        mainwindow.cpp \
    serialthread.cpp \
    qcustomplot.cpp \
    showstats.cpp \
    displaygraph.cpp \
    xmldevicereader.cpp \
    twobtechdevice.cpp \
    serialdataitem.cpp \
    parseddata.cpp \
    deviceprofile.cpp \
    filewriter.cpp

HEADERS  += mainwindow.h \
    serialthread.h \
    defines.h \
    qcustomplot.h \
    showstats.h \
    displaygraph.h \
    model_106l.h \
    xmldevicereader.h \
    twobtechdevice.h \
    serialdataitem.h \
    parseddata.h \
    deviceprofile.h \
    filewriter.h

FORMS    += mainwindow.ui \
    showstats.ui \
    displaygraph.ui \
    testform.ui

RESOURCES += \
    res.qrc

DISTFILES +=
