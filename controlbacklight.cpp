#include "controlbacklight.h"

ControlBacklight::ControlBacklight()
{

}

void ControlBacklight::setPercentage(int percentage){
    //echo 80  >  /sys/class/backlight/gpio-backlight.0/brightness
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QString command;
    command = "echo " + QString::number(percentage) + " > /sys/class/backlight/gpio-backlight.0/brightness";
    qDebug()<<"command:"<<command;

    arguments << "-c" << command;
    qDebug()<<"arguments1:"<<arguments.at(0)<<" "<<arguments.at(1);
    arguments << "-c" << "echo 80  >  /sys/class/backlight/gpio-backlight.0/brightness";
    qDebug()<<"arguments2:"<<arguments.at(0)<<" "<<arguments.at(1);
    QProcess *process = new QProcess();
    process->start(prog , arguments);
    process->waitForFinished();

    QString bl_status = process->readAll();
}

