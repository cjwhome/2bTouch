#include "xmldevicereader.h"

#include <QFile>
#include <QDebug>


XmlDeviceReader::XmlDeviceReader(const QString fname){
    filename = fname;
}

void XmlDeviceReader::read() {
    QFile xmlFile(filename);
    xmlFile.open(QIODevice::ReadOnly);
    xml.setDevice(&xmlFile);

    if (xml.readNextStartElement() && xml.name() == "devices")
       processDevices();

    // readNextStartElement() leaves the stream in
    // an invalid state at the end. A single readNext()
    // will advance us to EndDocument.
    if (xml.tokenType() == QXmlStreamReader::Invalid)
        xml.readNext();

    if (xml.hasError()) {
        xml.raiseError();
        qDebug() << errorString();
    }
}

void XmlDeviceReader::processDevices() {
    if (!xml.isStartElement() || xml.name() != "devices")
        return;
    while (xml.readNextStartElement()) {
        if (xml.name() == "device")
            processDevice();
        else
            xml.skipCurrentElement();
    }
}

// Uncomment this to see another way to read element
// text. It returns the concatenation of the text
// from all child elements.
//#define USE_READ_ELEMENT_TEXT 1

void XmlDeviceReader::processDevice() {
    if (!xml.isStartElement() || xml.name() != "device")
        return;

    /*QString from;
    QString to;
    QString conversion;
    
    while (xml.readNextStartElement()) {
        if (xml.name() == "from")
            from = readNextText();
        else if (xml.name() == "to")
            to = readNextText();
        else if (xml.name() == "conversion")
            conversion = readNextText();
#ifndef USE_READ_ELEMENT_TEXT
        xml.skipCurrentElement();
#endif
    }*/
    QList<TwobTechDevice> deviceList;

    
    if (xml.isStartElement()) {
                if (xml.name() == "device") {
                    TwobTechDevice twobTechDevice = new TwobTechDevice();
                    foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                        if (attr.name().toString() == QLatin1String("name")) {
                            twobTechDevice.device_name = attr.value().toString();
                        }
                    }
                }
            }

    
}

QString XmlDeviceReader::readNextText() {
#ifndef USE_READ_ELEMENT_TEXT
    xml.readNext();
    return xml.text().toString();
#else
    return xml.readElementText();
#endif
}

QString XmlDeviceReader::errorString() {
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}
