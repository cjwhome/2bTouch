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

QDateTime SerialDataItem::getDate() const
{
    return date;
}

void SerialDataItem::setDate(const QDateTime &value)
{
    date = value;
}

QDateTime SerialDataItem::getTime() const
{
    return time;
}

void SerialDataItem::setTime(const QDateTime &value)
{
    time = value;
}

