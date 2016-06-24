#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include "xmldevicereader.h"
#include "twobtechdevice.h"

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandler(QThread *thr, QObject *parent = 0);

    enum Types
    {
        Inactive,
        Asynchronously,
        Synchronously,
        Finished
    };
    SerialHandler::Types currentConnectionType;

signals:
    void finished();

    void error();
    void dataAvailable(QString);

public slots:
    void writeSync(QString *dat);
    void writeAsync(QString *dat);

    void dataReady();

private:
    QThread *thread;

    QString portName;
    QSerialPort *serialPort;
    int baudRate;

    void configSerialPort();
    TwobTechDevice device;
    XmlDeviceReader *reader;

    QString *data;

    //void dataReady();
    void handleSyncData(QString retData);
    int syncIndex;
};

#endif // SERIALHANDLER_H
