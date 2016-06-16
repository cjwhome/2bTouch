#include "serialthread.h"

bool SerialThread::startSerial(QSerialPort *port)
{

    s_port = port;
    s_stop = false;

    if (!s_port->open(QIODevice::ReadWrite)){
        qDebug()<<"Couldn't open serial port";
        return false;
    }



    start(QThread::TimeCriticalPriority);

	return true;
}

void SerialThread::stopSerial()
{    
    s_stop = true;
}

void SerialThread::run()
{
    QByteArray tmp;
    QSerialPort::SerialPortError error;

    while (!s_stop) {
        while(!s_port->canReadLine()){
            msleep(10);
        }
        tmp = s_port->readAll();

        s_port->flush();
        s_port->clear();
        emit newDataLine(QString(tmp));			//signal connected to
	}

    //stop_serial();      //if the port is closed, stop the thread
}

