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

    /*qDebug()<<"After processing devices here is the qlist:";
    for(int i=0;i<deviceList.size();i++){
        TwobTechDevice outputDevice = (deviceList.at(i));
        qDebug()<<"Device name:"<<outputDevice.device_name;
        for(int a=0;a<outputDevice.data_items.size();a++){
            SerialDataItem outputItem = outputDevice.data_items.at(a);
            qDebug()<<"dataItem name:"<<outputItem.getName()<<" and type:"<<outputItem.getType();
            //delete &outputItem;
        }
        //delete &outputDevice;
    }*/

    if (xml.tokenType() == QXmlStreamReader::Invalid)
        xml.readNext();

    if (xml.hasError()) {
        xml.raiseError();
        qDebug() << errorString();
    }
}

void XmlDeviceReader::processDevices() {
    qDebug()<<"Processing devices";

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

    //QList<TwobTechDevice> deviceList;
    TwobTechDevice twobTechDevice;
    //get name of device and port
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (attr.name().toString() == QLatin1String("name")) {

            twobTechDevice.device_name = attr.value().toString();
            qDebug()<<"Found a "<<twobTechDevice.device_name<<" device";
        }else if(attr.name().toString() == QLatin1String("portName")){
            qDebug()<<"Using port:"<<attr.value().toString();
            twobTechDevice.setCom_port(attr.value().toString());
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
        }
    }while(xml.name()!="device");



}

void XmlDeviceReader::processDataItem(TwobTechDevice *device){
    qDebug()<<"Processing a data Items Attributes:";
    SerialDataItem* serialDataItem = new SerialDataItem();
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (attr.name().toString() == QLatin1String("name")) {
            serialDataItem->setName(attr.value().toString());

            qDebug()<<"With the name:"<<serialDataItem->getName();
        }else if(attr.name().toString() == QLatin1String("type")){

            QString typeString = attr.value().toString();



        }else if(attr.name().toString() == QLatin1String("units")){
            serialDataItem->setUnits(attr.value().toString());
        }else if(attr.name().toString() == QLatin1String("priority")){
            serialDataItem->setPriority(attr.value().toDouble());
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

QList<TwobTechDevice> XmlDeviceReader::getDeviceList() const
{
    return deviceList;
}

TwobTechDevice XmlDeviceReader::getADevice(int element_number){
    return deviceList.at(element_number);
}


