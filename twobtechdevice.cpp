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

