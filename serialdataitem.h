#ifndef SERIALDATAITEM_H
#define SERIALDATAITEM_H
#include <QString>
#include <QDateTime>

class SerialDataItem
{
public:
    SerialDataItem();



    QString getName() const;
    void setName(const QString &value);

    QString getUnits() const;
    void setUnits(const QString &value);

    double getDvalue() const;
    void setDvalue(double value);

    int getIvalue() const;
    void setIvalue(int value);

    int getPriority() const;
    void setPriority(int value);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);



private:
    QString name;
    QString units;      //examples are ppb, ppm, c, k,
    double dvalue;
    int ivalue;
    int priority;
    QDateTime dateTime;

};

#endif // SERIALDATAITEM_H
