#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T11:32:12
#
#-------------------------------------------------

QT += core gui widgets serialport printsupport network

TARGET = 2BTouch-MultiPlot
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

CONFIG += c++11 #console

SOURCES += \
        main.cpp \
    devicemodel.cpp \
    richtextdelegate.cpp \
    menutreeform.cpp \
    modform.cpp \
    averageform.cpp \
    configform.cpp \
    datetimeform.cpp \
    calform.cpp \
    analogform.cpp \
    uimanager.cpp \
    grabdata.cpp \
    modbusform.cpp \
    keylineedit.cpp \
    keypad.cpp \
    modbusserver.cpp \
    networkform.cpp \
    filesform.cpp \
    networkconnectedform.cpp \
    networkmanager.cpp \
    deviceprofile.cpp \
    displaygraph.cpp \
    graphsettingsform.cpp \
    selectgasform.cpp \
    qcustomplot.cpp \
    xmldevicereader.cpp \
    twobtechdevice.cpp \
    serialdataitem.cpp \
    serialthread.cpp \
    statsaverageform.cpp \
    clickablelabel.cpp \
    parseddata.cpp \
    filewriter.cpp \
    serialhandler.cpp \
    mainwindow.cpp \
    statsmenuform.cpp \
    landingpage.cpp \
    serialqueue.cpp \
    errorform.cpp \
    testform.cpp

HEADERS += \
    devicemodel.h \
    richtextdelegate.h \
    menutreeform.h \
    modform.h \
    averageform.h \
    configform.h \
    datetimeform.h \
    calform.h \
    analogform.h \
    uimanager.h \
    grabdata.h \
    modbusform.h \
    keylineedit.h \
    keypad.h \
    modbusserver.h \
    networkform.h \
    filesform.h \
    networkconnectedform.h \
    networkmanager.h \
    deviceprofile.h \
    displaygraph.h \
    gasdatastate.h \
    graphsettingsform.h \
    selectgasform.h \
    qcustomplot.h \
    xmldevicereader.h \
    twobtechdevice.h \
    serialdataitem.h \
    serialthread.h \
    statsaverageform.h \
    clickablelabel.h \
    parseddata.h \
    filewriter.h \
    serialhandler.h \
    mainwindow.h \
    statsmenuform.h \
    landingpage.h \
    serialqueue.h \
    errorform.h \
    testform.h

FORMS += \
    menutreeform.ui \
    modform.ui \
    averageform.ui \
    configform.ui \
    datetimeform.ui \
    calform.ui \
    analogform.ui \
    modbusform.ui \
    keypad.ui \
    networkform.ui \
    filesform.ui \
    networkconnectedform.ui \
    displaygraph.ui \
    graphsettingsform.ui \
    selectgasform.ui \
    statsaverageform.ui \
    mainwindow.ui \
    statsmenuform.ui \
    landingpage.ui \
    errorform.ui \
    testform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \

DISTFILES += \
    Notes \
    RemovedClassIUpdateData

