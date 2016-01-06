#include "xmldevicereader.h"

#include <QFile>
#include <QDebug>


XmlDeviceReader::XmlDeviceReader(const QString fname){
    filename = fname;
}



void XmlDeviceReader::read() {
    QFile xmlFile(filename);
    qDebug()<<"XmlRead before open file";
    xmlFile.open(QIODevice::ReadOnly);
    xml.setDevice(&xmlFile);

    //testing
    /*while (!xml.atEnd()) {
        if (xml.readNextStartElement())
            qDebug()<<xml.name().toString();
    }*/


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
    qDebug()<<"Processing devices";
    //if (!xml.isStartElement() || xml.name() != "devices")
    //    return;
    while (!xml.atEnd()) {
        if (xml.readNextStartElement()){
            if (xml.isStartElement() && xml.name() == "device")
                processDevice();
            else{
                qDebug()<<"Skipping element in process devices:"<<xml.name().toString();

            }
        }
    }
}



void XmlDeviceReader::processDevice() {
    qDebug()<<"Processing a Device";

    QList<TwobTechDevice> deviceList;
    TwobTechDevice twobTechDevice;
    //get name of device and port
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (attr.name().toString() == QLatin1String("name")) {

            twobTechDevice.device_name = attr.value().toString();
            qDebug()<<"Found a "<<twobTechDevice.device_name<<" device";
        }else if(attr.name().toString() == QLatin1String("portName")){
            qDebug()<<"Using port:"<<attr.value().toString();
        }
    }

    xml.readNextStartElement();     //skip dataformat
    //now find all dataItems
    processDataItems(&twobTechDevice);
    deviceList.append(twobTechDevice);
    qDebug()<<"Done processing a device";
}

void XmlDeviceReader::processDataItems(TwobTechDevice *device){
    qDebug()<<"Processing data Items";
    do{
        xml.readNextStartElement();
        if (xml.isStartElement() && xml.name() == "dataItem"){
            qDebug()<<"Found dataItem";
            processDataItem(device);
        }else{
            qDebug()<<"Skipping element:"<<xml.name().toString();

            //xml.skipCurrentElement();
        }
        //xml.readNextStartElement();
    }while(xml.name()!="device");

    qDebug()<<"Done Processing data items";
}

void XmlDeviceReader::processDataItem(TwobTechDevice *device){
    qDebug()<<"Processing a data Items Attributes:";
    SerialDataItem* serialDataItem = new SerialDataItem();
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (attr.name().toString() == QLatin1String("name")) {
            serialDataItem->setName(attr.value().toString());

            qDebug()<<"With the name:"<<serialDataItem->getName();
        }else if(attr.name().toString() == QLatin1String("type")){

            serialDataItem->setType(attr.value().toString());
            qDebug()<<"And Type:"<<serialDataItem->getType();
        }
    }
    device->data_items.append(*serialDataItem);
    delete serialDataItem;

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
