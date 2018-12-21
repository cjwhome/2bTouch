#ifndef GRABDATA_H
#define GRABDATA_H

#include <QDebug>
#include <QThread>
#include <QWaitCondition>
#include <QTime>
#include <QCoreApplication>
#include <iostream>
#include <string>

#include "datetimeform.h"
#include "uimanager.h"
#include "statsaverageform.h"
#include "calform.h"
#include "analogform.h"

using namespace std;

//This class was repurposed to update other classes.
class GrabData : public QThread
{

Q_OBJECT

public:
    ~GrabData();
    static GrabData * getManager();
    void getData();

signals:
    void update();

protected:
    void run() override;

private:
    GrabData(QObject * parent = 0);
    static GrabData *manager;
    QThread * mainThread;

    void delay();
    void process();
    void checkForSignal();
    QString readLine();
    void readInDateTime(string);
    void readInAllValues(string);

    QWaitCondition * condition;

    bool restart = false;
    bool abort = false;

signals:
    void updateDView();
};

#endif // GRABDATA_H
