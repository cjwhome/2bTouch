#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent) : QObject(parent)
{
    int length = QSerialPortInfo::availablePorts().length();
    if(!(length > 0)) {

    }
    serial.setPort(QSerialPortInfo::availablePorts().at(0));

    xmlDeviceReader = new XmlDeviceReader(":/deviceConfig.xml");
    xmlDeviceReader->read();
    TwobTechDevice device = xmlDeviceReader->deviceByPort(serial.portName());

    serial.setBaudRate(device.getBaud_rate());
}
