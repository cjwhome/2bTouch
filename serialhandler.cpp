#include "serialhandler.h"

SerialHandler::SerialHandler(QThread *thr, QObject *parent) : QObject(parent) {
    thread = thr;
    //this->moveToThread(thread);

    settings = new QSettings("2B Technologies", "2B Touch");
    gettingSettings = false;

    configSerialPort();
    currentConnectionType = SerialHandler::Inactive;
}

void SerialHandler::writeSync(QString *dat) {
    dataList<<dat;
    if(currentConnectionType == SerialHandler::Synchronously) {
        qDebug()<<"Data operation already in process, adding to queue";
    } else {
        currentConnectionType = SerialHandler::Synchronously;
        data = dat;
        syncIndex = 0;
        serialPort->write(QString("<").toLatin1().toStdString().c_str(), 1);
    }
}

void SerialHandler::writeAsync(QString *dat) {
    currentConnectionType = SerialHandler::Asynchronously;
    data = dat;
    serialPort->write(dat->toLatin1().toStdString().c_str(), dat->length());
    currentConnectionType = (SerialHandler::Finished);
}

void SerialHandler::writeChar(char c) {
    const char *d = &c;
    serialPort->write(d);
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
            } else if(line == "Settings") {
                gettingSettings = true;
            } else if(gettingSettings) {
                qDebug()<<"Getting Settigns";
                gettingSettings = false;
                QStringList settingsList = line.split(",");
                settings->setValue("Raw Settings String", line);
                settings->setValue("Zero", settingsList.at(0));
                settings->setValue("Avg", settingsList.at(1));
                settings->setValue("Slope", settingsList.at(2));
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
            checkQueue();
        }
    } else if(retData == "Settings") {
        gettingSettings = true;
    } else if(gettingSettings) {
        qDebug()<<"Getting Settigns";
        gettingSettings = false;
        QStringList settingsList = retData.split(",");
        settings->setValue("Raw Settings String", retData);
        settings->setValue("Zero", settingsList.at(0));
        settings->setValue("Avg", settingsList.at(1));
        settings->setValue("Slope", settingsList.at(2));
    } else {
        emit dataAvailable(retData);
    }
}

void SerialHandler::checkQueue() {
    int index = dataList.indexOf(data);
    if((index+1) != dataList.size()) {
        currentConnectionType = SerialHandler::Synchronously;
        data = dataList.at(index+1);
        syncIndex = 0;
        serialPort->write(QString("<").toLatin1().toStdString().c_str(), 1);
    }
}
