#include "filewriter.h"

FileWriter::FileWriter(){}

QString FileWriter::getUsbPath() const{
    return usbPath;
}

void FileWriter::setUsbPath(const QString &value){
    usbPath = value;
}

//This checks to see if there is a usb present
//This works by calling bash and reading all media devices, returns true is a usb is present, false otherwise
bool FileWriter::checkIfUsbMounted(){
    QString prog = "/bin/bash";//shell
    QStringList arguments;

    arguments << "-c" << "mount | grep media";
    QProcess *process = new QProcess();
    process->start(prog , arguments);
    process->waitForFinished();

    QString mount_status = process->readAll();
    //qDebug()<<"mount command return: "<<mount_status;
    if(mount_status.contains("usb")||mount_status.contains("/dev/sd")){
            //separate string into sub strings by spaces and find string that has "media" in it
            QStringList stringList = mount_status.split(" ");
            for(int i=0;i<stringList.size();i++){
                if(stringList[i].contains("usb0")){     //if a usb stick is on a linux pc
                    this->setUsbPath(stringList[i]);
                    //qDebug()<<"Found device located at: "<<getUsbPath()<<" after usbdevice string";
                    return true;
                }else if(stringList[i].contains("/media")){     //if a usb stick is in the armadillo board
                    this->setUsbPath((stringList[i]));
                    //qDebug()<<"Found device located at: "<<getUsbPath()<<" after /dev/ string";
                    return true;
                }
            }
    }else{
        //qDebug()<<"Couldn't find a mounted usb.";
        return false;
    }
    return false;
}

//This makes sure that the folder that the program writes to is present on the usb and if not it attempts to create it
//Returns true if folder exsits, false otherwise
bool FileWriter::createDataFolder(QString deviceName){
    if(checkIfUsbMounted()){
        full_data_path = usbPath + "/" + deviceName;
        //qDebug()<<"USB Full data path is:"<<full_data_path;
        //QDir dir(full_data_path);
        if(!QDir(full_data_path).exists()){
            if(!QDir().mkdir(full_data_path)){
                //qDebug()<<"Tried but could not make base data folder";
                return false;
            }
        }
        full_data_path += "/";
        if(!QDir(full_data_path).exists()){
            if(!QDir().mkdir(full_data_path)){
                //qDebug()<<"Tried but could not make usb device folder";
                return false;
            }
        }

        return true;
    }else{
        full_data_path = "~/" + deviceName;
        //qDebug()<<"Local Full data path is:"<<full_data_path;
        //QDir dir(full_data_path);
        if(!QDir(full_data_path).exists())
        {
            if(!QDir().mkdir(full_data_path))
            {
                //qDebug()<<"Tried but could not make base data folder";
                return false;
            }
        }
        full_data_path += "/";
        if(!QDir(full_data_path).exists())
        {
            if(!QDir().mkdir(full_data_path))
            {
                //qDebug()<<"Tried but could not make local device folder";
                return false;
            }
        }
        return true;
    }
}

QString FileWriter::getFull_data_path() const{
    return full_data_path;
}

void FileWriter::setFull_data_path(const QString &value){
    full_data_path = value;
}
