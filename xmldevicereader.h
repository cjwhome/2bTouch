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
 
    QList<TwobTechDevice> getDeviceList() const;


private:
    void processDevices();
    void processDevice();
    void processDataItems(TwobTechDevice *device);
    void processDataItem(TwobTechDevice *device);
    QString readNextText();
    QString errorString();
 
    QString filename;
    QXmlStreamReader xml;
    QList<TwobTechDevice> deviceList;
};

#endif // XMLDEVICEREADER_H
