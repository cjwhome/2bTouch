#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QString>

//This was used for testing, feel free to remove
class DeviceModel
{
public:
    DeviceModel(QString dName, QString u, float v);

    QString deviceName;
    QString units;
    float value;
};

#endif // DEVICEMODEL_H
