#ifndef TWOBTECHDEVICE_H
#define TWOBTECHDEVICE_H

#include <QString>
#include <QList>
#include "serialdataitem.h"

class TwobTechDevice
{
public:
    TwobTechDevice();
    QString device_name;

    QList<SerialDataItem> data_items;
    QString getCom_port() const;
    void setCom_port(const QString &value);

    int getBaud_rate() const;
    void setBaud_rate(int value);

private:
    QString com_port;
    int baud_rate;
    
};

#endif // TWOBTECHDEVICE_H
