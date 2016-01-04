#ifndef TWOBTECHDEVICE_H
#define TWOBTECHDEVICE_H

#include <QString>
#include <QList>
#include "serialdataitem.h"

class TwobTechDevice
{
public:
    TwobTechDevice();
    
private:
    QString device_name;
    QList<SerialDataItem> data_items;
    
};

#endif // TWOBTECHDEVICE_H
