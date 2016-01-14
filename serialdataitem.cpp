#include "serialdataitem.h"

SerialDataItem::SerialDataItem()
{

}

QString SerialDataItem::getName() const
{
    return name;
}

void SerialDataItem::setName(const QString &value)
{
    name = value;
}

QString SerialDataItem::getUnits() const
{
    return units;
}

void SerialDataItem::setUnits(const QString &value)
{
    units = value;
}

double SerialDataItem::getDvalue() const
{
    return dvalue;
}

void SerialDataItem::setDvalue(double value)
{
    dvalue = value;
}

int SerialDataItem::getIvalue() const
{
    return ivalue;
}

void SerialDataItem::setIvalue(int value)
{
    ivalue = value;
}

int SerialDataItem::getPriority() const
{
    return priority;
}

void SerialDataItem::setPriority(int value)
{
    priority = value;
}

QDateTime SerialDataItem::getDateTime() const
{
    return dateTime;
}

void SerialDataItem::setDateTime(const QDateTime &value)
{
    dateTime = value;
}
