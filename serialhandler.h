#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QtNetwork>
#include "xmldevicereader.h"
#include "twobtechdevice.h"

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandler(int type, QHostAddress addr, QObject *parent = 0);

    enum ConnType
    {
        Serial = 0,
        Tcp = 1
    };

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
    void writeChar(char c);

    void dataReady();
    void netDataReady();
    void readData(QString data);

    void updateSettings();

private slots:
    void newConnection();

private:
    ConnType connType;

    QString portName;
    QSerialPort *serialPort;
    int baudRate;

    void configSerialPort();
    TwobTechDevice device;
    XmlDeviceReader *reader;

    QString *data;
    QList<QString*> dataList;
    void checkQueue();

    //void dataReady();
    void handleSyncData(QString retData);
    int syncIndex;

    QSettings *settings;
    bool gettingSettings;

    //Netowrking
    QTcpServer server;
    QList<QTcpSocket *> netSockets;
    QTcpSocket *getSocket;
    QHostAddress getAddress;
};

#endif // SERIALHANDLER_H
