#ifndef TWOBTECHDEVICE_H
#define TWOBTECHDEVICE_H

#include <QList>

#include "serialdataitem.h"

class TwobTechDevice
{
public:
    TwobTechDevice();

    QList<SerialDataItem> data_items;
    QString getCom_port() const;
    void setCom_port(const QString &value);

    int getBaud_rate() const;
    void setBaud_rate(int value);

    QString getDevice_name() const;
    void setDevice_name(const QString &value);

private:
    QString com_port;
    int baud_rate;
    QString device_name;
};

#endif // TWOBTECHDEVICE_H
