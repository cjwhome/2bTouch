#include "mainwindow.h"
#include "ui_mainwindow.h"
class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QWidget *centralWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
	QVBoxLayout *measurementDisplayLayoutArea = new QVBoxLayout();
    current_time = new QLabel();
    current_date = new QLabel();
	
    mainDisplay = new QLCDNumber();


    //add the separator line:
    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::VLine);

    QPixmap configPixmap(":/buttons/pics/config.jpg");
    QIcon configButtonIcon(configPixmap);

    QPushButton *configure_button = new QPushButton();
    configure_button->setIcon(configButtonIcon);
    configure_button->setIconSize(QSize(70,62));
    configure_button->setFixedSize(70,62);


    //QPixmap graphPixmap(":/buttons/pics/graph.jpg");
    //QIcon graphButtonIcon(graphPixmap);

    graph_button = new QPushButton("Graph");
    //graph_button->setIcon(graphButtonIcon);
    //graph_button->setIconSize(QSize(70,62));
    graph_button->setFixedSize(70,62);

    connect(graph_button, SIGNAL(clicked()), this, SLOT(displayBigPlot()));

    QPushButton *avg_button = new QPushButton("Stats");
    //avg_button->setIcon(graphButtonIcon);
    //avg_button->setIconSize(QSize(70,62));
    avg_button->setFixedSize(70,62);

    QGridLayout *gridLayout = new QGridLayout();


    QFont labelFont("Arial", 18, QFont::Bold);
    current_time->setFont(labelFont);
    current_date->setFont(labelFont);
    gridLayout->addWidget(current_time,2,1,1,1,0);
    gridLayout->addWidget(current_date,2,2,1,1,0);


    buttonLayout->addWidget(configure_button);
    buttonLayout->addWidget(graph_button);
    buttonLayout->addWidget(avg_button);
    horizontalLayout->addLayout(buttonLayout);
    horizontalLayout->addWidget(myFrame);
    measurementDisplayLayoutArea->addWidget(mainDisplay);
	measurementDisplayLayoutArea->addLayout(gridLayout);
    horizontalLayout->addLayout(measurementDisplayLayoutArea);


    mainDisplay->setFixedSize(300, 100);
    mainDisplay->setDigitCount(10);
    mainDisplay->display("0.0 PPB");
    mainDisplay->setFrameStyle(QFrame::NoFrame);

	
    data_point = 0;
	start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read

    centralWidget->setLayout(horizontalLayout);
    setCentralWidget(centralWidget);

    displayGraph = new DisplayGraph();
    displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //connect(this, SIGNAL(validDataReady()), displayGraph, SLOT(blah()));
    connect(displayGraph, SIGNAL(userClearedPlot()), this, SLOT(clearPlotData()));

    xmlDeviceReader = new XmlDeviceReader(":/deviceConfig.xml");
    xmlDeviceReader->read();

    createDevice();
    setupSerial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//build a device from the xml and prepare place to put the data
void MainWindow::createDevice(){
    int i;
    twobTechDevice = xmlDeviceReader->getADevice(1);

    deviceProfile.setDevice_name(twobTechDevice.device_name);
    qDebug()<<"Device Profile name: "<<deviceProfile.getDevice_name();

    //determine the index of elements
    for(i=0;i<twobTechDevice.data_items.size();i++){
        SerialDataItem serialDataItem = twobTechDevice.data_items.at(i);
        if(serialDataItem.getName() == "Date")
            deviceProfile.setDate_position(i);
        else if(serialDataItem.getName()=="Time")
            deviceProfile.setTime_position(i);
        else if(serialDataItem.getPriority()==0){
            deviceProfile.setMain_display_position(i);
            deviceProfile.setMain_display_units(serialDataItem.getUnits());
        }

    }
    deviceProfile.setNumber_of_columns(i);
    qDebug()<<"Number of columns:"<<deviceProfile.getNumber_of_columns();

}

void MainWindow::setupSerial(){
    // in here is where we determine which serial port to use -
    //TODO: check each port description for the ccs string and use that if it is the POM or 106
	serialPort = new QSerialPort();
    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
		if(!QString::compare(info.manufacturer(), "Microchip Technology, Inc.", Qt::CaseInsensitive)){  // if strings are equal x should return 0
			serialPort = new QSerialPort(info.portName());
		}
    }*/

    serialPort->setPortName("ttyAMA0");

    serialPort->setBaudRate(9600, QSerialPort::AllDirections);
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
    //qDebug()<<"New Line: "<<dLine;

    if(parseDataLine(dLine)){
        //displayGraph->setData(x, y);
        emit validDataReady();
    }
}



bool MainWindow::parseDataLine(QString dLine){
    QStringList fields;
    QVector<double> t,u;
	QDateTime tempDateTime;
	double current_seconds;
    double ellapsed_seconds;

    dLine.remove(QRegExp("[\\n\\t\\r]"));
    qDebug()<<dLine;
    fields = dLine.split(QRegExp(","));
    if(fields.length()==deviceProfile.getNumber_of_columns()){
        QList<SerialDataItem> parsedDataRecord;       //create an list of parsed data to append to the list of all parsed records
        for(int a=0;a<deviceProfile.getNumber_of_columns();a++){
            SerialDataItem serialDataItem;
            if(a==deviceProfile.getDate_position())
                serialDataItem.setDate(QDateTime::fromString(fields[deviceProfile.getDate_position()], "dd/MM/yy"));
            else if(a == deviceProfile.getTime_position())
                serialDataItem.setTime(QDateTime::fromString(fields[deviceProfile.getTime_position()], "hh:mm:ss"));
            serialDataItem.setDvalue(fields[a].toDouble());
            parsedDataRecord.append(serialDataItem);
        }

        if(allParsedRecordsList.size()<MAXIMUM_PARSED_DATA_RECORDS)
            allParsedRecordsList.append(parsedDataRecord);
        else
            qDebug()<<"Maxed out the qlist size, here is where we can close off the file and start a new one";

        //tempDateTime = QDateTime::fromString(fields[DATE_COLUMN]+fields[TIME_COLUMN], "dd/MM/yyhh:mm:ss");
        //tempDateTime = tempDateTime.addYears(100);			//for some reason, it assumes the date is 19XX instead of 20XX
        //current_seconds = tempDateTime.toTime_t();			//convert to seconds;
        //if(start_time_seconds > current_seconds)
        //	start_time_seconds = current_seconds;
        //ellapsed_seconds = current_seconds - start_time_seconds;

        mainDisplay->display(QString::number(main_display_value)+" " + deviceProfile.getMain_display_units());

        current_time->setText(fields[deviceProfile.getTime_position()]);
        current_date->setText(fields[deviceProfile.getDate_position()]);

        //x.insert(data_point,data_point);
        //y.insert(data_point,current_ozone);
        //t=x;                    //copy the vectors to order them to get high and low for range
        //u=y;
        //data_point++;

        return true;


    }else{
        qDebug()<<"Incomplete line: "<<fields.length()<<" columns.";
        return false;
    }
}



void MainWindow::displayBigPlot(void){
    //displayGraph = new DisplayGraph();
    //displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    displayGraph->setData(x, y);
    displayGraph->drawPlot();
    displayGraph->show();
}
 
void MainWindow::clearPlotData(void){
    //qDebug()<<"Clearing plot data, xcount:"<<x.count()<<", ycount:"<<y.count();
    data_point = 0;
    x.clear();
    y.clear();
}

/*bool MainWindow::yLessThan(const int &p1, const int &p2){
	return p1()<p2();
}*/
