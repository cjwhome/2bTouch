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
private:

    
};

#endif // TWOBTECHDEVICE_H
