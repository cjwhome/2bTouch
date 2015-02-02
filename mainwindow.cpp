#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSerial();
    ozone_label = new QLabel("Ozone=");
    ozone_output = new QLabel("0.0");
    ozone_units_label = new QLabel(" ppbv");

    temperature_label = new QLabel("Cell Temp=");
    temperature_output = new QLabel("0.0");
    temperature_units_label = new QLabel(" C");

    pressure_label = new QLabel("Cell Press=");
    pressure_output = new QLabel("0.0");
    pressure_units_label = new QLabel(" mBar");

    current_time = new QLabel();
    current_time_label = new QLabel("Time:");

    QWidget *centralWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPixmap configPixmap(":/pics/buttons/config.jpg");
    QIcon configButtonIcon(configPixmap);

    QPushButton *configure_button = new QPushButton();
    configure_button->setIcon(configButtonIcon);
    configure_button->setIconSize(QSize(180,160));
    configure_button->setFixedSize(180,160);

    QGridLayout *gridLayout = new QGridLayout();

    gridLayout->addWidget(ozone_label,0,0,1,1,0);
    gridLayout->addWidget(ozone_output,0,1,1,1,0);
    gridLayout->addWidget(ozone_units_label,0,2,1,1,0);

    gridLayout->addWidget(temperature_label,1,0,1,1,0);
    gridLayout->addWidget(temperature_output,1,1,1,1,0);
    gridLayout->addWidget(temperature_units_label,1,2,1,1,0);

    gridLayout->addWidget(pressure_label,2,0,1,1,0);
    gridLayout->addWidget(pressure_output,2,1,1,1,0);
    gridLayout->addWidget(pressure_units_label,2,2,1,1,0);

    gridLayout->addWidget(current_time_label,3,0,1,1,0);
    gridLayout->addWidget(current_time,3,2,1,1,0);

    horizontalLayout->addLayout(gridLayout);
    //horizontalLayout->setSpacing(35);
    centralWidget->setLayout(horizontalLayout);
    setCentralWidget(centralWidget);

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



    serialPort = new QSerialPort();
    serialPort->setPortName("ttyACM0");
    s_serialThread = new SerialThread();

    if(!s_serialThread->startSerial(serialPort))
        qDebug()<<"Unable to start serial thread";
    if (!s_serialThread) {
        QMessageBox::warning(this, "2BTouch", "Error allocating serial thread", QMessageBox::Ok);
        return;
    }

    connect(s_serialThread, SIGNAL(newDataLine(QString)), this, SLOT(newDataLine(QString)), Qt::DirectConnection);
}

void MainWindow::newDataLine(QString dLine){
    qDebug()<<dLine;
    parseDataLine(dLine);

}

void MainWindow::parseDataLine(QString dLine){
    QStringList fields;
    QDateTime *tempDateTime;
    fields = dLine.split(QRegExp(","));
    if(fields.length()==NUMBER_OF_COLUMNS){
        current_ozone = fields[OZONE_COLUMN].toDouble();
        current_temp = fields[TEMPERATURE_COLUMN].toDouble();
        current_press = fields[PRESSURE_COLUMN].toDouble();
        qDebug()<<"Time"<<fields[TIME_COLUMN];
        tempDateTime = QDateTime::fromString(fields[DATE_COLUMN]+fields[TIME_COLUMN], "dd/MM/yyhh:mm:ss");
        qDebug()<<"Converted time: "<<tempDateTime.toString();
        ozone_output->setText(QString::number(current_ozone));
        temperature_output->setText(QString::number(current_temp));
        pressure_output->setText(QString::number(current_press));
        current_time->setText(tempDateTime.toString());

    }else{
        qDebug()<<"Incomplete line: "<<fields.length()<<" columns.";
    }
}
