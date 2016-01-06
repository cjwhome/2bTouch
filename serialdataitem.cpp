#include "serialdataitem.h"

SerialDataItem::SerialDataItem()
{

}

QString SerialDataItem::getType() const
{
    return type;
}

void SerialDataItem::setType(const QString &value)
{
    type = value;
}

QString SerialDataItem::getName() const
{
    return name;
}

void SerialDataItem::setName(const QString &value)
{
    name = value;
}

