#ifndef SERIALDATAITEM_H
#define SERIALDATAITEM_H
#include <QString>
#include <QDateTime>

class SerialDataItem
{
public:
    SerialDataItem();



private:
    QString name;
    QString units;      //examples are ppb, ppm, c, k,
    double dvalue;
    int ivalue;
    int priority;
    QDateTime datetime;
};

#endif // SERIALDATAITEM_H
