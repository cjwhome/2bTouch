#ifndef SERIALDATAITEM_H
#define SERIALDATAITEM_H
#include <QString>

class SerialDataItem
{
public:
    SerialDataItem();

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

private:
    QString name;
    QString type;
};

#endif // SERIALDATAITEM_H
