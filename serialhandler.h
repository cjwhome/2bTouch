#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QTcpServer>
#include <QSettings>
#include <QSerialPort>
#include <QtNetwork>

#include "xmldevicereader.h"
#include "twobtechdevice.h"

#include "landingpage.h"
#include "errorform.h"

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    SerialHandler(QThread *thr, QObject *parent = nullptr);

    enum Types
    {
        Inactive,
        Asynchronously,
        Synchronously,
        Finished
    };
    SerialHandler::Types currentConnectionType;

    void writeLine(QString);

    static SerialHandler * getHandler(QThread*, QObject*);
    static SerialHandler * getHandler();

signals:
    void finished();

    void error();
    void dataAvailable(QString);

    void initialized();

    void boardReady();

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
    void writeInfo(QString *);
    void getRead();

private:
    static SerialHandler * handler;

    QThread *thread;

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

    //Networking
    QTcpServer server;
    QList<QTcpSocket *> netSockets;
};

#endif // SERIALHANDLER_H
