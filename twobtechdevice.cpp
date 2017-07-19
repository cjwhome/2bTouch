#include "twobtechdevice.h"

TwobTechDevice::TwobTechDevice()
{

}

QString TwobTechDevice::getCom_port() const
{
    return com_port;
}

void TwobTechDevice::setCom_port(const QString &value)
{
    com_port = value;
}

int TwobTechDevice::getBaud_rate() const
{
    return baud_rate;
}

void TwobTechDevice::setBaud_rate(int value)
{
    baud_rate = value;
}

QString TwobTechDevice::getDevice_name() const
{
    return device_name;
}

void TwobTechDevice::setDevice_name(const QString &value)
{
    device_name = value;
}

