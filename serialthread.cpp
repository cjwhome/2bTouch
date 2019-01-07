#include "serialthread.h"

bool SerialThread::startSerial(QSerialPort *port){
    s_port = port;
    s_stop = false;
    if (!s_port->open(QIODevice::ReadWrite)){
        qDebug()<<"Couldn't open serial port";
        return false;
    }
    start(QThread::TimeCriticalPriority);
    return true;
}

void SerialThread::stopSerial(){
    s_stop = true;
}

//Reads in the input from the pcb through a serial connection
//This does not currently run
void SerialThread::run(){
    qDebug() << "Is this the working thread";
    QByteArray tmp;
    while (!s_stop) {
        while(!s_port->canReadLine()){
            msleep(100);
        }
        qDebug()<<"Can read line in thread";
        tmp = s_port->readAll();
        s_port->flush();
        s_port->clear();
        emit newDataLine(QString(tmp));
    }
}
