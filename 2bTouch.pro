#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T06:20:11
#
#-------------------------------------------------

QT       += core gui serialport printsupport network 

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
    displaygraph.cpp \
    xmldevicereader.cpp \
    twobtechdevice.cpp \
    serialdataitem.cpp \
    parseddata.cpp \
    deviceprofile.cpp \
    filewriter.cpp \
    controlbacklight.cpp \
    settingsview.cpp \
    graphsettingsdialog.cpp \
    networkview.cpp \
    scannetworksview.cpp \
    keypad.cpp \
    usertypeview.cpp \
    adminview.cpp \
    settingswidget.cpp \
    serialhandler.cpp \
    keylineedit.cpp \
    diagnosticobject.cpp \
    statswidget.cpp \
    modbus_server.cpp \
    graphdialog.cpp \
    graphsettingsdialogb.cpp \
    selectgasdialog.cpp

HEADERS  += mainwindow.h \
    serialthread.h \
    defines.h \
    qcustomplot.h \
    displaygraph.h \
    model_106l.h \
    xmldevicereader.h \
    twobtechdevice.h \
    serialdataitem.h \
    parseddata.h \
    deviceprofile.h \
    filewriter.h \
    controlbacklight.h \
    settingsview.h \
    graphsettingsdialog.h \
    networkview.h \
    scannetworksview.h \
    keypad.h \
    usertypeview.h \
    adminview.h \
    settingswidget.h \
    serialhandler.h \
    keylineedit.h \
    diagnosticobject.h \
    statswidget.h \
    modbus_server.h \
    graphdialog.h \
    graphsettingsdialogb.h \
    selectgasdialog.h \
    gasdatastate.h

FORMS    += mainwindow.ui \
    displaygraph.ui \
    settingsview.ui \
    graphsettingsdialog.ui \
    networkview.ui \
    scannetworksview.ui \
    keypad.ui \
    usertypeview.ui \
    adminview.ui \
    settingswidget.ui \
    statswidget.ui \
    graphdialog.ui \
    designsettingsdialog.ui \
    graphsettingsdialogb.ui \
    selectgasdialog.ui

RESOURCES += \
    res.qrc

DISTFILES +=
