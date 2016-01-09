#include "deviceprofile.h"

DeviceProfile::DeviceProfile()
{

}

QString DeviceProfile::getDevice_name() const
{
    return device_name;
}

void DeviceProfile::setDevice_name(const QString &value)
{
    device_name = value;
}

int DeviceProfile::getMain_display_position() const
{
    return main_display_position;
}

void DeviceProfile::setMain_display_position(int value)
{
    main_display_position = value;
}

int DeviceProfile::getDatetime_position() const
{
    return datetime_position;
}

void DeviceProfile::setDatetime_position(int value)
{
    datetime_position = value;
}

