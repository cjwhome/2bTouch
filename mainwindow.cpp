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

    current_date = new QLabel();

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

    QPixmap graphPixmap(":/buttons/pics/graph.jpg");
    QIcon graphButtonIcon(graphPixmap);

    graph_button = new QPushButton("Graph");
    //graph_button->setIcon(graphButtonIcon);
    //graph_button->setIconSize(QSize(70,62));
    graph_button->setFixedSize(70,62);

    QPushButton *avg_button = new QPushButton("Stats");
    //avg_button->setIcon(graphButtonIcon);
    //avg_button->setIconSize(QSize(70,62));
    avg_button->setFixedSize(70,62);

    QGridLayout *gridLayout = new QGridLayout();

    //gridLayout->addWidget(ozone_label,0,0,1,1,0);
    //gridLayout->addWidget(ozone_output,0,1,1,1,0);
    //gridLayout->addWidget(ozone_units_label,0,2,1,1,0);

    /*gridLayout->addWidget(temperature_label,0,0,1,1,0);
    gridLayout->addWidget(temperature_output,0,1,1,1,0);
    gridLayout->addWidget(temperature_units_label,0,2,1,1,0);

    gridLayout->addWidget(pressure_label,1,0,1,1,0);
    gridLayout->addWidget(pressure_output,1,1,1,1,0);
    gridLayout->addWidget(pressure_units_label,1,2,1,1,0);*/

    //gridLayout->addWidget(current_time_label,3,0,1,1,0);
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
    // generate some data:
    //x(101);
    //y(101);

    ozoneDisplay->setFixedSize(300, 145);
	ozoneDisplay->setDigitCount(7);
	ozoneDisplay->display("0.0 ppb");
    ozoneDisplay->setFrameStyle(QFrame::NoFrame);
	
	
    data_point = 0;
	start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read

    /*customPlot = new QCustomPlot();
    // create graph and assign data to it:
    customPlot->addGraph();

    


    horizontalLayout->addWidget(myFrame);
    horizontalLayout->addWidget(customPlot);*/
    //horizontalLayout->setSpacing(35);
    centralWidget->setLayout(horizontalLayout);
    setCentralWidget(centralWidget);
    /*for (int i=0; i<101; ++i)
    {
      x[i] = i; // x goes from -1 to 1
      y[i] = i; // let's plot a quadratic function


    }
    customPlot->graph(0)->setData(x, y);
    customPlot->replot();*/
    
    //connect(this, signal(graph_button), this, slot(displayBigPlot));

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
    serialPort->setBaudRate(9600);
    s_serialThread = new SerialThread();

    if(!s_serialThread->startSerial(serialPort))
        qDebug()<<"Unable to start serial thread";
    if (!s_serialThread) {
        QMessageBox::warning(this, "2BTouch", "Error allocating serial thread", QMessageBox::Ok);
        return;
    }

    connect(s_serialThread, SIGNAL(newDataLine(QString)), this, SLOT(newDataLine(QString)), Qt::DirectConnection);
    //connect(this, SIGNAL(readyToPlot()), this, SLOT(rePlot()));
}

void MainWindow::newDataLine(QString dLine){
    qDebug()<<dLine;
    parseDataLine(dLine);

}

void MainWindow::parseDataLine(QString dLine){
    QStringList fields;
    QVector<double> t,u;
	QDateTime tempDateTime;
	double current_seconds;
	double ellapsed_seconds;

	dLine.remove(QRegExp("[\\n\\t\\r]"));
    fields = dLine.split(QRegExp(","));
    if(fields.length()==NUMBER_OF_COLUMNS){
        current_ozone = fields[OZONE_COLUMN].toDouble();
        current_temp = fields[TEMPERATURE_COLUMN].toDouble();
        current_press = fields[PRESSURE_COLUMN].toDouble();
        
		
		
        tempDateTime = QDateTime::fromString(fields[DATE_COLUMN]+fields[TIME_COLUMN], "dd/MM/yyhh:mm:ss");
		tempDateTime = tempDateTime.addYears(100);			//for some reason, it assumes the date is 19XX instead of 20XX
		current_seconds = tempDateTime.toTime_t();			//convert to seconds;
		if(start_time_seconds > current_seconds)
			start_time_seconds = current_seconds;
		ellapsed_seconds = current_seconds - start_time_seconds;
        qDebug()<<"Converted time: "<<tempDateTime.toString();
		qDebug()<<"Ellapsed time: "<<ellapsed_seconds;
		
		
		
        //ozone_output->setText(QString::number(current_ozone));
		ozoneDisplay->display(QString::number(current_ozone)+" ppb");
        temperature_output->setText(QString::number(current_temp));
        pressure_output->setText(QString::number(current_press));
        current_time->setText(fields[TIME_COLUMN]);
        current_date->setText(fields[DATE_COLUMN]);

        /*x.insert(data_point,data_point);
        y.insert(data_point,current_ozone);
        t=x;                    //copy the vectors to order them to get high and low for range
        u=y;
        data_point++;

        customPlot->xAxis->setRange(0, t.size());
        customPlot->graph(0)->setData(x, y);
		
		// give the axes some labels:
	    customPlot->xAxis->setLabel("Time");
		//customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
		customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
		customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
	    customPlot->yAxis->setLabel("Ozone (ppb)");
	    // set axes ranges, so we see all data:
	    //customPlot->xAxis->setRange(0, 100);
		std::sort(u.begin(),u.end());
		//int highest_value;
		//qDebug()<<"Max value is:"<<u.last();
	    customPlot->yAxis->setRange(u.first()-1, u.last()+1);

        emit readyToPlot();*/
        


    }else{
        qDebug()<<"Incomplete line: "<<fields.length()<<" columns.";
    }
}

void MainWindow::rePlot(void){
	customPlot->replot();
}

void MainWindow::displayBigPlot(void){
    
}
 
/*bool MainWindow::yLessThan(const int &p1, const int &p2){
	return p1()<p2();
}*/
