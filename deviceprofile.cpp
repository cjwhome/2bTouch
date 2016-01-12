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

int DeviceProfile::getDate_position() const
{
    return date_position;
}

void DeviceProfile::setDate_position(int value)
{
    date_position = value;
}

void DeviceProfile::setTime_position(int value)
{
    time_position = value;
}

int DeviceProfile::getTime_position() const
{
    return time_position;
}

QString DeviceProfile::getMain_display_units() const
{
    return main_display_units;
}

void DeviceProfile::setMain_display_units(const QString &value)
{
    main_display_units = value;
}

int DeviceProfile::getNumber_of_columns() const
{
    return number_of_columns;
}

void DeviceProfile::setNumber_of_columns(int value)
{
    number_of_columns = value;
}

