#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    DateTimeForm::getForm();//Initialize the widget here instead of on the grab data thread
    StatsAverageForm::getForm();//Initialize the widget here instead of on the grab data thread

    //This class runs the thread that updates the datetimeform
    grabData = GrabData::getManager();
    grabData->getData();
    started_file = false;
    settings = new QSettings("2B Technologies", "2B Touch");
    usbMounted = false;
    data_point = QDateTime::currentDateTime().toTime_t();
    data_index = 0;
    start_time_seconds = 10000000000;		//give it a maximum start time so it is never less than the time read
    xmlDeviceReader = new XmlDeviceReader(":/deviceConfig.xml");
    xmlDeviceReader->read();
    createDevice();
    setupSerial();
    modbus = ModbusServer::getInstance();//new ModbusServer();
    modbus->updateRegister(0, new QByteArray("BBBBBB"));
    modbus->updateRegister(10, new QByteArray("MMMMMM"));
    modbus->updateRegister(50, 260);
    modbus->updateRegister(100, 123.456f);
    errorTimer= new QTimer(this);
    connect(errorTimer, SIGNAL(timeout()), this, SLOT(errorTimerTick()));
    errorTimer->start(2000);
    //After this is only ui
    ui->setupUi(this);
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    displayGraph = new DisplayGraph(this, gases);
    displayGraph->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    model = new QStringListModel(this);
    QStringList List;
    for(int i = 0; i < gases->size(); i++){
        qDebug() << gases->at(i)->unit;
        if(gases->at(i)->unit != ""){
            //qDebug() << gases->at(i)->unit;
            QListWidgetItem * nItem = new QListWidgetItem();
            QString * s = new QString();
            QString * name = gases->at(i)->name;
            //It might be worth creating this part of the string when initializing the dasDataState
            for(int j = 0; j < name->length(); j++){
                if(name->at(j) >= 48 && name->at(j) <= 57){
                    s->append("<sub>" + QString(name->at(j)) + "</sub>");
                }else{
                    s->append(QString(name->at(j)));
                }
            }
            if(gases->at(i)->data.size() > 0){
                s->append(": <font color='blue'>" + QString::number(gases->at(i)->data.at(gases->at(i)->data.size()-1)) + "</font> " + gases->at(i)->unit);
            }else{
                s->append(": <font color='blue'>0.0</font> " + gases->at(i)->unit);
            }
            nItem->setText(*s);
            List << *s;
        }
    }
    model->setStringList(List);
    ui->listView->setModel(model);
    ui->listView->setItemDelegate(new RichTextDelegate());
    ui->listView->setWordWrap(true);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mainLabel->setText("NO<sub>2</sub>: <font color='green'>0.0</font> ppb");

    createSettingViews();

    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(showSettings()));
    connect(ui->listView, SIGNAL(clicked(const QModelIndex)), this, SLOT(updateMainDisplay(const QModelIndex)));
    connect(ui->graphButton, SIGNAL(clicked()), this, SLOT(displayBigPlot()));
    connect(ui->statsButton, SIGNAL(clicked()), this, SLOT(displayStats()));
    connect(ui->homeButton, SIGNAL(clicked()), this, SLOT(powerDown()));

    QString style("QPushButton { border: none;}");

    QPixmap homePixmap(":/pics/home-icon.gif");
    ui->homeButton->setIcon(homePixmap);
    ui->homeButton->setIconSize(QSize(35,31));
    ui->homeButton->setStyleSheet(style);
    QPixmap configPixmap(":/pics/settings-icon.gif");
    ui->settingsButton->setIcon(configPixmap);
    ui->settingsButton->setIconSize(QSize(35,31));
    ui->settingsButton->setStyleSheet(style);
    QPixmap chartPixmap(":/pics/chart-icon.gif");
    ui->graphButton->setIcon(chartPixmap);
    ui->graphButton->setIconSize(QSize(35,31));
    ui->graphButton->setStyleSheet(style);
    QPixmap statsPixmap(":/pics/stats-icon.gif");
    ui->statsButton->setIcon(statsPixmap);
    ui->statsButton->setIconSize(QSize(35,31));
    ui->statsButton->setStyleSheet(style);

    TestForm * t = new TestForm(this);
}

void MainWindow::updateMainDisplay(const QModelIndex val){   
    if(val.row() == -1){
        currentIndex = 0;
    }else{
        currentIndex = val.row();
    }
    ui->mainLabel->setText(model->stringList().at(currentIndex));
}

void MainWindow::updateList()
{
    int slIndex = 0;  //String list index
    for(int i = 0; i < gases->size(); i++){
        if(gases->at(i)->unit != ""){
            QString * s = new QString();
            QString * name = gases->at(i)->name;

            //It might be worth creating this part of the string when initializing the gasDataState
            for(int j = 0; j < name->length(); j++){
                if(name->at(j) >= 48 && name->at(j) <= 57){
                    s->append("<sub>" + QString(name->at(j)) + "</sub>");
                }else{
                    s->append(QString(name->at(j)));
                }
            }
            if(gases->at(i)->data.size() > 0){
                s->append(": <font color='blue'>" + QString::number(gases->at(i)->data.at(gases->at(i)->data.size()-1)) + "</font> " + gases->at(i)->unit);
            }else{
                s->append(": <font color='blue'>0.0</font> " + gases->at(i)->unit);
            }
            model->setData(model->index(slIndex),*s, 0);
            slIndex++;
        }
    }
    ui->mainLabel->setText(model->stringList().at(currentIndex));
}

void MainWindow::createSettingViews(){
    //Need to get current analog voltage scale
    AnalogForm * a = new AnalogForm();
    a->setStartSclae(250);

    CalForm * c = new CalForm();
    c->getInitialvalues(0.0, 0, 1.1, 1, 2.2, 2);

    DateTimeForm * d = new DateTimeForm();
    d->getCurrent(1,4,30,12,9,18);

    //grabData->getDateForm(d);

    AverageForm *f = new AverageForm(nullptr, gases, false);
    connect(this, SIGNAL(validDataReady()), f, SLOT(update()));

    UiManager * ui = UiManager::getManager();
    ui->settingWidgets->append(new StatsMenuForm());
    ui->settingWidgets->append(c);
    ui->settingWidgets->append(a);
    ui->settingWidgets->append(d);
    //ui->settingWidgets->append(new ModForm());
    ui->settingWidgets->append(f);
    ui->settingWidgets->append(new ModbusForm());
    ui->settingWidgets->append(new NetworkForm());

    ui->network = new NetworkConnectedForm();

    AverageForm * sf = new AverageForm(nullptr, gases, true);

    ui->statsWidgets->append(sf);

    ui->finishedCreating = true;
}

void MainWindow::createDevice(){
    int i;
    twobTechDevice = xmlDeviceReader->getADevice(6);

    deviceProfile.setDevice_name(twobTechDevice.getDevice_name());
    deviceProfile.setCom_port(twobTechDevice.getCom_port());
    deviceProfile.setBaud_rate(twobTechDevice.getBaud_rate());
    //qDebug()<<"Device Profile name: "<<deviceProfile.getDevice_name();
    //qDebug()<<"Device Profile comport: "<<deviceProfile.getCom_port();

    //determine the index of elements
    gases = new QList<GasDataState *>();
    for(i=0;i<twobTechDevice.data_items.size();i++){
        SerialDataItem serialDataItem = twobTechDevice.data_items.at(i);

        GasDataState *state = new GasDataState();
        state->name = new QString(serialDataItem.getName());
        state->unit = QString(serialDataItem.getUnits());
        gases->append(state);

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

void MainWindow::showSettings(){
    UiManager * ui = UiManager::getManager();
    if(ui->cWidget != nullptr)
        ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

void MainWindow::newDataLine(QString dLine){
    if(dLine.at(0) == '*'){
        if(parseDataLine(dLine)){
            emit validDataReady();
        }
    }
}

//Working on
bool MainWindow::parseDataLine(QString dLine){
    if(gases == nullptr){
        gases = new QList<GasDataState *>();
    }
    QStringList fields;
    QVector<double> t,u;
    QDateTime tempDate;
    tempDLine = dLine;
    dLine.remove(QRegExp("[\\n\\t\\r]"));
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
        parsedDataRecord.removeAt(deviceProfile.getDate_position() + 1);
        //if(allParsedRecordsList.size() < MAXIMUM_PARSED_DATA_RECORDS){
        if(allParsedRecordsList.size() > -1){
            allParsedRecordsList.append(parsedDataRecord);
        }else{
            allParsedRecordsList.removeFirst();
            allParsedRecordsList.append(parsedDataRecord);
            qDebug()<<"Maxed out the qlist size, removing first element and adding";
        }
        updateAverage(parsedDataRecord.at(deviceProfile.getMain_display_position()).getDvalue());
        data_point = tempDate.toTime_t();
        if(x.size() == 2)
        {
            int numberOfEnteriesAnHour = (int) ( (3600) / (x.at(1) - x.at(0)));
            int enteriesPerMin = (int) (60/ (x.at(1) - x.at(0)));
            for(int i = 0; i < allParsedRecordsList[allParsedRecordsList.size() - 1].size(); i++)
            {
                //qDebug()<<"List num: " + QString(1);
                gases->at(i)->enteriesPerHour = numberOfEnteriesAnHour;
                gases->at(i)->enteriesPerMinute = enteriesPerMin;
            }
        }
        if(x.size()==MAXIMUM_PARSED_DATA_RECORDS && false){
            x.removeFirst();
            x.append(data_point);
            for(int i = 0; i < allParsedRecordsList[allParsedRecordsList.size() - 1].size(); i++)
            {
                //qDebug()<<"List num: " + QString(1);
                gases->at(i)->data.removeFirst();
                gases->at(i)->x.removeFirst();
                gases->at(i)->addData(data_point, allParsedRecordsList[allParsedRecordsList.size()-1][i].getDvalue());
            }
            qDebug()<<"Maximum size reached";
        }else{
            x.append(data_point);
            for(int i = 0; i < allParsedRecordsList[allParsedRecordsList.size() - 1].size(); i++)
            {
                gases->at(i)->addData(data_point, allParsedRecordsList[allParsedRecordsList.size()-1][i].getDvalue());
            }
        }
        updateList();
        emit receivedData();
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
    else
    {
        avgDur = 0;
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

void MainWindow::powerDown()
{
    QApplication::quit();
}

void MainWindow::displayBigPlot(void)
{
    if(displayGraph == nullptr)
    {
        displayGraph = new DisplayGraph(this, gases);
    }
    displayGraph->redrawPlot();
    displayGraph->show();
}

void MainWindow::displayStats(void)
{
    UiManager * manager = UiManager::getManager();
    manager->cStatWidget = manager->statsWidgets->at(manager->cStatIndex);
    manager->cStatWidget->show();

}

void MainWindow::displaySettings(void){
    //Reworked needs update
    //settingsWidget->show();
    //settingsView->show();
}

void MainWindow::setupSerial(){
    QThread *thread = new QThread(this);
    serialHandler = new SerialHandler(thread, this);
    //serialHandler->writeSync(new QString("test"));
    connect(serialHandler, SIGNAL(dataAvailable(QString)), this, SLOT(newDataLine(QString)));
    QTimer::singleShot(2000, serialHandler, SLOT(updateSettings()));
}

void MainWindow::writeData(const QByteArray &data){
    serial->write(data);
}

void MainWindow::readData(){
    if(serial->canReadLine()){
        QByteArray data = serial->readAll();
        newDataLine(data);
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error){
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::closeSerialPort(){
    serial->close();
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
                //settingsWidget->copyAllPressed();
                //update this
            }
        }
    }
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

//Not sure if used
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
                warningLabel->setText("OK");
            }
        }
    }
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
    char t = ret.at(pos).toLatin1();
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
            //space = space;
            break;
        default:
            space = -1;
            break;
    }
    qDebug()<<"Free Elapsed"<<freeTimer.elapsed();
    return QString::number(space);
}

MainWindow::~MainWindow()
{
    delete ui;
}
