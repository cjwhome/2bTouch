#include <QDebug>
#include "filewriter.h"


FileWriter::FileWriter()
{

}

QString FileWriter::getUsbPath() const
{
    return usbPath;
}

void FileWriter::setUsbPath(const QString &value)
{
    usbPath = value;
}

void FileWriter::writeHeader()
{

}

void FileWriter::appendRow()
{

}

bool FileWriter::checkIfUsbMounted(){
    QString prog = "/bin/bash";//shell
    QStringList arguments;


    arguments << "-c" << "mount | grep media";
    QProcess *process = new QProcess();
    process->start(prog , arguments);
    process->waitForFinished();

    QString mount_status = process->readAll();
    qDebug()<<"mount command return: "<<mount_status;
    if(mount_status.contains("usb")){
            //separate string into sub strings by spaces and find string that has "media" in it

            QStringList stringList = mount_status.split(" ");
            for(int i=0;i<stringList.size();i++){
                if(stringList[i].contains("usb")){
                    this->setUsbPath(stringList[i]);
                    qDebug()<<"Found device located at: "<<getUsbPath()<<" after usbdevice string";
                    return true;
                }
            }
    }else{
        qDebug()<<"Couldn't find a mounted usb.";
        return false;
    }//

}


bool FileWriter::createDataFolder(QString deviceName){

    if(checkIfUsbMounted()){
        full_data_path = usbPath + "/" + deviceName;
        qDebug()<<"Full data path is:"<<full_data_path;
        //QDir dir(full_data_path);
        if(!QDir(full_data_path).exists()){
            if(!QDir().mkdir(full_data_path)){
                qDebug()<<"Tried but could not make base data folder";
                return false;
            }
        }
        full_data_path += "/";
        if(!QDir(full_data_path).exists()){
            if(!QDir().mkdir(full_data_path)){
                qDebug()<<"Tried but could not make mode folder";
                return false;
            }
        }

        return true;
    }else
        return false;
}
