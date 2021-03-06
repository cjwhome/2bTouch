#include "settingswidget.h"
#include "ui_settingswidget.h"
#include <QSignalMapper>
#include <QDir>
#include <QException>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    initializeViews();
    settings = new QSettings("2B Technologies", "2B Touch");

    XmlDeviceReader *reader = new XmlDeviceReader(":/deviceConfig.xml");
    reader->read();
    device = reader->getADevice(3);
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

    homeButton = new QPushButton();
    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    homeButton->setFixedSize(buttonSize);
    homeButton->setIconSize(buttonSize);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

    regButtonStyle = "background-color: rgba(255, 255, 255, 0); color: #000000";
    selButtonStyle = "background-color: #002266; color: #ffffff";

    titleFont = QFont("Times serif", 30, 4);
    labelFont = QFont("Times serif", 15, 2);
    messageBoxFont = QFont("Times_serif", 10, 2);

    QWidget *landing = widgetForLanding();
    mainLayout->addWidget(landing);
}

QWidget* SettingsWidget::widgetForLanding() {
    //Landing Page - Create Objects
    landingWidget = new QWidget(this);
    landingVLayout = new QVBoxLayout(landingWidget);
    landingPassTitle = new QLabel("SETTINGS", landingWidget);
    landingPassRow = new QHBoxLayout(landingWidget);
    landingPassPrompt = new QLabel("Password: ", landingWidget);
    landingPassField = new KeyLineEdit(landingWidget);
    landingPassSubmit = new QPushButton(landingWidget);
    landingPassSubmit->setText("GO");
    //TODO: ICON
    //Landing Page - Style Layout
    landingPassTitle->setFont(titleFont);
    landingPassTitle->setAlignment(Qt::AlignHCenter);
    landingPassPrompt->setFont(labelFont);
    //landingPassField->setEchoMode(QLineEdit::Password);
    landingPassSubmit->setFixedHeight(30);
    //Landing Page - Fill Layout
    landingVLayout->addWidget(landingPassTitle);
    landingPassRow->addWidget(landingPassPrompt);
    landingPassRow->addWidget(landingPassField);
    landingVLayout->addLayout(landingPassRow);
    landingVLayout->addWidget(landingPassSubmit);
    landingVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    landingWidget->setLayout(landingVLayout);
    //Landing Page - Connect Buttons
    connect(landingPassSubmit, SIGNAL(released()), this, SLOT(landingSubmit()));

    homeButton->setParent(landingWidget);
    landingWidget->setStyleSheet(univStyle);

    //landingPad = new Keypad(landingPassField, false, landingWidget);

    return landingWidget;
}

QWidget* SettingsWidget::widgetForCal() {
    //Calibration
    calWidget = new QWidget(this);
    calVLayout = new QVBoxLayout(calWidget);
    calTitle = new QLabel("CALIBRATION");
    calSlopeRow = new QHBoxLayout(calWidget);
    calSlopeLabel = new QLabel("Slope: ");
    calSlopeField = new KeyLineEdit(calWidget);
    calOffsetRow= new QHBoxLayout(calWidget);
    calOffsetLabel= new QLabel("Offset: ");
    calOffsetField = new KeyLineEdit(calWidget);
    calSubmit = new QPushButton("SAVE", calWidget);
    //Styling
    calTitle->setFont(titleFont);
    calTitle->setAlignment(Qt::AlignHCenter);
    calSlopeLabel->setFont(labelFont);
    calOffsetLabel->setFont(labelFont);
    calSubmit->setFixedHeight(30);
    calVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Calibration - Fill Layout
    calVLayout->addWidget(calTitle);
    calSlopeRow->addWidget(calSlopeLabel);
    calSlopeRow->addWidget(calSlopeField);
    calVLayout->addLayout(calSlopeRow);
    calOffsetRow->addWidget(calOffsetLabel);
    calOffsetRow->addWidget(calOffsetField);
    calVLayout->addLayout(calOffsetRow);
    calVLayout->addWidget(calSubmit);
    calWidget->setLayout(calVLayout);
    calWidget->setStyleSheet(univStyle);
    //Calibration - Connect Buttons
    connect(calSubmit, SIGNAL(released()), this, SLOT(calSubmitReleased()));

    homeButton->setParent(calWidget);

    calOffsetField->setText(settings->value("Zero").toString());
    calSlopeField->setText(settings->value("Slope").toString());

    //calSlopePad = new Keypad(calSlopeField, false, calWidget);
    //calOffPad = new Keypad(calOffsetField, false, calWidget);

    return calWidget;
}

QWidget* SettingsWidget::widgetForAvg() {
    //Averaging
    avgWidget = new QWidget(this);
    avgVLayout = new QVBoxLayout(avgWidget);
    avgTitle = new QLabel("AVERAGING", avgWidget);
    avgRowOne = new QHBoxLayout(avgWidget);
    avgTwoSecButton = new QPushButton("5 s", avgWidget);
    avgTenSecButton = new QPushButton("10 s", avgWidget);
    avgRowTwo = new QHBoxLayout(avgWidget);
    avgOneMinButton = new QPushButton("1 m", avgWidget);
    avgOneHourButton = new QPushButton("1 hr", avgWidget);
    //TODO: ICON
    //Styling
    avgTitle->setFont(titleFont);
    avgTitle->setAlignment(Qt::AlignHCenter);
    avgTwoSecButton->setFixedSize(60, 60);
    avgTenSecButton->setFixedSize(60, 60);
    avgOneMinButton->setFixedSize(60, 60);
    avgOneHourButton->setFixedSize(60, 60);
    avgVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Aveaging - Fill Layout
    avgVLayout->addWidget(avgTitle);
    avgRowOne->addWidget(avgTwoSecButton);
    avgRowOne->addWidget(avgTenSecButton);
    avgVLayout->addLayout(avgRowOne);
    avgRowTwo->addWidget(avgOneMinButton);
    avgRowTwo->addWidget(avgOneHourButton);
    avgVLayout->addLayout(avgRowTwo);
    avgWidget->setLayout(avgVLayout);
    avgWidget->setStyleSheet(univStyle);
    //AVeraging - Connect Buttons
    connect(avgTwoSecButton, SIGNAL(released()),this, SLOT(twoSecPressed()));
    connect(avgTenSecButton, SIGNAL(released()),this, SLOT(tenSecPressed()));
    connect(avgOneMinButton, SIGNAL(released()),this, SLOT(oneMinPressed()));
    connect(avgOneHourButton, SIGNAL(released()),this, SLOT(oneHourPressed()));

    int selButton = settings->value("Avg").toInt();
    if (selButton == 0) {
        avgTwoSecButton->setStyleSheet(selButtonStyle);
    } else if (selButton == 1) {
        avgTenSecButton->setStyleSheet(selButtonStyle);
    } else if (selButton == 2) {
        avgOneMinButton->setStyleSheet(selButtonStyle);
    } else if (selButton == 4) {
        avgOneHourButton->setStyleSheet(selButtonStyle);
    }

    homeButton->setParent(avgWidget);

    return avgWidget;
}

QWidget* SettingsWidget::widgetForRelayOne() {
    //RelayOne
    rOWidget = new QWidget(this);
    rOVLayout = new QVBoxLayout(rOWidget);
    relayOneTitle = new QLabel("RELAY ONE", rOWidget);
    rOLowRow = new QHBoxLayout(rOWidget);
    rOLowLabel = new QLabel("↓LOW", rOWidget);
    rOLowField = new KeyLineEdit(rOWidget);
    rOHighRow = new QHBoxLayout(rOWidget);
    rOHighLabel = new QLabel("HIGH↑", rOWidget);
    rOHighField = new KeyLineEdit(rOWidget);
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
    //Styling
    relayOneTitle->setFont(titleFont);
    relayOneTitle->setAlignment(Qt::AlignHCenter);
    //rOLowButton->setFixedHeight(60);
    //rOHighButton->setFixedHeight(60);
    rOVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Relay One - Fill Layout
    rOVLayout->addWidget(relayOneTitle);
    rOLowRow->addWidget(rOLowLabel);
    rOLowRow->addWidget(rOLowField);
    rOVLayout->addLayout(rOLowRow);
    rOHighRow->addWidget(rOHighLabel);
    rOHighRow->addWidget(rOHighField);
    rOVLayout->addLayout(rOHighRow);
    rOVLayout->addWidget(rOSubmitButton);
    //rORow->addWidget(rOLowButton);
    //rORow->addWidget(rOHighButton);
    //rOVLayout->addLayout(rORow);
    rOHelpButton->setGeometry(320, 15, 30, 30);
    rOWidget->setLayout(rOVLayout);
    rOWidget->setStyleSheet(univStyle);
    //Relay One - Connect Buttons
    //connect(rOLowButton, SIGNAL(released()), this, SLOT(rOLowPressed()));
    //connect(rOHighButton, SIGNAL(released()), this, SLOT(rOHighPressed()));
    connect(rOSubmitButton, SIGNAL(released()), this, SLOT(rOSubmitPressed()));
    connect(rOHelpButton, SIGNAL(released()), this, SLOT(rOHelpPressed()));

    float low = settings->value("Rel1On").toFloat();
    low = low / 10;
    rOLowField->setText(QString::number(low));

    float high = settings->value("Rel1Off").toFloat();
    high = high / 10;
    rOHighField->setText(QString::number(high));

   //rOLowPad = new Keypad(rOLowField, false, rOWidget);
    //rOHighPad / new Keypad(rOHighField,false, rOWidget);

    homeButton->setParent(rOWidget);

    return rOWidget;
}

QWidget* SettingsWidget::widgetForRelayTwo() {
    //Relay Two
    rTWidget = new QWidget(this);
    rTVLayout = new QVBoxLayout(rTWidget);
    rTTitle = new QLabel("RELAY TWO", rTWidget);
    rTHelpButton = new QPushButton(rTWidget);
    rTHelpButton->setIcon(QIcon(":/buttons/pics/help-icon.png"));
    rTHelpButton->setFixedSize(buttonSize);
    rTHelpButton->setIconSize(buttonSize);
    rTModeHLayout = new QHBoxLayout(rTWidget);
    rTModeLabel = new QLabel("Mode: ", rTWidget);
    rTOzoneButton = new QPushButton("Ozone", rTWidget);
    rTDiagnosticsButton = new QPushButton("Diagnostics", rTWidget);
    rTDiagnosticsLabel = new QLabel("Diagnostic Testing Components:");
    //TODO: Create Diagnostic Testing Buttons
    //Styling
    rTTitle->setFont(titleFont);
    rTTitle->setAlignment(Qt::AlignHCenter);
    rTHelpButton->setGeometry(320, 15, 31, 30);
    rTModeLabel->setFont(labelFont);
    rTDiagnosticsLabel->setFont(labelFont);
    rTVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Relay Two - Fill Layout
    rTVLayout->addWidget(rTTitle);
    rTModeHLayout->addWidget(rTModeLabel);
    rTModeHLayout->addWidget(rTOzoneButton);
    rTModeHLayout->addWidget(rTDiagnosticsButton);
    rTVLayout->addLayout(rTModeHLayout);
    rTVLayout->addWidget(rTDiagnosticsLabel);
    rTWidget->setLayout(rTVLayout);
    rTWidget->setStyleSheet(univStyle);
    //TODO: Fill Diagnostic Buttons
    //Relay Two - Connect Buttons
    connect(rTOzoneButton, SIGNAL(released()), this, SLOT(rTOzonePresed()));
    connect(rTDiagnosticsButton, SIGNAL(released()), this, SLOT(rTDiagnosticsPressed()));
    connect(rTHelpButton, SIGNAL(released()), this, SLOT(rTHelpPressed()));

    homeButton->setParent(rTWidget);

    return rTWidget;
}

QWidget* SettingsWidget::widgetForVoltage() {
    //Voltage
    voltWidget = new QWidget(this);
    voltVLayout = new QVBoxLayout(voltWidget);
    voltTitle = new QLabel("ANALOG OUTPUT", voltWidget);
    voltVoltLabel = new QLabel("2.5 V & 20 mA", voltWidget);
    voltPPBRow = new QHBoxLayout(voltWidget);
    voltPPBField = new KeyLineEdit(voltWidget);
    voltPPBLabel = new QLabel("ppb", voltWidget);
    voltSubmitButton = new QPushButton("SAVE", voltWidget);
    //Styling
    voltTitle->setFont(titleFont);
    voltTitle->setAlignment(Qt::AlignHCenter);
    voltVoltLabel->setFont(labelFont);
    voltVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Voltage - Fill Layout
    voltVLayout->addWidget(voltTitle);
    voltVLayout->addWidget(voltVoltLabel);
    voltPPBRow->addWidget(voltPPBField);
    voltPPBRow->addWidget(voltPPBLabel);
    voltVLayout->addLayout(voltPPBRow);
    voltVLayout->addWidget(voltSubmitButton);
    voltWidget->setLayout(voltVLayout);
    voltWidget->setStyleSheet(univStyle);

    QString v = settings->value("VOut").toString();
    voltPPBField->setText(v);
    //voltPad = new Keypad(voltPPBField, false, voltWidget);

    connect(voltSubmitButton, SIGNAL(pressed()), this, SLOT(voltSubmitPressed()));

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
    QDir currentDir = QDir("/"+device.device_name);
    QStringList list = currentDir.entryList(extFilter);
    for(int i = 0; i < list.length(); i++) {
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(list.at(i));
        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);

        QFileInfo fileInfo("/"+device.device_name+"/"+list.at(i));
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
    dateDateLabel = new QLabel("Date (DDMMYY): ", dateWidget);
    dateDateField = new KeyLineEdit(dateWidget);
    dateTimeRow = new QHBoxLayout(dateWidget);
    dateTimeLabel = new QLabel("Time (HHMMSS): ", dateWidget);
    dateTimeField = new KeyLineEdit(dateWidget);
    dateSubmitButton = new QPushButton("SAVE", dateWidget);

    dateTitle->setFont(titleFont);
    dateTitle->setAlignment(Qt::AlignHCenter);
    dateDateLabel->setFont(labelFont);
    dateTimeLabel->setFont(labelFont);
    dateVLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    dateVLayout->addWidget(dateTitle);
    dateDateRow->addWidget(dateDateLabel);
    dateDateRow->addWidget(dateDateField);
    dateVLayout->addLayout(dateDateRow);
    dateTimeRow->addWidget(dateTimeLabel);
    dateTimeRow->addWidget(dateTimeField);
    dateVLayout->addLayout(dateTimeRow);
    dateVLayout->addWidget(dateSubmitButton);
    dateWidget->setStyleSheet(univStyle);

    dateDateField->setText(settings->value("Date").toString());
    //dateDatePad = new Keypad(dateDateField, false, dateWidget);
    dateTimeField->setText(settings->value("Time").toString());
    //dateTimePad = new Keypad(dateTimeField, false, dateWidget);

    connect(dateSubmitButton, SIGNAL(released()), this, SLOT(dateSubmitPressed()));

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
        connPassField = new KeyLineEdit(connWidget);
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

QWidget* SettingsWidget::widgetForPassChange() {
    cpWidget = new QWidget(this);
    cpVLayout = new QVBoxLayout(cpWidget);
    cpTitle = new QLabel("PASSWORD", cpWidget);
    cpPassRow = new QHBoxLayout(cpWidget);
    cpPassLabel = new QLabel("Password: ", cpWidget);
    cpPassText = new KeyLineEdit(cpWidget);
    cpConfRow = new QHBoxLayout(cpWidget);
    cpConfirmLabel = new QLabel("Confirm: ", cpWidget);
    cpConfText = new KeyLineEdit(cpWidget);
    cpSaveButton = new QPushButton("SAVE", cpWidget);
    //Styling
    cpTitle->setFont(titleFont);
    cpTitle->setAlignment(Qt::AlignHCenter);
    cpPassLabel->setFont(labelFont);
    //cpPassText->setEchoMode(QLineEdit::Password);
    cpConfirmLabel->setFont(labelFont);
    //cpConfText->setEchoMode(QLineEdit::Password);
    cpVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    cpVLayout->addWidget(cpTitle);
    cpPassRow->addWidget(cpPassLabel);
    cpPassRow->addWidget(cpPassText);
    cpVLayout->addLayout(cpPassRow);
    cpConfRow->addWidget(cpConfirmLabel);
    cpConfRow->addWidget(cpConfText);
    cpVLayout->addLayout(cpConfRow);
    cpVLayout->addWidget(cpSaveButton);
    cpWidget->setLayout(cpVLayout);
    cpWidget->setStyleSheet(univStyle);

    connect(cpSaveButton, SIGNAL(released()), this, SLOT(changePassPressed()));

    homeButton->setParent(cpWidget);

    //cpPassPad = new Keypad(cpPassText, false, cpWidget);
    //cpConfPad = new Keypad(cpConfText, false, cpWidget);

    return cpWidget;
}

void SettingsWidget::homePressed() {
    invalidate();
    close();
}

void SettingsWidget::showCal() {
    clearView();
    QWidget *cal = widgetForCal();

    QPushButton *left = new QPushButton(cal);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showPassChange()));

    QPushButton *right = new QPushButton(cal);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showAvg()));

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

void SettingsWidget::showAvg() {
    clearView();
    QWidget *avg = widgetForAvg();

    QPushButton *left = new QPushButton(avg);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showCal()));

    QPushButton *right = new QPushButton(avg);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showRO()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(avg);
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
    connect(left, SIGNAL(released()), this, SLOT(showAvg()));

    QPushButton *right = new QPushButton(ro);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showRT()));

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

void SettingsWidget::showRT() {
    clearView();
    QWidget *rt = widgetForRelayTwo();

    QPushButton *left = new QPushButton(rt);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showRO()));

    QPushButton *right = new QPushButton(rt);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showVolt()));

    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(rt);
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
    connect(left, SIGNAL(released()), this, SLOT(showRT()));

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
    connect(right, SIGNAL(released()), this, SLOT(showPassChange()));

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

void SettingsWidget::showPassChange() {
    clearView();
    QWidget *files = widgetForPassChange();

    QPushButton *left = new QPushButton(files);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showNet()));

    QPushButton *right = new QPushButton(files);
    right->setIcon(QIcon(":/buttons/pics/right-arrow-icon.png"));
    connect(right, SIGNAL(released()), this, SLOT(showCal()));

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

void SettingsWidget::clearView() {
    QWidget *widget = mainLayout->itemAt(0)->widget();
    mainLayout->removeWidget(widget);
    widget->deleteLater();
}

void SettingsWidget::landingSubmit() {
    QString passTest = landingPassField->text();
    QString password = settings->value("Password", "password").toString();
    qDebug()<<"Password = "<<password;
    qDebug()<<"PassTest = "<<passTest;
    if(passTest == password) {
        showCal();
    } else {
        QMessageBox msg;
        msg.setText("Incorrect Password");
        msg.exec();
    }
}

void SettingsWidget::calSubmitReleased() {
    QString calMsg = "c:"+calOffsetField->text();
    sendMessage(calMsg);
    settings->setValue("Zero", calOffsetField->text());

    QString slopeMsg = "s:"+calSlopeField->text();
    sendMessage(slopeMsg);
    settings->setValue("Slope", calSlopeField->text());
}

void SettingsWidget::twoSecPressed() {
    sendMessage("a:0");
    settings->setValue("Avg", "0");
    avgTwoSecButton->setStyleSheet(selButtonStyle);
    avgTenSecButton->setStyleSheet(regButtonStyle);
    avgOneMinButton->setStyleSheet(regButtonStyle);
    avgOneHourButton->setStyleSheet(regButtonStyle);
}

void SettingsWidget::tenSecPressed() {
    sendMessage("a:1");
    settings->setValue("Avg", "1");
    avgTwoSecButton->setStyleSheet(regButtonStyle);
    avgTenSecButton->setStyleSheet(selButtonStyle);
    avgOneMinButton->setStyleSheet(regButtonStyle);
    avgOneHourButton->setStyleSheet(regButtonStyle);
}

void SettingsWidget::oneMinPressed() {
    sendMessage("a:2");
    settings->setValue("Avg", "2");
    avgTwoSecButton->setStyleSheet(regButtonStyle);
    avgTenSecButton->setStyleSheet(regButtonStyle);
    avgOneMinButton->setStyleSheet(selButtonStyle);
    avgOneHourButton->setStyleSheet(regButtonStyle);
}

void SettingsWidget::oneHourPressed() {
    sendMessage("a:4");
    settings->setValue("Avg", "4");
    avgTwoSecButton->setStyleSheet(regButtonStyle);
    avgTenSecButton->setStyleSheet(regButtonStyle);
    avgOneMinButton->setStyleSheet(regButtonStyle);
    avgOneHourButton->setStyleSheet(selButtonStyle);
}

/*void SettingsWidget::rOLowPressed() {
    sendMessage("o:a");
}

void SettingsWidget::rOHighPressed() {
    sendMessage("o:b");
}*/

void SettingsWidget::rOSubmitPressed() {
    float lowf = rOLowField->text().toFloat();
    QString low = QString::number(lowf * 10);
    settings->setValue("Rel1On", low);
    sendMessage("l:"+low);

    float highf = rOHighField->text().toFloat();
    QString high = QString::number(highf * 10);
    settings->setValue("Rel1Off", high);
    sendMessage("h:"+high);
}

void SettingsWidget::rOHelpPressed() {
    QMessageBox msg;
    msg.setFont(messageBoxFont);
    msg.setText("**RELAY HELP**\n\nRelay will be CLOSED when O3 is less than LOW\nRelay will be OPEN when O3 is greater than HIGH");
    msg.exec();
}

void SettingsWidget::rTOzonePresed()  {
    sendMessage("t:a");
}

void SettingsWidget::rTDiagnosticsPressed() {
    sendMessage("t:b");
}

void SettingsWidget::rTHelpPressed() {
    QMessageBox msg;
    msg.setText("This is the text for the relay two help message");
    msg.exec();
}

void SettingsWidget::voltSubmitPressed() {
    QString msg = "v:"+voltPPBField->text();
    sendMessage(msg);
}

void SettingsWidget::copyAllPressed() {
    QStringList extFilter("*.csv");
    QDir currentDir = QDir("/"+device.device_name);
    QStringList list = currentDir.entryList(extFilter);
    FileWriter fileWriter;
    fileWriter.createDataFolder(device.device_name);
    QString filePath = fileWriter.getFull_data_path();
    qDebug()<<filePath;
    bool success = true;
    for(int i = 0; i < list.length(); i++) {
        QString src = "/"+device.device_name+"/"+list.at(i);
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
    if(success) {
        completion.setText("Files Copied Successfully");
    } else {
        completion.setText("An Error Occurred While Copying Files");
    }
    completion.exec();
}

void SettingsWidget::copySelectedPressed() {
    FileWriter fileWriter;
    fileWriter.createDataFolder(device.device_name);
    QString filePath = fileWriter.getFull_data_path();

    bool success = true;
    for(int i = 0; i < filesTable->selectedItems().length(); i++) {
        QString src = "/"+ device.device_name + "/" + filesTable->selectedItems().at(i)->text();
        QString dest = filePath+"/"+filesTable->selectedItems().at(i)->text();
        if (QFile::copy(src, dest)) {
            qDebug()<<"Data copied successfully";
        } else {
            qDebug()<<"Could not copy data";
            success = false;
        }
    }
    QMessageBox completion;
    if(success) {
        completion.setText("Files Copied Successfully");
    } else {
        completion.setText("An Error Occurred While Copying Files");
    }
    completion.exec();
}

void SettingsWidget::deleteAllPressed() {
    QMessageBox msg;
    msg.setText("Do you want to delete all of the files?");
    msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = msg.exec();

    switch(ret) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Ok:
            QStringList extFilter("*.csv");
            QDir currentDir = QDir("/"+device.device_name);
            QStringList list = currentDir.entryList(extFilter);

            for(int i = 0; i < list.length(); i++) {
                QString src = "/" + device.device_name + "/" + list.at(i);
                QFile file(src);
                file.remove();
            }
            break;
    }
    showFiles();
}

void SettingsWidget::deleteSelectedPressed() {
    QMessageBox msg;
    msg.setText("Do you want to delete these files?");
    msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = msg.exec();

    switch(ret) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Ok:
            for(int i = 0; i < filesTable->selectedItems().length(); i++) {
                QString src = "/" + device.device_name + "/" + filesTable->selectedItems().at(i)->text();
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
    QString dateMsg = "d:" + dateDateField->text();
    sendMessage(dateMsg);

    QString timeMsg = "t:" + dateTimeField->text();
    sendMessage(timeMsg);
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

void SettingsWidget::changePassPressed() {
    QString pass1 = cpPassText->text();
    QString pass2 = cpConfText->text();
    if(pass1 == pass2) {
        settings->setValue("Password", pass1);
        QMessageBox msg;
        msg.setText("Password Changed");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setText("Passwords Do Not Match");
        msg.exec();
    }
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

void SettingsWidget::invalidate() {
    clearView();

    QWidget *landing = widgetForLanding();
    mainLayout->addWidget(landing);
}
