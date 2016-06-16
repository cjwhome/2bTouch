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

    started_file = false;
    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons
    //ControlBacklight controlBacklight;
    //controlBacklight.setPercentage(100);
    //listFonts();

    QWidget *centralWidget = new QWidget();

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *topTimeLayout = new QHBoxLayout();
    QHBoxLayout *mainDisplayLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
	QVBoxLayout *measurementDisplayLayoutArea = new QVBoxLayout();
    current_time = new QLabel();
    current_date = new QLabel();
    main_label = new QLabel();
    main_units_label = new QLabel();

    main_measurement_display = new QLabel();

    //add the separator line:

    QFrame* horizontalFrame = new QFrame();
    horizontalFrame->setFrameShape(QFrame::HLine);

    QPixmap configPixmap(":/buttons/pics/settings-icon.gif");
    QIcon configButtonIcon(configPixmap);

    QPushButton *configure_button = new QPushButton();
    configure_button->setIcon(configButtonIcon);
    configure_button->setIconSize(QSize(35,31));
    configure_button->setFixedSize(35,31);


    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon-selected.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);


    graph_button = new QPushButton();
    QPixmap chartPixmap(":/buttons/pics/chart-icon.gif");
    QIcon chartButtonIcon(chartPixmap);

    graph_button->setIcon(chartButtonIcon);
    graph_button->setIconSize(QSize(35,31));
    graph_button->setFixedSize(35,31);

    connect(graph_button, SIGNAL(clicked()), this, SLOT(displayBigPlot()));

    QPushButton *stats_button = new QPushButton();
    QPixmap statsPixmap(":/buttons/pics/stats-icon.gif");
    QIcon statsButtonIcon(statsPixmap);
    stats_button->setIcon(statsButtonIcon);
    stats_button->setIconSize(QSize(35,31));
    stats_button->setFixedSize(35,31);
    QFont labelFont("Cabin", 50, QFont::ForceIntegerMetrics);
    QFont unitsLabelFont("Cabin", 40, QFont::ForceIntegerMetrics);

    QFont timeFont("Cabin", 12, QFont::ForceIntegerMetrics);
    current_time->setFont(timeFont);
    current_date->setFont(timeFont);
    main_label->setFont(labelFont);
    main_label->setStyleSheet("QLabel { color : black; }");
    main_units_label->setFont(unitsLabelFont);
    main_units_label->setStyleSheet("QLabel { color : black; }");
    main_measurement_display->setFont(labelFont);
    main_measurement_display->setStyleSheet("QLabel { color : green; }");
    //main_measurement_display->setFixedWidth(8);

    topTimeLayout->addSpacing(400);
    //topTimeLayout->addWidget(current_date);
    //topTimeLayout->addSpacing(150);
    topTimeLayout->addWidget(current_time);


    //mainDisplayLayout->addSpacerItem(new QSpacerItem(20,1));
    mainDisplayLayout->addWidget(main_label);
    //mainDisplayLayout->addWidget(main_lcd_display);
    mainDisplayLayout->addWidget(main_measurement_display);
    mainDisplayLayout->addWidget(main_units_label);
    mainDisplayLayout->setAlignment(Qt::AlignCenter);
    mainDisplayLayout->setSpacing(5);
    measurementDisplayLayoutArea->addLayout(mainDisplayLayout);
    //measurementDisplayLayoutArea->addWidget(current_time);
    measurementDisplayLayoutArea->setAlignment(Qt::AlignCenter);
    measurementDisplayLayoutArea->setSpacing(50);
    //measurementDisplayLayoutArea->addLayout(gridLayout);
    verticalLayout->addLayout(topTimeLayout);
    verticalLayout->addSpacing(20);
    verticalLayout->addLayout(measurementDisplayLayoutArea);
    verticalLayout->addSpacing(55);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addSpacing(5);
    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(configure_button);
    buttonLayout->addWidget(graph_button);
    buttonLayout->addWidget(stats_button);

    verticalLayout->addLayout(buttonLayout);

	
    data_point = 0;
	start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    displayGraph = new DisplayGraph();
    displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(this, SIGNAL(validDataReady()), displayGraph, SLOT(redrawPlot()));

    connect(displayGraph, SIGNAL(userClearedPlot()), this, SLOT(clearPlotData()));


    //connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    showStats = new ShowStats();
    showStats->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(stats_button, SIGNAL(clicked()), this, SLOT(displayStats()));

    settingsView = new SettingsView();
    settingsView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(configure_button, SIGNAL(clicked()), this, SLOT(displaySettings()));

    xmlDeviceReader = new XmlDeviceReader(":/deviceConfig.xml");
    xmlDeviceReader->read();


    //current_time->setText("8:30:45");
    //current_date->setText("02/17/2016");
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
    twobTechDevice = xmlDeviceReader->getADevice(5);

    deviceProfile.setDevice_name(twobTechDevice.device_name);
    deviceProfile.setCom_port(twobTechDevice.getCom_port());
    deviceProfile.setBaud_rate(twobTechDevice.getBaud_rate());
    //qDebug()<<"Device Profile name: "<<deviceProfile.getDevice_name();
    //qDebug()<<"Device Profile comport: "<<deviceProfile.getCom_port();

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
            deviceProfile.setMain_display_name(serialDataItem.getName());
        }else if(serialDataItem.getPriority()==1){
            deviceProfile.setDiagnosticA_units(serialDataItem.getUnits());
            deviceProfile.setDiagnosticA_name(serialDataItem.getName());
            deviceProfile.setDiagnosticA_position(i);
        }else if(serialDataItem.getPriority()==2){
            deviceProfile.setDiagnosticB_units(serialDataItem.getUnits());
            deviceProfile.setDiagnosticB_name(serialDataItem.getName());
            deviceProfile.setDiagnosticB_position(i);
        }else if(serialDataItem.getPriority()==3){
            deviceProfile.setDiagnosticC_units(serialDataItem.getUnits());
            deviceProfile.setDiagnosticC_name(serialDataItem.getName());
            deviceProfile.setDiagnosticC_position(i);
        }else if(serialDataItem.getPriority()==4){
            deviceProfile.setDiagnosticD_units(serialDataItem.getUnits());
            deviceProfile.setDiagnosticD_name(serialDataItem.getName());
            deviceProfile.setDiagnosticD_position(i);
        }else if(serialDataItem.getPriority()==5){
            deviceProfile.setDiagnosticE_units(serialDataItem.getUnits());
            deviceProfile.setDiagnosticE_name(serialDataItem.getName());
            deviceProfile.setDiagnosticE_position(i);
        }
        //qDebug()<<"For "<<i<<" priority="<<serialDataItem.getPriority();
    }
    deviceProfile.setNumber_of_columns(i);
    //qDebug()<<"Number of columns:"<<deviceProfile.getNumber_of_columns();

}

void MainWindow::setupSerial(){
    // in here is where we determine which serial port to use -
    //TODO: check each port description for the ccs string and use that if it is the POM or 106
    serial = new QSerialPort();
    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
		if(!QString::compare(info.manufacturer(), "Microchip Technology, Inc.", Qt::CaseInsensitive)){  // if strings are equal x should return 0
			serialPort = new QSerialPort(info.portName());
		}
    }*/

    serial->setPortName(deviceProfile.getCom_port());

    serial->setBaudRate(deviceProfile.getBaud_rate(), QSerialPort::AllDirections);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug()<<"Setup Serial Port successfully";
        connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError(QSerialPort::SerialPortError)));
        connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    }else{
        qDebug()<<"Error setting up serial port";
        QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
    /*s_serialThread = new SerialThread();

    if(!s_serialThread->startSerial(serialPort))
        qDebug()<<"Unable to start serial thread";
    if (!s_serialThread) {
        QMessageBox::warning(this, "2BTouch", "Error allocating serial thread", QMessageBox::Ok);
        return;
    }

    connect(s_serialThread, SIGNAL(newDataLine(QString)), this, SLOT(newDataLine(QString)), Qt::DirectConnection);*/

}

void MainWindow::closeSerialPort()
{
    serial->close();
}
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);

}


void MainWindow::readData()
{
    if(serial->canReadLine()){
        QByteArray data = serial->readAll();
        newDataLine(data);
    }
}


void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::newDataLine(QString dLine){
    //qDebug()<<"New Line: "<<dLine;

    if(parseDataLine(dLine)){
        displayGraph->setData(x, y);
        emit validDataReady();
    }
}



bool MainWindow::parseDataLine(QString dLine){
    QStringList fields;
    QVector<double> t,u;
    QDateTime tempDate;

    tempDLine = dLine;

    dLine.remove(QRegExp("[\\n\\t\\r]"));
    qDebug()<<dLine;
    fields = dLine.split(QRegExp(","));
    if(fields.length()==deviceProfile.getNumber_of_columns()){

        QList<SerialDataItem> parsedDataRecord;       //create an list of parsed data to append to the list of all parsed records
        for(int a=0;a<deviceProfile.getNumber_of_columns();a++){
            SerialDataItem serialDataItem;
            if(a!=deviceProfile.getDate_position()||a!=deviceProfile.getTime_position()){
                serialDataItem.setDvalue(fields[a].toDouble());
            }
            parsedDataRecord.append(serialDataItem);
        }

        tempDate = QDateTime::fromString(fields[deviceProfile.getDate_position()]+fields[deviceProfile.getTime_position()], "dd/MM/yyhh:mm:ss");
        if(tempDate.date().year()<2000)
            tempDate = tempDate.addYears(100);      //only if century is not part of the format

        SerialDataItem serialDataItemb;
        serialDataItemb.setDateTime(tempDate);
        parsedDataRecord.insert(deviceProfile.getDate_position(),serialDataItemb);

        if(allParsedRecordsList.size()<MAXIMUM_PARSED_DATA_RECORDS){

            allParsedRecordsList.append(parsedDataRecord);
        }else{

            allParsedRecordsList.removeFirst();
            allParsedRecordsList.append(parsedDataRecord);
            qDebug()<<"Maxed out the qlist size, removing first element and adding";
        }

        x.insert(data_point,data_point);
        y.insert(data_point,parsedDataRecord.at(deviceProfile.getMain_display_position()).getDvalue());
        t=x;                    //copy the vectors to order them to get high and low for range
        u=y;
        data_point++;

        updateDisplay();
        return true;


    }else{
        qDebug()<<"Incomplete line: "<<fields.length()<<" columns.";
        return false;
    }
}

void MainWindow::updateDisplay(void){
    double current_value;

    if(!started_file){
        qDebug()<<"File not started yet, attempting to start file";

        this->createFileName();
    }
    SerialDataItem tempSerialDataItem;
    tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size() -1).at(deviceProfile.getMain_display_position());
    current_value = tempSerialDataItem.getDvalue();
    //main_label->setText(deviceProfile.getMain_display_name()+": ");
    if(deviceProfile.getMain_display_name().contains("3")){
        main_label->setText("O<sub>3</sub>: ");
    }else if(deviceProfile.getMain_display_name().contains("2")){
         main_label->setText("NO<sub>2</sub>: ");
    }
    main_measurement_display->setText(QString::number(current_value));
    main_units_label->setText(" "+deviceProfile.getMain_display_units());

    tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size() -1).at(deviceProfile.getDate_position());

    current_time->setText(tempSerialDataItem.getDateTime().toString("hh:mm"));

    showStats->setData(&allParsedRecordsList, &deviceProfile);
    //showStats->calculateMaxMinMedian(allParsedRecordsList, 0);
    this->writeFile();
    /*if(!y.isEmpty()){
        //displayGraph->setYaxisLabel(deviceProfile.getMain_display_name()+" "+deviceProfile.getMain_display_units());
        displayGraph->setData(x, y);
        displayGraph->drawPlot();
    }else
        qDebug()<<"No Data to Plot";*/
}

void MainWindow::displayBigPlot(void){
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

void MainWindow::displayStats(void){


    showStats->show();
}

void MainWindow::displaySettings(void){
    settingsView->show();
}

void MainWindow::initFile(void){
    //determine file location - if there is a usb drive, use it.  Otherwise use local drive home directory
    //If there isn't a usb drive, always check if one is there each cycle.  If it does find one, make a button visible "USB" that blinks?
    //Also have option to transfer files to usb drive that are local and an option to clear local files
    //Next check for directory labeled with device name.  If not there, create it.
    //This is now the path for all files to be saved
    //



}

void MainWindow::createFileName(void){
    QString dataPath;
    if(allParsedRecordsList.empty())
        return;

    if(fileWriter.createDataFolder(deviceProfile.getDevice_name())){
        //qDebug()<<"found usb mounted at path:"<<fileWriter.getUsbPath();
        dataPath = fileWriter.getFull_data_path();
    }
    SerialDataItem tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size()-1).at(deviceProfile.getDate_position());
    QDateTime tempDateTime = tempSerialDataItem.getDateTime();

    QString fileName = dataPath + tempDateTime.toString("ddMMyyhhmmss")+".csv";
    qDebug()<<"Filename:"<<fileName;
    currentFile.setFileName(fileName);
    //currentFile = new QFile(fileName);
    started_file = true;
}

void MainWindow::writeFile(void){

    if(currentFile.open(QIODevice::Append))
    {
        qDebug()<<"Writing file";
        QTextStream stream(&currentFile);
        stream<<tempDLine;
        currentFile.close();
    }
}


void MainWindow::listFonts(void){
    QFontDatabase database;
    QTreeWidget fontTree;
    fontTree.setColumnCount(2);
    fontTree.setHeaderLabels(QStringList() << "Font" << "Smooth Sizes");

    foreach (const QString &family, database.families()) {
        QTreeWidgetItem *familyItem = new QTreeWidgetItem(&fontTree);
        familyItem->setText(0, family);
        qDebug()<<"Family:"<<family;
        foreach (const QString &style, database.styles(family)) {
            QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);


            QString sizes;
            foreach (int points, database.smoothSizes(family, style))
                sizes += QString::number(points) + " ";

            styleItem->setText(1, sizes.trimmed());
        }
    }
}
