#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSerial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSerial(){
    // in here is where we determine which serial port to use -
    //TODO: check each port description for the ccs string and use that if it is the POM or 106
    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
    }*/
    // Example use QSerialPort
    qDebug()<<"Setting Up Serial";

    serialPort = new QSerialPort();
    serialPort->setPortName("ttyACM0");
    qDebug()<<"Here";
    //if (!s_serialThread) {
        s_serialThread = new SerialThread();
        qDebug()<<"Creating new Serial Thread";
        if(!s_serialThread->startSerial(serialPort))
            qDebug()<<"Unable to start serial thread";
        if (!s_serialThread) {
            QMessageBox::warning(this, "2BTouch", "Error allocating serial thread", QMessageBox::Ok);
            return;
        }
    //}


    connect(s_serialThread, SIGNAL(newDataLine(QString)), this, SLOT(newDataLine(QString)), Qt::DirectConnection);

}

void MainWindow::newDataLine(QString dLine){
    qDebug()<<"New Data line: "<<dLine;

}
