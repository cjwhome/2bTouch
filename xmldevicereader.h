#ifndef XMLDEVICEREADER_H
#define XMLDEVICEREADER_H
#include <QXmlStreamReader>
#include <QFile>
#include <QList>
#include "twobtechdevice.h"
#include "serialdataitem.h"

class XmlDeviceReader
{
public:
    XmlDeviceReader(const QString fname);
 
    void read();
 
private:
    void processDevices();
    void processDevice();
    QString readNextText();
    QString errorString();
 
    QString filename;
    QXmlStreamReader xml;
};

#endif // XMLDEVICEREADER_H
