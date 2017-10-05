#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

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

    //play_jingle();
    started_file = false;
    //this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons
    //this->setStyleSheet(" background-image: url(:/keyboard/keyboard/Touch-Keyboard-white.png);");
    //ControlBacklight controlBacklight;
    //controlBacklight.setPercentage(100);
    listFonts();

    settings = new QSettings("2B Technologies", "2B Touch");
    usbMounted = false;
    buttonSize = QSize(50, 50);

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
    configure_button->setFixedSize(buttonSize);


    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(buttonSize);


    graph_button = new QPushButton();
    QPixmap chartPixmap(":/buttons/pics/chart-icon.gif");
    QIcon chartButtonIcon(chartPixmap);

    graph_button->setIcon(chartButtonIcon);
    graph_button->setIconSize(QSize(35,31));
    graph_button->setFixedSize(buttonSize);

    connect(graph_button, SIGNAL(clicked()), this, SLOT(displayBigPlot()));

    QPushButton *stats_button = new QPushButton();
    QPixmap statsPixmap(":/buttons/pics/stats-icon.gif");
    QIcon statsButtonIcon(statsPixmap);
    stats_button->setIcon(statsButtonIcon);
    stats_button->setIconSize(QSize(35,31));
    stats_button->setFixedSize(buttonSize);
    QFont labelFont("Courier", 50, QFont::ForceIntegerMetrics);

    QFont unitsLabelFont("Courier", 40, QFont::ForceIntegerMetrics);

    QFont timeFont("Courier", 12, QFont::ForceIntegerMetrics);
    current_time->setFont(timeFont);
    current_date->setFont(timeFont);


    main_label->setFont(labelFont);

    main_units_label->setStyleSheet("QLabel { color : black; }");
    main_units_label->setFont(unitsLabelFont);
    main_measurement_display->setFont(labelFont);
    main_measurement_display->setStyleSheet("QLabel { color : green; }");
    main_measurement_display->setFixedWidth(8);

    warningLabel = new QLabel("Warming Up", this);
    warningLabel->setGeometry(35, 190, 400, 20);
    warningLabel->setMinimumWidth(100);
    warningLabel->setAlignment(Qt::AlignCenter);

    topTimeLayout->addWidget(warningLabel);
    topTimeLayout->addSpacing(300);
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
    verticalLayout->addSpacing(45);
    //verticalLayout->addSpacing(10);
   // verticalLayout->addWidget(warningLabel);
   // verticalLayout->addSpacing(10);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addSpacing(2);
    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(configure_button);
    buttonLayout->addWidget(graph_button);
    buttonLayout->addWidget(stats_button);

    verticalLayout->addLayout(buttonLayout);
    //verticalLayout->addSpacing(5);

	
    data_point = QDateTime::currentDateTime().toTime_t();
    data_index = 0;
	start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    displayGraph = new DisplayGraph();
    displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(this, SIGNAL(validDataReady()), displayGraph, SLOT(redrawPlot()));

    connect(displayGraph, SIGNAL(userClearedPlot()), this, SLOT(clearPlotData()));


    //connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    //showStats = new ShowStats();
    //showStats->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    settingsView = new SettingsView();
    settingsView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(configure_button, SIGNAL(clicked()), this, SLOT(displaySettings()));

    settingsWidget = new SettingsWidget();
    settingsWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(settingsWidget, SIGNAL(sendMsg(QString)), this, SLOT(on_sendMsg(QString)));
    //connect(settingsWidget, SIGNAL(sendAMsg(QString*)), serialHandler, SLOT(writeAsync(QString*)));



    xmlDeviceReader = new XmlDeviceReader(":/deviceConfig.xml");
    xmlDeviceReader->read();


    //current_time->setText("8:30:45");
    //current_date->setText("02/17/2016");
    createDevice();
    statsWidget = new StatsWidget(deviceProfile, this);
    statsWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(stats_button, SIGNAL(clicked()), this, SLOT(displayStats()));
    //qDebug()<<"After stats widget creation";

    setupSerial();



    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    this->setStyleSheet(msgBoxStyle);

    //statusRow = new QHBoxLayout(this);
    //statusRow->setGeometry(QRect(15, 15, 100, 20));

    QPixmap pixmap(":/icons/pics/usb-icon.png");
    QIcon icon(pixmap);
    usbIcon = new QPushButton(this);
    usbIcon->setIcon(icon);
    //usbIcon->setGeometry(15, 20, 20, 20);
    usbIcon->setGeometry(20, 20, 40, 20);
    usbIcon->setFixedSize(QSize(20, 20));
    usbIcon->setIconSize(QSize(20, 20));

    usbTimer = new QTimer(this);
    connect(usbTimer, SIGNAL(timeout()), this, SLOT(usbTimerTick()));
    usbTimer->start(5000);

    /*QPixmap errorPix(":/icons/pics/error-icon.png");
    QIcon eIc(errorPix);
    errorIcon = new QPushButton(this);
    errorIcon->setIcon(eIc);
    errorIcon->setGeometry(100, 20, 20, 20);
    errorIcon->setFixedSize(QSize(20, 20));
    errorIcon->setIconSize(QSize(20, 20));*/

    //cpuIcon = new QPushButton(this);
    //cpuIcon->setGeometry(35, 20, 40, 20);
    //cpuIcon->setFixedSize(QSize(40, 20));
    //cpuIcon->setText(getCpuUsage());

    //QPixmap diskPix(":/icons/pics/disk-error-icon.png");
    //QIcon diskIc(diskPix);
   // diskSpaceIcon = new QPushButton(this);
   // diskSpaceIcon->setIcon(diskIc);
   // diskSpaceIcon->setGeometry(75, 20, 20, 20);
   // diskSpaceIcon->setFixedSize(QSize(20, 20));
   // diskSpaceIcon->setIconSize(QSize(20, 20));

   /* warningIcon = new QPushButton(this);
    warningIcon->setIcon(eIc);
    warningIcon->setGeometry(15, 190, 20, 20);
    warningIcon->setIconSize(QSize(20, 20));*/



   // warningIcon->hide();
   // warningLabel->hide();

    errorTimer= new QTimer(this);
    connect(errorTimer, SIGNAL(timeout()), this, SLOT(errorTimerTick()));
    errorTimer->start(2000);

    //statusRow->addWidget(usbIcon);
    //statusRow->addWidget(cpuIcon);
    //statusRow->addWidget(diskSpaceIcon);
    //statusRow->addWidget(errorIcon);
    //QString test("blah");
    //serialHandler->write106(&test);
    //this->i2c_test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//build a device from the xml and prepare place to put the data
void MainWindow::createDevice(){
    int i;
    twobTechDevice = xmlDeviceReader->getADevice(1);

    deviceProfile.setDevice_name(twobTechDevice.getDevice_name());
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
        } else if(serialDataItem.getPriority() == 6) {

            deviceProfile.setDiagnosticF_uints(serialDataItem.getUnits());
            deviceProfile.setDiagnosticF_name(serialDataItem.getName());
            deviceProfile.setDiagnosticF_position(i);
        }
        //qDebug()<<"For "<<i<<" priority="<<serialDataItem.getPriority();
    }
    qDebug()<<"Finished Profile Setup";
    deviceProfile.setNumber_of_columns(i);
    qDebug()<<"Number of columns:"<<deviceProfile.getNumber_of_columns();

}

void MainWindow::setupSerial(){
    QThread *thread = new QThread(this);
    serialHandler = new SerialHandler(thread);
    //serialHandler->writeSync(new QString("test"));
    connect(serialHandler, SIGNAL(dataAvailable(QString)), this, SLOT(newDataLine(QString)));
    QTimer::singleShot(2000, serialHandler, SLOT(updateSettings()));
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
    //qDebug()<<dLine;
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

        updateAverage(parsedDataRecord.at(deviceProfile.getMain_display_position()).getDvalue());

        data_point = QDateTime::currentDateTime().toTime_t();

        //to do - limit how big the graph can get (if size == GRAPH_SIZE_LIMIT) then shift list and add to end of list
        if(x.size()==MAXIMUM_PARSED_DATA_RECORDS){
            qDebug()<<"Maximum size reached";
            x.removeFirst();
            x.append(data_point);
            y.removeFirst();
            y.append(avg);
        }else{
            x.insert(data_index,data_point);
            y.insert(data_index,avg);//parsedDataRecord.at(deviceProfile.getMain_display_position()).getDvalue());
            t=x;                    //copy the vectors to order them to get high and low for range
            u=y;
            data_index++;
        }

        //for(int i=0;i<y.size();i++){
         //   qDebug()<<"y["<<i<<"]="<<y.at(i);
        //}

        updateDisplay();
        return true;


    }else{
        qDebug()<<"Incomplete line: "<<fields.length()<<" columns.";
        return false;
    }
}

void MainWindow::updateAverage(double value) {
    int avgIndex = settings->value("Avg").toInt();
    avgIndex = 0;
    //qDebug()<<"Avg Index: "<<avgIndex;
    int avgDur;
    if (avgIndex == 0) {
        avgDur = 2;
    } else if (avgIndex == 1) {
        avgDur = 10;
    } else if (avgIndex == 2) {
        avgDur = 60;
    } else if (avgIndex == 3) {
        avgDur = 60 * 15;
    } else if (avgIndex == 4) {
        avgDur = 60 * 60;
    }
    int avgCount = avgDur / 2;
    if(avgCount < 1) {
        avgCount = 1;
    }
    //qDebug()<<"Avg Count: "<<avgCount;

    int curLength = avgList.length();
    if(curLength > avgCount) {
        //Average The List By Pairs Until It is Less Than The New Value
        while(avgList.length() > avgCount) {
            qDebug()<<"Consolidating Avg List";
            QList<double> temp;
            for(int i = 0; i < (avgList.length() / 2); i++) {
                double a = avgList.at(i);
                i++;
                double b = avgList.at(i);

                double tAvg = (a + b) / 2;
                temp << tAvg;
            }
            //qDebug()<<"Temp List: "<<temp;
            avgList = temp;
        }
    } else if(curLength == avgCount) {
        QList<double> tempList;
        for(int i = 0; i < (avgList.length() - 1); i++) {
            tempList<<avgList.at(i+1);
        }
        avgList = tempList;
    }
    avgList<<value;
    //qDebug()<<"Avg List: "<<avgList;

    double sum = 0;
    for(int i = 0; i < avgList.length(); i++) {
        sum += avgList.at(i);
    }
    avg = sum / avgList.length();
}

void MainWindow::updateDisplay(void){
    double current_value;
    double scrubber_temperature;

    if(!started_file){
        qDebug()<<"File not started yet, attempting to start file";

        this->createFileName();
    }
    SerialDataItem tempSerialDataItem;
    //first, get the main measurement value
    tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size() -1).at(deviceProfile.getMain_display_position()); 
    current_value = tempSerialDataItem.getDvalue();
    //check of the scrubber temperature is hot enough
    //tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size() -1).at(deviceProfile.getDiagnosticC_position());
    //scrubber_temperature = tempSerialDataItem.getDvalue();
    //main_label->setText(deviceProfile.getMain_display_name()+": ");
    if(deviceProfile.getMain_display_name().contains("3")){
        main_label->setText("O<sub>3</sub>: ");
    }else if(deviceProfile.getMain_display_name().contains("2")){
         main_label->setText("NO<sub>2</sub>: ");
    }

    //skip first 3 minutes of data by default
    if(allParsedRecordsList.size()<18){
        current_value = 0;
    }
    QString mesStr = QString::number(current_value);

    if(mesStr.contains(".")) {
        while(mesStr.at(mesStr.length() - 2) != '.') {
            mesStr = mesStr.mid(0, mesStr.length() - 1);
        }
    } else {
       mesStr.append(".0");
    }

    main_measurement_display->setText(mesStr);
    main_units_label->setText(" "+deviceProfile.getMain_display_units());
    //qDebug()<<"date position:"<<deviceProfile.getDate_position();
    tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size() -1).at(deviceProfile.getDate_position());
//qDebug()<<"Current time:"<<tempSerialDataItem.getDateTime().toString("dd/mm/yy");
    current_time->setText(tempSerialDataItem.getDateTime().toString("hh:mm"));
    //QString tempDate = tempSerialDataItem.getDateTime().toString("ddMMyy");
    //qDebug()<<"DateString:"<<tempDate;
    //QString tempTime = tempSerialDataItem.getDateTime().toString("hhmmss");
    //qDebug()<<"TimeString:"<<tempTime;
    //qDebug()<<"Here next";
    settings->setValue("Time", tempSerialDataItem.getDateTime().toString("hhmmss"));
    settings->setValue("Date", tempSerialDataItem.getDateTime().toString("ddMMyy"));
    //qDebug()<<"Before statswidget";
    statsWidget->setData(&allParsedRecordsList, &deviceProfile);
     //qDebug()<<"Here9";
    //statsWidget->calculateMaxMinMedian(allParsedRecordsList, 0);
     //qDebug()<<"Here10";
    this->writeFile();
    if(!y.isEmpty()){
        //displayGraph->setYaxisLabel(deviceProfile.getMain_display_name()+" "+deviceProfile.getMain_display_units());
        displayGraph->setData(x, y);
        displayGraph->drawPlot();
    }else
        qDebug()<<"No Data to Plot";
    //qDebug()<<"Here9";
}

void MainWindow::displayBigPlot(void){
        displayGraph->setData(x, y);
        displayGraph->drawPlot();
        displayGraph->show();

}
 
void MainWindow::clearPlotData(void){
    //qDebug()<<"Clearing plot data, xcount:"<<x.count()<<", ycount:"<<y.count();
    data_index = 0;
    x.clear();
    y.clear();
    qDebug()<<"Finished Clearing Data";
}

void MainWindow::displayStats(void){
    statsWidget->show();
    //showStats->show();
}

void MainWindow::displaySettings(void){
    settingsWidget->show();
    //settingsView->show();
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
    } else {
        dataPath = "/"+deviceProfile.getDevice_name() + "/";
        QDir dir(dataPath);
        if(!dir.exists()) {
            QDir().mkdir(dataPath);
        }
    }
    SerialDataItem tempSerialDataItem = allParsedRecordsList.at(allParsedRecordsList.size()-1).at(deviceProfile.getDate_position());
    QDateTime tempDateTime = tempSerialDataItem.getDateTime();

    QString fileName = dataPath + tempDateTime.toString("ddMMyyhhmmss")+".csv";
    qDebug()<<"Filename:"<<fileName;
    currentFile.setFileName(fileName);
    //currentFile = new QFile(fileName);
    started_file = true;
    qDebug()<<"Finished Creating File";
}

void MainWindow::writeFile(void){

    if(currentFile.open(QIODevice::Append))
    {
        //qDebug()<<"Writing file: "<<currentFile.fileName();
        if(!tempDLine.contains("\n")){
            //qDebug()<<"Adding line feed carriage return";
            tempDLine.append("\n");
        }
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

void MainWindow::on_sendMsg(QString msg) {
    qDebug()<<"Slot from send message";
    serialHandler->writeSync(new QString(msg));
}

void MainWindow::usbTimerTick() {
    if(usbMounted) {
        usbMounted = fileWriter.checkIfUsbMounted();
        usbIcon->show();
        if(!usbMounted) {
            //USB Lost
            createFileName();
        }
    } else {
        usbMounted = fileWriter.checkIfUsbMounted();
        usbIcon->hide();
        if(usbMounted) {
            //USB Found
            createFileName();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "USB Found", "Would you like to copy all files to the usb drive?", QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes) {
                settingsWidget->copyAllPressed();
            }
        }
    }
}

void MainWindow::errorTimerTick() {
    //Check STemp
    //qDebug()<<"Error Timer Tick: "<<QDateTime::currentDateTime().toTime_t();
    if(deviceProfile.getDevice_name()=="IAQ"||deviceProfile.getDevice_name()=="IAQ-PC"){
        if(allParsedRecordsList.length() != 0) {
            SerialDataItem item = allParsedRecordsList.last().at(deviceProfile.getDiagnosticC_position());
            double val = item.getDvalue();
            if(val < (80 + 273)) {
                //errorIcon->show();
                //warningIcon->show();
                warningLabel->setText("Warming up");
                //warningLabel->show();
            } else {
                //errorIcon->hide();
                //warningIcon->hide();
                //warningLabel->hide();
                warningLabel->setText("OK");
            }
        }
    }
    /*cpuIcon->setText(getCpuUsage());
    QString spaceStr = getFreeSpace();
    //qDebug()<<"Space: "<<spaceStr;
    double space = spaceStr.toDouble();
    if(space < 2000) {
        diskSpaceIcon->show();
    } else {
        diskSpaceIcon->hide();
    }*/
}

QString MainWindow::getCpuUsage() {
    QElapsedTimer cpuTimer;
    cpuTimer.start();
    QString prog = "/bin/bash";
    QStringList args;
    args<<"/home/armadillo/cpuUsage";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();

    QString ret = process->readAll();
    //qDebug()<<"CPU: "<<ret;
    qDebug()<<"CPU Elapsed"<<cpuTimer.elapsed();
    cpuTimer.invalidate();
    return ret;
}

QString MainWindow::getFreeSpace() {
    QElapsedTimer freeTimer;
    freeTimer.start();
    QString prog = "/bin/bash";
    QStringList args;
    args<<"/home/armadillo/diskSpace";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();

    QString ret = process->readAll();
    //qDebug()<<"Free Space: "<<ret;
    int pos = 0;
    char t;
    bool cont = true;
    while(cont) {
        if((t == 'G') || (t == 'M') || (t == 'K')) {
            cont = false;
        } else {
            pos++;
            t = ret.at(pos).toLatin1();
        }
    }
    QString spaceStr = ret.mid(0, pos);
    double space = spaceStr.toDouble();
    switch(t) {
        case 'M':
            space *=1000;
            break;
        case 'G':
            space *=1000*1000;
            break;
        case 'K':
            space = space;
            break;
        default:
            space = -1;
            break;
    }
    qDebug()<<"Free Elapsed"<<freeTimer.elapsed();
    return QString::number(space);

}

void MainWindow::i2c_test(void){
    int file;
    char *filename = "/dev/i2c-1";
    if ((file = open(filename, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        qDebug()<<"Failed to open the i2c bus";
        return;
    }else{
        qDebug()<<"Opened the i2c bus";
    }
}

void MainWindow::play_jingle(void){
    //check if sound file exists

    QString file_path = "/jingle.wav";
    if(!QDir(file_path).exists()){
        qDebug()<<"Could not find file";
    }else{

        QString prog = "/bin/bash";//shell

        QStringList arguments;


        arguments << "-c" << "aplay " + file_path;
        QProcess *process = new QProcess();
        process->start(prog , arguments);
        //process->waitForFinished();
    }

}
