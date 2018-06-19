#include "settingswidget.h"
#include "ui_settingswidget.h"
#include <QSignalMapper>
#include <QDir>
#include <QException>
#include <QDebug>
#include "modbus_server.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

     settings = new QSettings("2B Technologies", "2B Touch");
    qDebug()<<"before initializing views";
    initializeViews();



    XmlDeviceReader *reader = new XmlDeviceReader(":/deviceConfig.xml");
    reader->read();
    device = reader->getADevice(1);



}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::initializeViews() {
    mainLayout = new QVBoxLayout(this);

    buttonSize = QSize(35, 31);
    this->setStyleSheet("QPushButton { border: none; }");

    univStyle = "QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    //set font for entire setup


    QFont genericFont("Cabin");


    homeButton = new QPushButton();
    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    homeButton->setFixedSize(buttonSize);
    homeButton->setIconSize(buttonSize);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

    regButtonStyle = "background-color: rgba(255, 255, 255, 0); color: #000000";
    selButtonStyle = "background-color: #002266; color: #ffffff";

    titleFont = QFont("Cabin", 30, 4);
    labelFont = QFont("Cabin", 20, 3);
    labelFontSmall = QFont("Cabin", 10, 2);

    widgetForLanding();

    //mainLayout->addWidget(landing);

    qDebug()<<"initialize views in settings widget";

}

void SettingsWidget::widgetForLanding() {



        QWidget *cal = widgetForCal();

        QPushButton *left = new QPushButton(cal);
        left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
        connect(left, SIGNAL(released()), this, SLOT(showModbus()));

        QPushButton *right = new QPushButton(cal);
        right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
        connect(right, SIGNAL(released()), this, SLOT(showRO()));

        right->setFixedSize(buttonSize);
        right->setIconSize(buttonSize);
        left->setFixedSize(buttonSize);
        left->setIconSize(buttonSize);

        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(left);
        layout->addWidget(cal);
        layout->addWidget(right);
        QWidget *w = new QWidget();
        w->setLayout(layout);

        homeButton->setParent(w);
        mainLayout->addWidget(w);


}

QWidget* SettingsWidget::widgetForCal() {
    //Calibration
    calWidget = new QWidget(this);
    calVLayout = new QVBoxLayout(calWidget);
    calTitle = new QLabel("CALIBRATION");
    calSlopeRow = new QHBoxLayout(calWidget);
    calSlopeLabel = new QLabel("Slope: ");
    calSlopeLabel->setMaximumWidth(100);
    calSlopeLabel->setAlignment(Qt::AlignLeft);
    slopeCheckBox = new QCheckBox();
    slopeCheckBox->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px;}");
    //qDebug()<<"before slopestring";
    slopeValue = settings->value("Slope").toFloat();
    qDebug()<<"Slope value read from settings:"<<slopeValue;
    qDebug()<<"String with fraction value:"<<QString::number(slopeValue/100, 'f', 2);
    //qDebug()<<"after appending";
    //calSlopeField = new KeyLineEdit(slopeString, calWidget);
    calSlopeField = new QLabel();
    calSlopeField->setAlignment(Qt::AlignLeft);
    calSlopeField->setText(QString::number(slopeValue/100, 'f', 2));

    //qDebug()<<"after making keylineedit";
    calSlopeField->setMaximumWidth(100);
    calOffsetRow= new QHBoxLayout(calWidget);
    calOffsetLabel= new QLabel("Offset: ");
    calOffsetLabel->setMaximumWidth(100);
    calOffsetLabel->setAlignment(Qt::AlignLeft);
    offsetCheckBox = new QCheckBox();
    offsetCheckBox->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px;}");

    calOffsetField = new QLabel();
    calOffsetField->setText(QString::number(offsetValue));

    calOffsetField->setMaximumWidth(50);
    calOffsetField->setAlignment(Qt::AlignLeft);
    calSubmit = new QPushButton("SAVE", calWidget);
    calIncreaseButton = new QPushButton("+");
    calDecreaseButton = new QPushButton("-");

    //Styling
    calTitle->setFont(titleFont);
    calTitle->setAlignment(Qt::AlignHCenter);
    calSlopeLabel->setFont(labelFont);
    calOffsetLabel->setFont(labelFont);
    calSlopeField->setFont(labelFont);
    calOffsetField->setFont(labelFont);
    calSubmit->setFixedHeight(30);
    calVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    calIncreaseButton->setStyleSheet("color: blue;");
    calDecreaseButton->setStyleSheet("color: blue;");
    calIncreaseButton->setFont(labelFont);
    calDecreaseButton->setFont(labelFont);
    slopeCheckBox->setChecked(true);

    //Calibration - Fill Layout
    calVLayout->addWidget(calTitle);
    calSlopeRow->addWidget(calSlopeLabel);
    calSlopeRow->addWidget(calSlopeField);
    calSlopeRow->addWidget(slopeCheckBox);
    calSlopeRow->addSpacing(10);
    calSlopeRow->addWidget(calIncreaseButton);
    calVLayout->addLayout(calSlopeRow);
    calOffsetRow->addWidget(calOffsetLabel);
    calOffsetRow->addWidget(calOffsetField);
    calOffsetRow->addWidget(offsetCheckBox);
    calOffsetRow->addSpacing(10);
    calOffsetRow->addWidget(calDecreaseButton);
    calVLayout->addLayout(calOffsetRow);
    calVLayout->addWidget(calSubmit);
    calWidget->setLayout(calVLayout);
    //calWidget->setStyleSheet(univStyle);
    //Calibration - Connect Buttons
    connect(calSubmit, SIGNAL(released()), this, SLOT(calSubmitReleased()));
    connect(calIncreaseButton, SIGNAL(released()), this, SLOT(on_calIncreasePressed()));
    connect(calDecreaseButton, SIGNAL(released()), this, SLOT(on_calDecreasePressed()));
    connect(slopeCheckBox, SIGNAL(released()),this, SLOT(on_slopeCheckBoxPressed()));
    connect(offsetCheckBox, SIGNAL(released()),this, SLOT(on_offsetCheckBoxPressed()));

    homeButton->setParent(calWidget);

    calOffsetField->setText(settings->value("Zero").toString());


    calIncreaseButton->setAutoRepeat(true);
    calDecreaseButton->setAutoRepeat(true);
    //calSlopePad = new Keypad(calSlopeField, false, calWidget);
    //calOffPad = new Keypad(calOffsetField, false, calWidget);

    return calWidget;
}



QWidget* SettingsWidget::widgetForRelayOne() {


    //RelayOne
    rOWidget = new QWidget(this);
    rOVLayout = new QVBoxLayout(rOWidget);
    relayOneTitle = new QLabel("RELAY", rOWidget);
    rOLowRow = new QHBoxLayout(rOWidget);
    rOLowLabel = new QLabel("↓LOW", rOWidget);
    rOLowLabel->setMinimumWidth(100);
    rOLowLabel->setAlignment(Qt::AlignLeft);
    relayOneLowValue = settings->value("RelOn").toInt();
    QString lowString;

    lowString.append(QString::number(relayOneLowValue));

    rOLowField = new QLabel();
    rOLowField->setText(lowString);
    rOLowField->setMinimumWidth(75);
    rOLowField->setAlignment(Qt::AlignLeft);
    rOLowCheckBox = new QCheckBox(rOWidget);
    rOLowCheckBox->setChecked(true);
    rOHighCheckBox = new QCheckBox(rOWidget);
    rOHighCheckBox->setChecked(false);
    rOLowCheckBox->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px;}");
    rOHighCheckBox->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px;}");

   // rOLowField->setMaximumWidth(50);
    rOLowLabel->setMinimumWidth(100);
    rOLowLabel->setAlignment(Qt::AlignLeft);
    rOHighRow = new QHBoxLayout(rOWidget);
    rOHighLabel = new QLabel("HIGH↑", rOWidget);
    rOHighLabel->setMinimumWidth(100);
    QString highString;
    relayOneHighValue = settings->value("RelOff").toInt();
    highString.append(QString::number(relayOneHighValue));
    rOHighField = new QLabel();
    rOHighField->setText(highString);
    rOHighField->setMinimumWidth(75);
    rOHighField->setAlignment(Qt::AlignLeft);
    rOSubmitButton = new QPushButton("SAVE", rOWidget);

    //rORow = new QHBoxLayout(rOWidget);
    //rOLowButton = new QPushButton("↓LOW", rOWidget);
    //rOHighButton = new QPushButton("HIGH↑", rOWidget);
    QPixmap pixmap(":/buttons/pics/help-icon.png");
    QIcon icon(pixmap);
    rOHelpButton = new QPushButton(rOWidget);
    rOHelpButton->setIcon(icon);
    rOHelpButton->setFixedSize(buttonSize);
    rOHelpButton->setIconSize(buttonSize);

    relayIncreaseButton = new QPushButton("+");
    relayDecreaseButton = new QPushButton("-");
    relayIncreaseButton->setStyleSheet("color: blue;");
    relayDecreaseButton->setStyleSheet("color: blue;");

    //Styling
    relayOneTitle->setFont(titleFont);
    relayOneTitle->setAlignment(Qt::AlignHCenter);
    rOLowLabel->setFont(labelFont);
    rOHighLabel->setFont(labelFont);
    rOLowField->setFont(labelFont);
    rOSubmitButton->setFont(labelFont);


    rOHighField->setFont(labelFont);
    relayDecreaseButton->setFont(labelFont);
    relayIncreaseButton->setFont(labelFont);
    //rOLowButton->setFixedHeight(60);
    //rOHighButton->setFixedHeight(60);
    rOVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Relay One - Fill Layout
    rOVLayout->addWidget(relayOneTitle);
    rOLowRow->addWidget(rOLowLabel);
    rOLowRow->addWidget(rOLowField);
    rOLowRow->addWidget(rOLowCheckBox);
    rOLowRow->addWidget(relayIncreaseButton);

    rOVLayout->addLayout(rOLowRow);
    rOHighRow->addWidget(rOHighLabel);
    rOHighRow->addWidget(rOHighField);
    rOHighRow->addWidget(rOHighCheckBox);
    rOHighRow->addSpacing(10);
    rOHighRow->addWidget(relayDecreaseButton);
    rOVLayout->addLayout(rOHighRow);
    rOVLayout->addWidget(rOSubmitButton);
    //rORow->addWidget(rOLowButton);
    //rORow->addWidget(rOHighButton);
    //rOVLayout->addLayout(rORow);
    rOHelpButton->setGeometry(320, 15, 30, 30);
    relayIncreaseButton->setMinimumSize(30,30);
    relayDecreaseButton->setMinimumSize(30,30);
    rOWidget->setLayout(rOVLayout);
    rOWidget->setStyleSheet(univStyle);
    //Relay One - Connect Buttons
    //connect(rOLowButton, SIGNAL(released()), this, SLOT(rOLowPressed()));
    //connect(rOHighButton, SIGNAL(released()), this, SLOT(rOHighPressed()));
    connect(rOSubmitButton, SIGNAL(released()), this, SLOT(rOSubmitPressed()));
    connect(rOHelpButton, SIGNAL(released()), this, SLOT(rOHelpPressed()));
    connect(relayIncreaseButton, SIGNAL(released()), this, SLOT(on_relayIncreasePressed()));
    connect(relayDecreaseButton, SIGNAL(released()), this, SLOT(on_relayDecreasePressed()));
    connect(rOLowCheckBox, SIGNAL(released()),this, SLOT(on_relayLowCheckBoxPressed()));
    connect(rOHighCheckBox, SIGNAL(released()),this, SLOT(on_relayHighCheckBoxPressed()));


    relayIncreaseButton->setAutoRepeat(true);
    relayDecreaseButton->setAutoRepeat(true);


   //rOLowPad = new Keypad(rOLowField, false, rOWidget);
    //rOHighPad / new Keypad(rOHighField,false, rOWidget);

    homeButton->setParent(rOWidget);

    return rOWidget;
}


QWidget* SettingsWidget::widgetForVoltage() {
    //Voltage
    voltWidget = new QWidget(this);
    voltVLayout = new QVBoxLayout(voltWidget);
    voltTitle = new QLabel("ANALOG OUTPUT", voltWidget);
    voltVoltLabel = new QLabel("2.5 V =", voltWidget);
    voltVoltLabel->setMaximumWidth(250);
    voltPPBRow = new QHBoxLayout(voltWidget);
    QString voltString;
    voltString.append(settings->value("VOut").toString());
    voltPPBField = new QLabel(voltString);
    voltPPBField->setMaximumWidth(100);
    voltPPBLabel = new QLabel("ppb", voltWidget);
    voltSubmitButton = new QPushButton("SAVE", voltWidget);
    increaseVoltButton = new QPushButton("+");
    decreaseVoltButton = new QPushButton("-");
    //Styling
    voltTitle->setFont(titleFont);
    voltTitle->setAlignment(Qt::AlignHCenter);
    voltVoltLabel->setFont(labelFont);
    voltVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    voltPPBField->setFont(labelFont);
    voltPPBLabel->setFont(labelFont);
    increaseVoltButton->setFont(labelFont);
    decreaseVoltButton->setFont(labelFont);
    increaseVoltButton->setStyleSheet("color: blue;");
    decreaseVoltButton->setStyleSheet("color: blue;");
    voltSubmitButton->setFont(labelFont);
    //Voltage - Fill Layout
    voltVLayout->addWidget(voltTitle);
    //voltVLayout->addWidget(voltVoltLabel);
    voltPPBRow->addWidget(voltVoltLabel);
    voltPPBRow->addWidget(voltPPBField);
    voltPPBRow->addWidget(voltPPBLabel);
    voltPPBRow->addWidget(increaseVoltButton);
    voltPPBRow->addSpacing(10);
    voltPPBRow->addWidget(decreaseVoltButton);
    voltVLayout->addLayout(voltPPBRow);
    voltVLayout->addWidget(voltSubmitButton);
    voltWidget->setLayout(voltVLayout);
    voltWidget->setStyleSheet(univStyle);

    QString v = settings->value("VOut").toString();
    voltPPBField->setText(v);
    //voltPad = new Keypad(voltPPBField, false, voltWidget);

    connect(voltSubmitButton, SIGNAL(pressed()), this, SLOT(voltSubmitPressed()));
    connect(increaseVoltButton, SIGNAL(pressed()), this, SLOT(on_increaseVoltButton()));
    connect(decreaseVoltButton, SIGNAL(pressed()), this, SLOT(on_decreaseVoltButton()));

    increaseVoltButton->setAutoRepeat(true);
    decreaseVoltButton->setAutoRepeat(true);

    homeButton->setParent(voltWidget);

    return voltWidget;
}

QWidget* SettingsWidget::widgetForFiles() {
    //Files
    filesWidget = new QWidget(this);
    filesVLayout = new QVBoxLayout(filesWidget);
    filesTitle = new QLabel("FILES", filesWidget);
    filesCopyActionsMenu = new QHBoxLayout(filesWidget);
    filesCopyAllButton = new QPushButton("COPY ALL", filesWidget);
    filesCopySelectedButton = new QPushButton("COPY SELECTED", filesWidget);
    filesTable = new QTableWidget(0, 2, filesWidget);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList labels;
    labels << tr("Filename") << tr("Date Created");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setShowGrid(false);

    QStringList extFilter("*.csv");
    QDir currentDir = QDir("/"+device.getDevice_name());
    QStringList list = currentDir.entryList(extFilter);
    for(int i = 0; i < list.length(); i++) {
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(list.at(i));
        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);

        QFileInfo fileInfo("/"+device.getDevice_name()+"/"+list.at(i));
        QString date = fileInfo.created().toString("MM/dd/yy");
        QTableWidgetItem *dateItem = new QTableWidgetItem(date);
        filesTable->setItem(row, 1, dateItem);
    }

    filesDeleteActionsMenu = new QHBoxLayout(filesWidget);
    filesDeleteAllButton = new QPushButton("Delete All", filesWidget);
    filesDeleteSelectedButton = new QPushButton("Delete Selected", filesWidget);

    filesTitle->setFont(titleFont);

    filesVLayout->addWidget(filesTitle);
    filesCopyActionsMenu->addWidget(filesCopyAllButton);
    filesCopyActionsMenu->addWidget(filesCopySelectedButton);
    filesVLayout->addLayout(filesCopyActionsMenu);
    filesVLayout->addWidget(filesTable);
    filesDeleteActionsMenu->addWidget(filesDeleteAllButton);
    filesDeleteActionsMenu->addWidget(filesDeleteSelectedButton);
    filesVLayout->addLayout(filesDeleteActionsMenu);
    filesWidget->setStyleSheet(univStyle);

    filesTitle->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    connect(filesCopyAllButton, SIGNAL(released()), this, SLOT(copyAllPressed()));
    connect(filesCopySelectedButton, SIGNAL(released()), this, SLOT(copySelectedPressed()));
    connect(filesDeleteAllButton, SIGNAL(released()), this, SLOT(deleteAllPressed()));
    connect(filesDeleteSelectedButton, SIGNAL(released()), this, SLOT(deleteSelectedPressed()));

    homeButton->setParent(filesWidget);

    return filesWidget;
}

QWidget* SettingsWidget::widgetForDate() {
    dateWidget = new QWidget(this);
    dateVLayout = new QVBoxLayout(dateWidget);
    dateTitle = new QLabel("DATE & TIME", dateWidget);
    dateDateRow = new QHBoxLayout(dateWidget);
    dateDateLabel = new QLabel("(DDMMYY): ", dateWidget);
    QString dateString;
    dateString.append(settings->value("Date").toString());
    qDebug()<<"Current Date:"<<dateString;

    dateTimeRow = new QHBoxLayout(dateWidget);
    dateTimeLabel = new QLabel("(HHMMSS): ", dateWidget);
    QString timeString;
    timeString.append(settings->value("Time").toString());
    qDebug()<<"Current Time:"<<timeString;

    dateSubmitButton = new QPushButton("SAVE", dateWidget);
    dayTenButton = new QPushButton("D", dateWidget);
    dayTenButton->setText(dateString[0] + "");
    dayButton = new QPushButton("D", dateWidget);
    dayButton->setText(dateString[1] + "");
    dayTenButton->setCheckable(true);
    dayButton->setCheckable(true);
    monthTenButton = new QPushButton("M", dateWidget);
    monthTenButton->setText(dateString[2] + "");
    monthTenButton->setCheckable(true);
    monthButton = new QPushButton("M", dateWidget);
    monthButton->setText(dateString[3] + "");
    monthButton->setCheckable(true);
    yearTenButton = new QPushButton("Y", dateWidget);
    yearTenButton->setText(dateString[4] + "");
    yearButton = new QPushButton("Y", dateWidget);
    yearButton->setText(dateString[5] + "");
    yearTenButton->setCheckable(true);
    yearButton->setCheckable(true);

    hourTenButton = new QPushButton("h", dateWidget);
    hourTenButton->setText(timeString[0] + "");
    hourButton = new QPushButton("h", dateWidget);
    hourButton->setText(timeString[1] + "");
    hourTenButton->setCheckable(true);
    hourButton->setCheckable(true);
    minTenButton = new QPushButton("m", dateWidget);
    minTenButton->setText(timeString[2] + "");
    minButton = new QPushButton("m", dateWidget);
    minButton->setText(timeString[3] + "");
    minTenButton->setCheckable(true);
    minButton->setCheckable(true);
    secTenButton = new QPushButton("s", dateWidget);
    secTenButton->setText(timeString[4] + "");
    secButton = new QPushButton("s", dateWidget);
    secButton->setText(timeString[5] + "");
    secTenButton->setCheckable(true);
    secButton->setCheckable(true);
    QButtonGroup *dtButtonGroup = new QButtonGroup();
    dtButtonGroup->addButton(dayTenButton);
    dtButtonGroup->addButton(dayButton);
    dtButtonGroup->addButton(monthTenButton);
    dtButtonGroup->addButton(monthButton);
    dtButtonGroup->addButton(yearTenButton);
    dtButtonGroup->addButton(yearButton);

    dtButtonGroup->addButton(hourTenButton);
    dtButtonGroup->addButton(hourButton);
    dtButtonGroup->addButton(minTenButton);
    dtButtonGroup->addButton(minButton);
    dtButtonGroup->addButton(secTenButton);
    dtButtonGroup->addButton(secButton);



    increaseDTButton = new QPushButton("+", dateWidget);
    decreaseDTButton = new QPushButton("-", dateWidget);


    //style
    dateTitle->setFont(titleFont);
    dateTitle->setAlignment(Qt::AlignHCenter);
    dateDateLabel->setFont(labelFontSmall);
    dateTimeLabel->setFont(labelFontSmall);
    dateVLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    monthTenButton->setFont(labelFont);
    monthButton->setFont(labelFont);
    dayTenButton->setFont(labelFont);
    dayButton->setFont(labelFont);
    yearTenButton->setFont(labelFont);
    yearButton->setFont(labelFont);

    hourTenButton->setFont(labelFont);
    hourButton->setFont(labelFont);
    minTenButton->setFont(labelFont);
    minButton->setFont(labelFont);
    secTenButton->setFont(labelFont);
    secButton->setFont(labelFont);
    increaseDTButton->setFont(labelFont);
    increaseDTButton->setMinimumSize(30,30);
    decreaseDTButton->setFont(labelFont);
    decreaseDTButton->setMinimumSize(30,30);
    increaseDTButton->setStyleSheet("color: blue;");
    decreaseDTButton->setStyleSheet("color: blue;");


    //lay it out
    QLabel *forwardSlash = new QLabel("/");
    QLabel *forwardSlash2 = new QLabel("/");
    QLabel *colon = new QLabel(":");
    QLabel *colon2 = new QLabel(":");
    QLabel *space = new QLabel(" ");
    QLabel *space2 = new QLabel(" ");
    forwardSlash->setFont(labelFont);
    forwardSlash2->setFont(labelFont);
    colon->setFont(labelFont);
    colon2->setFont(labelFont);
    space->setFont(labelFont);
    space2->setFont(labelFont);
    dateVLayout->addWidget(dateTitle);
    dateDateRow->addWidget(dateDateLabel);
    dateDateRow->addWidget(dayTenButton);
    dateDateRow->addWidget(dayButton);
    dateDateRow->addWidget(forwardSlash);
    dateDateRow->addWidget(monthTenButton);
    dateDateRow->addWidget(monthButton);
    dateDateRow->addWidget(forwardSlash2);
    dateDateRow->addWidget(yearTenButton);
    dateDateRow->addWidget(yearButton);
    dateDateRow->addWidget(space);
    dateDateRow->addWidget(increaseDTButton);

   // dateDateRow->addWidget(dateDateField);
    dateVLayout->addLayout(dateDateRow);
    dateTimeRow->addWidget(dateTimeLabel);
    dateTimeRow->addWidget(hourTenButton);
    dateTimeRow->addWidget(hourButton);
    dateTimeRow->addWidget(colon);
    dateTimeRow->addWidget(minTenButton);
    dateTimeRow->addWidget(minButton);
    dateTimeRow->addWidget(colon2);
    dateTimeRow->addWidget(secTenButton);
    dateTimeRow->addWidget(secButton);
    dateTimeRow->addWidget(space2);
    dateTimeRow->addWidget(decreaseDTButton);
    dateVLayout->addLayout(dateTimeRow);
    dateVLayout->addWidget(dateSubmitButton);
    dateWidget->setStyleSheet(univStyle);
    dateWidget->setStyleSheet("QPushButton:checked { background-color: lightgreen; }");

    connect(increaseDTButton, SIGNAL(pressed()), this, SLOT(on_increaseDTButtonPressed()));
    connect(decreaseDTButton, SIGNAL(pressed()), this, SLOT(on_decreaseDTButtonPressed()));
    connect(dateSubmitButton, SIGNAL(released()), this, SLOT(dateSubmitPressed()));

    increaseDTButton->setAutoRepeat(true);
    decreaseDTButton->setAutoRepeat(true);

    return dateWidget;
}

QWidget* SettingsWidget::widgetForNet() {
    QWidget *widget;
    QString network = checkNetwork();
    if(network != "false") {
        netWidget = new QWidget(this);
        netVLayout = new QVBoxLayout(netWidget);
        netTitle =new QLabel("NETWORK");
        netIPLabel = new QLabel(network, netWidget);
        netDisButton = new QPushButton("DISCONNECT", netWidget);

        netVLayout->addWidget(netTitle);
        netVLayout->addWidget(netIPLabel);
        netVLayout->addWidget(netDisButton);
        netWidget->setLayout(netVLayout);

        netTitle->setFont(titleFont);
        netIPLabel->setFont(labelFont);
        netVLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        connect(netDisButton, SIGNAL(released()), this, SLOT(netDisButtonPressed()));

        widget = netWidget;
    } else {
        connWidget = new QWidget(this);
        connVLayout = new QVBoxLayout(connWidget);
        connTitle = new QLabel("NETWORK", connWidget);

        connTable = new QTableWidget(0, 1, connWidget);
        connTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        connTable->setSelectionMode(QAbstractItemView::SingleSelection);
        QStringList labels;
        labels << tr("SSID");
        connTable->setHorizontalHeaderLabels(labels);
        connTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        connTable->verticalHeader()->hide();
        connTable->setShowGrid(false);

        QList<QString> availableNets = availableNetworks();
        for(int i = 0; i < availableNets.length(); i++) {
            QString ssid = availableNets.at(i);
            QTableWidgetItem *item = new QTableWidgetItem(ssid);
            int row = connTable->rowCount();
            connTable->insertRow(row);
            connTable->setItem(row, 0, item);
        }

        connPassRow = new QHBoxLayout(connWidget);
        connPassTitle = new QLabel("Password: ", connWidget);
        QString passString;
        passString.append("****");
        connPassField = new KeyLineEdit(passString,connWidget);
        connSubmitButton = new QPushButton("Connect", connWidget);

        connVLayout->addWidget(connTitle);
        connVLayout->addWidget(connTable);
        connPassRow->addWidget(connPassTitle);
        connPassRow->addWidget(connPassField);
        connVLayout->addLayout(connPassRow);
        connVLayout->addWidget(connSubmitButton);

        connTitle->setFont(titleFont);
        connPassTitle->setFont(labelFont);
        connVLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        connect(connSubmitButton, SIGNAL(released()), this, SLOT(connSubmitPressed()));

        widget = connWidget;
    }
    widget->setStyleSheet(univStyle);
    return widget;
}

QWidget* SettingsWidget::widgetForAbout() {

    /*
     * dateVLayout = new QVBoxLayout(dateWidget);
    dateTitle = new QLabel("DATE & TIME", dateWidget);
    dateDateRow = new QHBoxLayout(dateWidget);
    dateDateLabel = new QLabel("(DDMMYY): ", dateWidget);
     */
    aboutWidget = new QWidget(this);
    aboutVLayout = new QVBoxLayout(aboutWidget);
    aboutVersionRow = new QHBoxLayout(aboutWidget);
    aboutCopyrightRow = new QHBoxLayout(aboutWidget);
    aboutTitle = new QLabel("ABOUT", aboutWidget);
    aboutNameLabel = new QLabel(APP_NAME);

    QString copyrightString = "2B Technologies, Inc. ";

    copyrightString.append(COPYRIGHT_DATE);
    QString appVersionString = "Version: ";
    appVersionString.append(APP_VERSION);
    appVersionString.append(".");
    appVersionString.append(BUILD_NUMBER);
    aboutCopyrightLabel = new QLabel(copyrightString);
    aboutVersionLabel = new QLabel(appVersionString);



    aboutVLayout->addWidget(aboutTitle);

    aboutVersionRow->addWidget(aboutNameLabel);
    aboutVersionRow->addWidget(aboutVersionLabel);
    aboutCopyrightRow->addWidget(aboutCopyrightLabel);
    aboutVLayout->addLayout(aboutVersionRow);
    aboutVLayout->addLayout(aboutCopyrightRow);


    aboutTitle->setFont(titleFont);
    aboutNameLabel->setFont(labelFont);
    aboutVersionLabel->setFont(labelFont);
    aboutVersionLabel->setStyleSheet("color: blue;");


    aboutVLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    aboutWidget->setStyleSheet(univStyle);
    return aboutWidget;
}

QWidget* SettingsWidget::widgetForModbus() {
    modbusWidget = new QWidget(this);
    modbusVLayout = new QVBoxLayout(modbusWidget);
    modbusTitle = new QLabel("MODBUS", modbusWidget);
    modbusFirstRow = new QHBoxLayout(modbusWidget);
    modbusCustomEntry = new KeyLineEdit("Custom Entry", modbusWidget);
    modbusCustomAddress = new KeyLineEdit("0", modbusWidget);
    modbusSaveButton = new QPushButton("SAVE", modbusWidget);

    modbusVLayout->addWidget(modbusTitle);
    modbusVLayout->addLayout(modbusFirstRow);
    modbusFirstRow->addWidget(modbusCustomEntry);
    modbusFirstRow->addWidget(modbusCustomAddress);
    modbusVLayout->addWidget(modbusSaveButton);

    modbusTitle->setFont(titleFont);
    modbusSaveButton->setFont(labelFont);

    connect(modbusSaveButton, SIGNAL(released()), this, SLOT(modbusSavePressed()));

    return modbusWidget;
}

void SettingsWidget::homePressed() {
    //invalidate();
    close();
}

void SettingsWidget::showCal() {

    clearView();

    qDebug()<<"in show cal before making widget";
    QWidget *cal = widgetForCal();

    QPushButton *left = new QPushButton(cal);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showModbus()));

    QPushButton *right = new QPushButton(cal);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    //connect(right, SIGNAL(released()), this, SLOT(showAvg()));
    connect(right, SIGNAL(released()), this, SLOT(showRO()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(cal);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}



void SettingsWidget::showRO() {
    clearView();
    QWidget *ro = widgetForRelayOne();

    QPushButton *left = new QPushButton(ro);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    //connect(left, SIGNAL(released()), this, SLOT(showAvg()));
    connect(left, SIGNAL(released()), this, SLOT(showCal()));

    QPushButton *right = new QPushButton(ro);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showVolt()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(ro);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}



void SettingsWidget::showVolt() {
    clearView();
    QWidget *volt = widgetForVoltage();

    QPushButton *left = new QPushButton(volt);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showRO()));

    QPushButton *right = new QPushButton(volt);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showFiles()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(volt);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}

void SettingsWidget::showFiles() {
    clearView();
    QWidget *files = widgetForFiles();

    QPushButton *left = new QPushButton(files);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showVolt()));

    QPushButton *right = new QPushButton(files);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showDate()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(files);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}

void SettingsWidget::showDate() {
    clearView();
    QWidget *files = widgetForDate();

    QPushButton *left = new QPushButton(files);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showFiles()));

    QPushButton *right = new QPushButton(files);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showNet()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(files);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}

void SettingsWidget::showNet() {
    clearView();
    QWidget *widget = widgetForNet();

    QPushButton *left = new QPushButton(widget);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showDate()));

    QPushButton *right = new QPushButton(widget);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showAbout()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(widget);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}

void SettingsWidget::showAbout(){
    clearView();
    QWidget *widget = widgetForAbout();

    QPushButton *left = new QPushButton(widget);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showNet()));

    QPushButton *right = new QPushButton(widget);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showModbus()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(widget);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}

void SettingsWidget::showModbus()
{
    clearView();
    QWidget *widget = widgetForModbus();

    QPushButton *left = new QPushButton(widget);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showAbout()));

    QPushButton *right = new QPushButton(widget);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showCal()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(widget);
    layout->addWidget(right);
    QWidget *w = new QWidget();
    w->setLayout(layout);

    homeButton->setParent(w);
    mainLayout->addWidget(w);
}


void SettingsWidget::clearView() {
    QWidget *widget = mainLayout->itemAt(0)->widget();
    mainLayout->removeWidget(widget);
    widget->deleteLater();
}



void SettingsWidget::calSubmitReleased() {
    QMessageBox msg;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msg.setStyleSheet(msgBoxStyle);
    msg.setText("The new Slope and Zero settings are now saved.");
    msg.exec();

    calSlopeField->setStyleSheet("QLabel { color : black; }");
    calOffsetField->setStyleSheet("QLabel { color : black; }");
    QString calMsg = "c:"+calOffsetField->text();
    sendMessage(calMsg);
    settings->setValue("Zero", calOffsetField->text());

    QString slopeMsg = "s:"+calSlopeField->text();
    sendMessage(slopeMsg);
    settings->setValue("Slope", QString::number(slopeValue));
}


void SettingsWidget::on_calIncreasePressed(){
    if(slopeCheckBox->isChecked()){
        calSlopeField->setStyleSheet("QLabel { color : gray; }");
        slopeValue++;
        if(slopeValue > MAX_SLOPE_VALUE)
            slopeValue = MIN_SLOPE_VALUE;
        else if(slopeValue < MIN_SLOPE_VALUE)
            slopeValue = MIN_SLOPE_VALUE;
        calSlopeField->setText(QString::number(slopeValue/100, 'f', 2));

        //settings->setValue("Slope", slopeValue);
    }else if(offsetCheckBox->isChecked()){
        calOffsetField->setStyleSheet("QLabel { color : gray; }");
        offsetValue++;
        if(offsetValue > MAX_OFFSET_VALUE)
            offsetValue = MIN_OFFSET_VALUE;
        else if(offsetValue < MIN_OFFSET_VALUE)
            offsetValue = MIN_OFFSET_VALUE;
        calOffsetField->setText(QString::number(offsetValue));
        //settings->setValue("Zero", offsetValue);
    }
}

void SettingsWidget::on_calDecreasePressed(){
    if(slopeCheckBox->isChecked()){
        calSlopeField->setStyleSheet("QLabel { color : gray; }");
        slopeValue--;
        if(slopeValue < MIN_SLOPE_VALUE)
            slopeValue = MAX_SLOPE_VALUE;
        calSlopeField->setText(QString::number(slopeValue/100, 'f', 2));


        //settings->setValue("Slope", slopeValue);
    }else if(offsetCheckBox->isChecked()){
        calOffsetField->setStyleSheet("QLabel { color : gray; }");
        offsetValue--;
        if(offsetValue < MIN_OFFSET_VALUE)
            offsetValue = MAX_OFFSET_VALUE;
        calOffsetField->setText(QString::number(offsetValue));
        //settings->setValue("Zero", offsetValue);
    }
}

void SettingsWidget::on_slopeCheckBoxPressed(){
    offsetCheckBox->setChecked(false);
}

void SettingsWidget::on_offsetCheckBoxPressed(){
    slopeCheckBox->setChecked(false);
}

void SettingsWidget::on_relayDecreasePressed(){
    if(rOLowCheckBox->isChecked()){
        rOLowField->setStyleSheet("QLabel { color : gray; }");
        relayOneLowValue--;
        if(relayOneLowValue<MIN_RELAY_VALUE)
            relayOneLowValue = MAX_RELAY_VALUE;
        rOLowField->setText(QString::number(relayOneLowValue));
        settings->setValue("RelOn", relayOneLowValue);
    }else if(rOHighCheckBox->isChecked()){
        rOHighField->setStyleSheet("QLabel { color : gray; }");
        relayOneHighValue--;
        if(relayOneHighValue<MIN_RELAY_VALUE)
            relayOneHighValue = MAX_RELAY_VALUE;
        rOHighField->setText(QString::number(relayOneHighValue));
        settings->setValue("RelOff", relayOneHighValue);
    }

}
void SettingsWidget::on_relayIncreasePressed(){
    if(rOLowCheckBox->isChecked()){
        rOLowField->setStyleSheet("QLabel { color : gray; }");
        relayOneLowValue++;
        if(relayOneLowValue>MAX_RELAY_VALUE)
            relayOneLowValue = MIN_RELAY_VALUE;
        rOLowField->setText(QString::number(relayOneLowValue));
        settings->setValue("RelOn", relayOneLowValue);
    }else if(rOHighCheckBox->isChecked()){
        rOHighField->setStyleSheet("QLabel { color : gray; }");
        relayOneHighValue++;
        if(relayOneHighValue>MAX_RELAY_VALUE)
            relayOneHighValue = MIN_RELAY_VALUE;
        rOHighField->setText(QString::number(relayOneHighValue));
        settings->setValue("RelOff", relayOneHighValue);
    }

}
void SettingsWidget::on_relayLowCheckBoxPressed(){
    rOHighCheckBox->setChecked(false);
}

void SettingsWidget::on_relayHighCheckBoxPressed(){
    rOLowCheckBox->setChecked(false);
}



void SettingsWidget::rOSubmitPressed() {

    QMessageBox msg;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msg.setStyleSheet(msgBoxStyle);
    msg.setText("The new relay settings are now saved.");
    msg.exec();
    QString low = QString::number(relayOneLowValue);
    settings->setValue("RelOn", low);
    sendMessage("l:"+low);


    QString high = QString::number(relayOneHighValue);
    settings->setValue("RelOff", high);
    sendMessage("h:"+high);

    rOLowField->setStyleSheet("QLabel { color : black; }");
    rOHighField->setStyleSheet("QLabel { color : black; }");
}

void SettingsWidget::rOHelpPressed() {
    QMessageBox msg;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msg.setStyleSheet(msgBoxStyle);
    msg.setText("LOW is the O3 in ppb that the relay will remain ON until. HIGH is the O3 in ppb that the relay will turn OFF.");
    msg.exec();
}


void SettingsWidget::voltSubmitPressed() {
    QMessageBox msgBox;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msgBox.setStyleSheet(msgBoxStyle);
    msgBox.setText("The voltage output setting has been saved.");
    msgBox.exec();
    QString msg = "v:"+voltPPBField->text();
    sendMessage(msg);
    settings->setValue("VOut", voltPPBValue);
    voltPPBField->setStyleSheet("QLabel { color : black; }");
}

void SettingsWidget::on_increaseVoltButton(){
    voltPPBValue++;
    if(voltPPBValue > MAX_VOLT_PPB_VALUE){
        voltPPBValue = MIN_VOLT_PPB_VALUE;
    }
    voltPPBField->setText(QString::number(voltPPBValue));
    voltPPBField->setStyleSheet("QLabel { color : gray; }");
}

void SettingsWidget::on_decreaseVoltButton(){
    voltPPBValue--;
    if(voltPPBValue < MIN_VOLT_PPB_VALUE){
        voltPPBValue = MAX_VOLT_PPB_VALUE;
    }
    voltPPBField->setText(QString::number(voltPPBValue));
    voltPPBField->setStyleSheet("QLabel { color : gray; }");
}

void SettingsWidget::on_increaseDTButtonPressed(){
    if(dayTenButton->isChecked()){

        dayTenValue++;
        if(dayTenValue==3){
            if(dayValue > 1)
                dayTenValue = 0;
        }else if(dayTenValue > 3){
            dayTenValue = 0;
        }
        dayTenButton->setText(QString::number(dayTenValue));

    }else if(dayButton->isChecked()){
        dayValue++;
        if(dayTenValue==3){
            if(dayValue > 1)
                dayValue = 0;
        }else if(dayValue > 9){
            dayValue = 0;
        }
        dayButton->setText(QString::number(dayValue));


    }else if(monthTenButton->isChecked()){
        monthTenValue++;
        if(monthTenValue > 1){
              monthTenValue = 0;
        }
        monthTenButton->setText(QString::number(monthTenValue));

    }else if(monthButton->isChecked()){
        monthValue++;
        if(monthTenValue==1){
            if(monthValue > 2)
                monthValue = 0;
        }else if(monthValue > 9){
            monthValue = 0;
        }
        monthButton->setText(QString::number(monthValue));

    }else if(yearTenButton->isChecked()){
        yearTenValue++;
        if(yearTenValue > 9){
            yearTenValue = 0;
        }
        yearTenButton->setText(QString::number(yearTenValue));


    }else if(yearButton->isChecked()){
        yearValue++;
        if(yearValue > 9){
            yearValue = 0;
        }
        yearButton->setText(QString::number(yearValue));

    }else if(hourTenButton->isChecked()){

        hourTenValue++;
        if(hourTenValue==2){
            if(hourValue > 4)
                hourTenValue = 0;
        }else if(hourTenValue > 2){
            hourTenValue = 0;
        }
        hourTenButton->setText(QString::number(hourTenValue));

    }else if(hourButton->isChecked()){
        hourValue++;
        if(hourTenValue==2){
            if(hourValue > 4)
                hourValue = 0;
        }else if(hourValue > 9){
            hourValue = 0;
        }
        hourButton->setText(QString::number(hourValue));


    }else if(minTenButton->isChecked()){
        minTenValue++;
        if(minTenValue > 6){
              minTenValue = 0;
        }
        minTenButton->setText(QString::number(minTenValue));

    }else if(minButton->isChecked()){
        minValue++;
        if(minValue > 9){
            minValue = 0;
        }
        minButton->setText(QString::number(minValue));

    }else if(secTenButton->isChecked()){
        secTenValue++;
        if(secTenValue > 6){
            secTenValue = 0;
        }
        secTenButton->setText(QString::number(secTenValue));


    }else if(secButton->isChecked()){
        secValue++;
        if(secValue > 9){
            secValue = 0;
        }
        secButton->setText(QString::number(secValue));

    }
}

void SettingsWidget::on_decreaseDTButtonPressed(){
    if(dayTenButton->isChecked()){

        dayTenValue--;
        if(dayTenValue==3){
            if(dayValue < 0)
                dayTenValue = 1;
        }else if(dayTenValue < 0){
            dayTenValue = 3;
        }
        dayTenButton->setText(QString::number(dayTenValue));
    }else if(dayButton->isChecked()){
        dayValue--;
        if(dayTenValue==3){
            if(dayValue < 0)
                dayValue = 1;
        }else if(dayValue < 0){
            dayValue = 9;
        }
        dayButton->setText(QString::number(dayValue));
    }else if(monthTenButton->isChecked()){
        monthTenValue--;
        if(monthTenValue < 0){
              monthTenValue = 1;
        }
        monthTenButton->setText(QString::number(monthTenValue));
    }else if(monthButton->isChecked()){
        monthValue--;
        if(monthTenValue==1){
            if(monthValue < 0)
                monthValue = 2;
        }else if(monthValue < 0){
            monthValue = 9;
        }
        monthButton->setText(QString::number(monthValue));
    }else if(yearTenButton->isChecked()){
        yearTenValue--;
        if(yearTenValue < 0){
            yearTenValue = 9;
        }
        yearTenButton->setText(QString::number(yearTenValue));
    }else if(yearButton->isChecked()){
        yearValue--;
        if(yearValue < 0){
            yearValue = 9;
        }
        yearButton->setText(QString::number(yearValue));
    }else if(hourTenButton->isChecked()){

        hourTenValue--;
        if(hourTenValue==2){
            if(hourValue < 0)
                hourTenValue = 3;
        }else if(hourTenValue < 0){
            hourTenValue = 2;
        }
        hourTenButton->setText(QString::number(hourTenValue));

    }else if(hourButton->isChecked()){
        hourValue--;
        if(hourTenValue==2){
            if(hourValue < 0)
                hourValue = 3;
        }else if(hourValue < 0){
            hourValue = 9;
        }
        hourButton->setText(QString::number(hourValue));


    }else if(minTenButton->isChecked()){
        minTenValue--;
        if(minTenValue < 0){
              minTenValue = 6;
        }
        minTenButton->setText(QString::number(minTenValue));

    }else if(minButton->isChecked()){
        minValue--;
        if(minValue < 0){
            minValue = 9;
        }
        minButton->setText(QString::number(minValue));

    }else if(secTenButton->isChecked()){
        secTenValue--;
        if(secTenValue < 0){
            secTenValue = 6;
        }
        secTenButton->setText(QString::number(secTenValue));


    }else if(secButton->isChecked()){
        secValue--;
        if(secValue < 0){
            secValue = 9;
        }
        secButton->setText(QString::number(secValue));

    }
}

void SettingsWidget::copyAllPressed() {
    QStringList extFilter("*.csv");
    QDir currentDir = QDir("/"+device.getDevice_name());
    QStringList list = currentDir.entryList(extFilter);
    FileWriter fileWriter;
    fileWriter.createDataFolder(device.getDevice_name());
    QString filePath = fileWriter.getFull_data_path();
    qDebug()<<filePath;
    bool success = true;
    for(int i = 0; i < list.length(); i++) {
        QString src = "/"+device.getDevice_name()+"/"+list.at(i);
        QString dest = filePath+list.at(i);
        qDebug()<<src;
        qDebug()<<dest;
        if (QFile::copy(src, dest)) {
            qDebug()<<"Data copied successfully";
        } else {
            qDebug()<<"Could not copy data";
            success = false;
        }
    }
    QMessageBox completion;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    completion.setStyleSheet(msgBoxStyle);
    if(success) {
        completion.setText("Files Copied Successfully");
    } else {
        completion.setText("An Error Occurred While Copying Files");
    }
    completion.exec();
}

void SettingsWidget::copySelectedPressed() {
    FileWriter fileWriter;
    fileWriter.createDataFolder(device.getDevice_name());
    QString filePath = fileWriter.getFull_data_path();

    bool success = true;
    for(int i = 0; i < filesTable->selectedItems().length(); i++) {
        QString src = "/"+ device.getDevice_name() + "/" + filesTable->selectedItems().at(i)->text();
        QString dest = filePath+"/"+filesTable->selectedItems().at(i)->text();
        if (QFile::copy(src, dest)) {
            qDebug()<<"Data copied successfully";
        } else {
            qDebug()<<"Could not copy data";
            success = false;
        }
    }
    QMessageBox completion;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    completion.setStyleSheet(msgBoxStyle);
    if(success) {
        completion.setText("Files Copied Successfully");
    } else {
        completion.setText("An Error Occurred While Copying Files");
    }
    completion.exec();
}

void SettingsWidget::deleteAllPressed() {
    QMessageBox msg;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msg.setStyleSheet(msgBoxStyle);
    msg.setText("Do you want to delete all of the files?");
    msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = msg.exec();

    switch(ret) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Ok:
            QStringList extFilter("*.csv");
            QDir currentDir = QDir("/"+device.getDevice_name());
            QStringList list = currentDir.entryList(extFilter);

            for(int i = 0; i < list.length(); i++) {
                QString src = "/" + device.getDevice_name() + "/" + list.at(i);
                QFile file(src);
                file.remove();
            }
            break;
    }
    showFiles();
}

void SettingsWidget::deleteSelectedPressed() {
    QMessageBox msg;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msg.setStyleSheet(msgBoxStyle);
    msg.setText("Do you want to delete these files?");
    msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = msg.exec();

    switch(ret) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Ok:
            for(int i = 0; i < filesTable->selectedItems().length(); i++) {
                QString src = "/" + device.getDevice_name() + "/" + filesTable->selectedItems().at(i)->text();
                QFile file(src);
                file.remove();
            }
            break;
        default:
            break;
    }
    showFiles();
}

void SettingsWidget::dateSubmitPressed() {
    QString dateString = dayTenButton->text() + dayButton->text() + monthTenButton->text() + monthButton->text() + yearTenButton->text() + yearButton->text();
    qDebug()<<"DateString:"<<dateString;
    settings->setValue("Date", dateString);

    QString timeString = hourTenButton->text() + hourButton->text() + minTenButton->text() + minButton->text() + secTenButton->text() + secButton->text();
    qDebug()<<"TimeString:"<<timeString;
    settings->setValue("Time", timeString);

    QString dateMsg = "d:" + dateString;
    sendMessage(dateMsg);

    QString timeMsg = "t:" + timeString;
    sendMessage(timeMsg);

    QMessageBox msgBox;
    msgBoxStyle = "QPushButton { border: none; } QMessageBox { border-width: 2px; border-color: rgb(0, 0, 153); border-radius: 9px; border-style: solid; }";
    msgBox.setStyleSheet(msgBoxStyle);
    msgBox.setText("The date and time have been saved.");
    msgBox.exec();

}

void SettingsWidget::connSubmitPressed() {
    QString prog = "/bin/bash";


    QStringList args_write;
    QString new_net = "printf \" \n network={ \n ssid=\\\""+connTable->selectedItems().at(0)->text()+"\\\" \n psk=\\\""+connPassField->text()+"\\\" \n } \n \" >> /etc/wpa_supplicant/wpa_supplicant.conf";
    args_write<<"-c"<<new_net;
    QProcess *write = new QProcess();
    write->start(prog, args_write);
    write->waitForFinished();

    QStringList args_down;
    args_down<<"-c"<<"sudo ifdown wlan0";

    QProcess *down = new QProcess();
    down->start(prog, args_down);
    down->waitForFinished();

    QStringList args_up;
    args_up<<"-c"<<"sudo ifup wlan0";

    QProcess *up = new QProcess();
    up->start(prog, args_up);
    up->waitForFinished();

    showNet();
}

void SettingsWidget::sendMessage(QString msg) {
    emit sendMsg(msg);
}


QString SettingsWidget::checkNetwork() {
    QNetworkInterface wlan0 = QNetworkInterface::interfaceFromName("wlan0");
    QList<QNetworkAddressEntry> entries = wlan0.addressEntries();
    if(!entries.isEmpty()) {
        return entries.first().ip().toString();
    } else {
        QNetworkInterface eth0 = QNetworkInterface::interfaceFromName("eth0");
        QList<QNetworkAddressEntry> entries_eth0 = eth0.addressEntries();
        if(!entries_eth0.isEmpty()) {
            return entries_eth0.first().ip().toString();
        } else {
            return "false";
        }
    }
}

QList<QString> SettingsWidget::availableNetworks() {
    qDebug()<<"Looking For Available Networks";
    QList<QString> list;
    QString prog = "/bin/bash";
    QStringList args;
    args<<"-c"<<"sudo iwlist wlan0 scan";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();
    QString response = process->readAll();
    qDebug()<<"Response: "<<response;

    QStringList cells = response.split("Cell ");
    qDebug()<<"Cells: "<<cells;
    if(cells.length() > 1) {
        for(int i = 1; i < cells.length(); i++) {
            QString cell = cells.at(i);
            qDebug()<<"Cell: "<<cell;
            QStringList info = cell.split("\n");
            qDebug()<<"Info: "<<info;
            QString ssidLine = info.at(1);
            qDebug()<<"SSID Line: "<<ssidLine;
            QString ssid = ssidLine.split(":").at(1);
            ssid.remove("\"");
            if(!list.contains(ssid)) {
                list<<ssid;
            }
        }
    } else {
        list<<"No Networks Found";
    }
    return list;
}

void SettingsWidget::netDisButtonPressed() {
    QString prog = "/bin/bash";
    QStringList args;
    args<<"-c"<<"sudo iwconfig | grep wlan0";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();

    QString ret = process->readAll();
    qDebug()<<args;
    qDebug()<<ret;
    ret = ret.split("wlan0").at(1);
    qDebug()<<ret;
    ret = ret.split(QString('"')).at(1);
    qDebug()<<ret;

    args.clear();
    args<<"-c"<<"awk '/"+ret+"/ {print NR;exit}' /etc/wpa_supplicant/wpa_supplicant.conf";
    qDebug()<<args;
    process->start(prog, args);
    process->waitForFinished();

    ret = process->readAll();
    qDebug()<<ret;
    int lineNum = ret.toInt();
    int bottom = lineNum-1;
    int top = lineNum+3;
    args.clear();
    args<<"-c"<<"sudo sed -i.back -e '"+QString::number(bottom)+","+QString::number(top)+"d' /etc/wpa_supplicant/wpa_supplicant.conf";
    qDebug()<<args;
    process->start(prog, args);
    process->waitForFinished();

    args.clear();
    args<<"-c"<<"sudo ifdown wlan0";
    process->start(prog, args);
    process->waitForFinished();

    showNet();
}

void SettingsWidget::modbusSavePressed()
{
    ModbusServer::getInstance()->deleteRegister(settings->value("modbus_CUSTOMADDR", 50).toInt());
    settings->setValue("modbus_CUSTOMSTR", modbusCustomEntry->text());
    settings->setValue("modbus_CUSTOMADDR", modbusCustomAddress->text());

    ModbusServer::getInstance()->updateRegister(modbusCustomAddress->text().toInt(), modbusCustomEntry->text());
}

void SettingsWidget::invalidate() {
    clearView();

    QWidget *landing = widgetForCal();
    mainLayout->addWidget(landing);
}
