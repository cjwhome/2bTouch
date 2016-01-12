#ifndef PARSEDDATA_H
#define PARSEDDATA_H
#include <QList>
#include "serialdataitem.h"

class ParsedData
{
public:
    ParsedData();
private:
    QList<SerialDataItem> data_items;

};

#endif // PARSEDDATA_H
