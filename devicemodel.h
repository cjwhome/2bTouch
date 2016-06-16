#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "xmldevicereader.h"
#include "twobtechdevice.h"

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = 0);
    QString *com_port;

private:
    QSerialPort serial;
   XmlDeviceReader *xmlDeviceReader;

signals:

public slots:
};

#endif // DEVICEMODEL_H
