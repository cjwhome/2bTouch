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
    showstats.cpp \
    displaygraph.cpp \
    xmldevicereader.cpp \
    twobtechdevice.cpp \
    serialdataitem.cpp \
    parseddata.cpp \
    deviceprofile.cpp \
    filewriter.cpp \
<<<<<<< HEAD
    settingswidget.cpp \
    devicemodel.cpp
=======
    controlbacklight.cpp \
    settingsview.cpp \
    graphsettingsdialog.cpp \
    networkview.cpp \
    scannetworksview.cpp \
    keypad.cpp \
    usertypeview.cpp \
    adminview.cpp
>>>>>>> 53d69c6e0f6780facc0408cc9525eb5e30bd5129

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
    filewriter.h \
<<<<<<< HEAD
    settingswidget.h \
    devicemodel.h
=======
    controlbacklight.h \
    settingsview.h \
    graphsettingsdialog.h \
    networkview.h \
    scannetworksview.h \
    keypad.h \
    usertypeview.h \
    adminview.h
>>>>>>> 53d69c6e0f6780facc0408cc9525eb5e30bd5129

FORMS    += mainwindow.ui \
    showstats.ui \
    displaygraph.ui \
<<<<<<< HEAD
    settingswidget.ui
=======
    settingsview.ui \
    graphsettingsdialog.ui \
    networkview.ui \
    scannetworksview.ui \
    keypad.ui \
    usertypeview.ui \
    adminview.ui
>>>>>>> 53d69c6e0f6780facc0408cc9525eb5e30bd5129

RESOURCES += \
    res.qrc

DISTFILES +=
