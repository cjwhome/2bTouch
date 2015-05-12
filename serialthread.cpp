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

    while (!s_stop) {
        tmp = s_port->readLine();

        if(!tmp.size()){

            msleep(500);
            continue;
		}

        emit newDataLine(QString(tmp));			//signal connected to


	}

    //stop_serial();      //if the port is closed, stop the thread
}
