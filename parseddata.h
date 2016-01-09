#ifndef PARSEDDATA_H
#define PARSEDDATA_H
#include <QList>
#include "serialdataitem.h"

class parsedData
{
public:
    parsedData();
private:
    QList<SerialDataItem> data_items;

};

#endif // PARSEDDATA_H
