#ifndef PARSEDDATA_H
#define PARSEDDATA_H

#include<QList>

#include "serialdataitem.h"

class ParsedData
{
public:
    static ParsedData * getManager();

private:
    static ParsedData * manager;
    ParsedData();

    QList<SerialDataItem> data_items;
};

#endif // PARSEDDATA_H
