#include "serialhandler.h"

SerialHandler::SerialHandler(QThread *thr, QObject *parent) : QObject(parent) {
    thread = thr;
    //this->moveToThread(thread);

    configSerialPort();
    currentConnectionType = SerialHandler::Inactive;
}

void SerialHandler::writeSync(QString *dat) {
    currentConnectionType = SerialHandler::Synchronously;
    data = dat;
    syncIndex = 0;
    serialPort->write(QString("<").toLatin1().toStdString().c_str(), 1);
}

void SerialHandler::writeAsync(QString *dat) {
    currentConnectionType = SerialHandler::Asynchronously;
    data = dat;
    serialPort->write(data->toLatin1().toStdString().c_str(), data->length());
    currentConnectionType = (SerialHandler::Finished);
}

void SerialHandler::configSerialPort() {
    serialPort = new QSerialPort();

    reader = new XmlDeviceReader(":/deviceConfig.xml");
    reader->read();

    device = reader->getADevice(4);
    portName = device.getCom_port();
    baudRate = device.getBaud_rate();

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug()<<"Setup Serial Port successfully";
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(dataReady()));
    }else{
        qDebug()<<"Error setting up serial port";
    }

}

void SerialHandler::dataReady() {
    if(serialPort->canReadLine()) {
        QByteArray retData = serialPort->readAll();
        QList<QByteArray> list = retData.split('\n');
        for(int i = 0; i < list.length(); i++) {
            QString line = QString(list.at(i));
            qDebug()<<"Received new line from serial: "<<line;
            if(currentConnectionType == SerialHandler::Synchronously) {
                handleSyncData(QString(line));
            } else {
                emit dataAvailable(line);
            }
        }
    }
}

void SerialHandler::handleSyncData(QString retData) {
    if((retData == "n") || (retData == "Starting string")) {
        if(syncIndex < (data->size())) {
            serialPort->write(QString(data->at(syncIndex)).toLatin1().toStdString().c_str(), 1);
            syncIndex++;
        } else {
            serialPort->write(QString(">").toLatin1().toStdString().c_str(), 1);
            currentConnectionType = SerialHandler::Finished;
            qDebug()<<"Finished Sync Write";
        }
    } else {
        emit dataAvailable(retData);
    }
}
