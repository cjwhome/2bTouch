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

QString DeviceProfile::getCom_port() const
{
    return com_port;
}

void DeviceProfile::setCom_port(const QString &value)
{
    com_port = value;
}

QString DeviceProfile::getDiagnosticA_units() const
{
    return diagnosticA_units;
}

void DeviceProfile::setDiagnosticA_units(const QString &value)
{
    diagnosticA_units = value;
}

QString DeviceProfile::getDiagnosticB_units() const
{
    return diagnosticB_units;
}

void DeviceProfile::setDiagnosticB_units(const QString &value)
{
    diagnosticB_units = value;
}

QString DeviceProfile::getDiagnosticC_units() const
{
    return diagnosticC_units;
}

void DeviceProfile::setDiagnosticC_units(const QString &value)
{
    diagnosticC_units = value;
}

QString DeviceProfile::getMain_display_name() const
{
    return main_display_name;
}

void DeviceProfile::setMain_display_name(const QString &value)
{
    main_display_name = value;
}

QString DeviceProfile::getDiagnosticA_name() const
{
    return diagnosticA_name;
}

void DeviceProfile::setDiagnosticA_name(const QString &value)
{
    diagnosticA_name = value;
}

QString DeviceProfile::getDiagnosticB_name() const
{
    return diagnosticB_name;
}

void DeviceProfile::setDiagnosticB_name(const QString &value)
{
    diagnosticB_name = value;
}

QString DeviceProfile::getDiagnosticC_name() const
{
    return diagnosticC_name;
}

void DeviceProfile::setDiagnosticC_name(const QString &value)
{
    diagnosticC_name = value;
}

int DeviceProfile::getDiagnosticA_position() const
{
    return diagnosticA_position;
}

void DeviceProfile::setDiagnosticA_position(int value)
{
    diagnosticA_position = value;
}

int DeviceProfile::getDiagnosticB_position() const
{
    return diagnosticB_position;
}

void DeviceProfile::setDiagnosticB_position(int value)
{
    diagnosticB_position = value;
}

int DeviceProfile::getDiagnosticC_position() const
{
    return diagnosticC_position;
}

void DeviceProfile::setDiagnosticC_position(int value)
{
    diagnosticC_position = value;
}



