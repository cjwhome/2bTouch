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
	

    setupSerial();

    QWidget *centralWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
	QVBoxLayout *measurementDisplayLayoutArea = new QVBoxLayout();
	
	ozoneDisplay = new QLCDNumber();	
		

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
	measurementDisplayLayoutArea->addWidget(ozoneDisplay);
	measurementDisplayLayoutArea->addLayout(gridLayout);
    horizontalLayout->addLayout(measurementDisplayLayoutArea);


    ozoneDisplay->setFixedSize(350, 145);
    ozoneDisplay->setDigitCount(10);
    ozoneDisplay->display("0.0 PPB");
    ozoneDisplay->setFrameStyle(QFrame::NoFrame);
	
	
    data_point = 0;
	start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read

    centralWidget->setLayout(horizontalLayout);
    setCentralWidget(centralWidget);

    displayGraph = new DisplayGraph();
    displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(this, SIGNAL(validDataReady()), displayGraph, SLOT(blah()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    //serialPort->setBaudRate(19200,QSerialPort::AllDirections);
    //serialPort->setBaudRate(115200);
    serialPort->setBaudRate(9600);
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
    //qDebug()<<dLine;

    if(parseDataLine(dLine)){
        displayGraph->setData(x, y);
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
    if(fields.length()==NUMBER_OF_COLUMNS){
        current_ozone = fields[OZONE_COLUMN].toDouble();
        current_temp = fields[TEMPERATURE_COLUMN].toDouble();
        current_press = fields[PRESSURE_COLUMN].toDouble();
        
		
        //qDebug()<<"Date size:"<<fields[DATE_COLUMN].size()<<" time size:"<<fields[TIME_COLUMN].size();
        tempDateTime = QDateTime::fromString(fields[DATE_COLUMN]+fields[TIME_COLUMN], "dd/MM/yyhh:mm:ss");
		tempDateTime = tempDateTime.addYears(100);			//for some reason, it assumes the date is 19XX instead of 20XX
		current_seconds = tempDateTime.toTime_t();			//convert to seconds;
		if(start_time_seconds > current_seconds)
			start_time_seconds = current_seconds;
		ellapsed_seconds = current_seconds - start_time_seconds;
        //qDebug()<<"Converted time: "<<tempDateTime.toString();
        //qDebug()<<"Ellapsed time: "<<ellapsed_seconds;
		
        //ozone_output->setText(QString::number(current_ozone));
        /*if(current_ozone >= 1000 || current_ozone <= -1000)
            ozoneDisplay->setDigitCount(10);
        else if(current_ozone >= 100 || current_ozone <= -100)
            ozoneDisplay->setDigitCount(9);
        else if(current_ozone >= 10 || current_ozone <= -10)
            ozoneDisplay->setDigitCount(8);
        else
            ozoneDisplay->setDigitCount(7);*/
        ozoneDisplay->display(QString::number(current_ozone)+" PPB");
        temperature_output->setText(QString::number(current_temp));
        pressure_output->setText(QString::number(current_press));
        current_time->setText(fields[TIME_COLUMN]);
        current_date->setText(fields[DATE_COLUMN]);

        x.insert(data_point,data_point);
        y.insert(data_point,current_ozone);
        t=x;                    //copy the vectors to order them to get high and low for range
        u=y;
        data_point++;

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
 
/*bool MainWindow::yLessThan(const int &p1, const int &p2){
	return p1()<p2();
}*/
