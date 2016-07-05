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
    device = reader->getADevice(4);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::initializeViews() {
    mainLayout = new QVBoxLayout(this);

    buttonSize = QSize(35, 31);
    this->setStyleSheet("QPushButton { border: none;}");

    homeButton = new QPushButton();
    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    homeButton->setFixedSize(buttonSize);
    homeButton->setIconSize(buttonSize);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

    regButtonStyle = "background-color: rgba(255, 255, 255, 0); color: #000000";
    selButtonStyle = "background-color: #002266; color: #ffffff";

    titleFont = QFont("Times serif", 30, 4);
    labelFont = QFont("Times serif", 15, 2);

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
    landingPassField = new QLineEdit(landingWidget);
    landingPassSubmit = new QPushButton(landingWidget);
    landingPassSubmit->setText("GO");
    //TODO: ICON
    //Landing Page - Style Layout
    landingPassTitle->setFont(titleFont);
    landingPassTitle->setAlignment(Qt::AlignHCenter);
    landingPassPrompt->setFont(labelFont);
    landingPassField->setEchoMode(QLineEdit::Password);
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

    landingPad = new Keypad(landingPassField, false, landingWidget);

    return landingWidget;
}

QWidget* SettingsWidget::widgetForCal() {
    //Calibration
    calWidget = new QWidget(this);
    calVLayout = new QVBoxLayout(calWidget);
    calTitle = new QLabel("CALIBRATION");
    calSlopeRow = new QHBoxLayout(calWidget);
    calSlopeLabel = new QLabel("Slope: ");
    calSlopeField = new QLineEdit(calWidget);
    calOffsetRow= new QHBoxLayout(calWidget);
    calOffsetLabel= new QLabel("Offset: ");
    calOffsetField = new QLineEdit(calWidget);
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
    //Calibration - Connect Buttons
    connect(calSubmit, SIGNAL(released()), this, SLOT(calSubmitReleased()));

    homeButton->setParent(calWidget);

    calOffsetField->setText(settings->value("Zero").toString());
    calSlopeField->setText(settings->value("Slope").toString());

    calSlopePad = new Keypad(calSlopeField, false, calWidget);
    calOffPad = new Keypad(calOffsetField, false, calWidget);

    return calWidget;
}

QWidget* SettingsWidget::widgetForAvg() {
    //Averaging
    avgWidget = new QWidget(this);
    avgVLayout = new QVBoxLayout(avgWidget);
    avgTitle = new QLabel("AVERAGING", avgWidget);
    avgRowOne = new QHBoxLayout(avgWidget);
    avgTwoSecButton = new QPushButton("2 s", avgWidget);
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
    //AVeraging - Connect Buttons
    QSignalMapper *signalMapper = new QSignalMapper(this);
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
    rORow = new QHBoxLayout(rOWidget);
    rOLowButton = new QPushButton("↓LOW", rOWidget);
    rOHighButton = new QPushButton("HIGH↑", rOWidget);
    QPixmap pixmap(":/buttons/pics/help-icon.png");
    QIcon icon(pixmap);
    rOHelpButton = new QPushButton(rOWidget);
    rOHelpButton->setIcon(icon);
    rOHelpButton->setFixedSize(buttonSize);
    rOHelpButton->setIconSize(buttonSize);
    //Styling
    relayOneTitle->setFont(titleFont);
    relayOneTitle->setAlignment(Qt::AlignHCenter);
    rOLowButton->setFixedHeight(60);
    rOHighButton->setFixedHeight(60);
    rOVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Relay One - Fill Layout
    rOVLayout->addWidget(relayOneTitle);
    rORow->addWidget(rOLowButton);
    rORow->addWidget(rOHighButton);
    rOVLayout->addLayout(rORow);
    rOHelpButton->setGeometry(320, 15, 30, 30);
    rOWidget->setLayout(rOVLayout);
    //Relay One - Connect Buttons
    connect(rOLowButton, SIGNAL(released()), this, SLOT(rOLowPressed()));
    connect(rOHighButton, SIGNAL(released()), this, SLOT(rOHighPressed()));
    connect(rOHelpButton, SIGNAL(released()), this, SLOT(rOHelpPressed()));

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
    voltVoltLabel = new QLabel("2.5 V & 20 mA = xxx ppb", voltWidget);
    //Styling
    voltTitle->setFont(titleFont);
    voltTitle->setAlignment(Qt::AlignHCenter);
    voltVoltLabel->setFont(labelFont);
    voltVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //Voltage - Fill Layout
    voltVLayout->addWidget(voltTitle);
    voltVLayout->addWidget(voltVoltLabel);
    voltWidget->setLayout(voltVLayout);

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
    }

    filesDeleteActionsMenu = new QHBoxLayout(filesWidget);
    filesDeleteAllButton = new QPushButton("Delete All", filesWidget);
    filesDeleteSelectedButton = new QPushButton("Delete Selected", filesWidget);

    filesVLayout->addWidget(filesTitle);
    filesCopyActionsMenu->addWidget(filesCopyAllButton);
    filesCopyActionsMenu->addWidget(filesCopySelectedButton);
    filesVLayout->addLayout(filesCopyActionsMenu);
    filesVLayout->addWidget(filesTable);
    filesDeleteActionsMenu->addWidget(filesDeleteAllButton);
    filesDeleteActionsMenu->addWidget(filesDeleteSelectedButton);
    filesVLayout->addLayout(filesDeleteActionsMenu);

    filesTitle->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    connect(filesCopyAllButton, SIGNAL(released()), this, SLOT(copyAllPressed()));
    connect(filesCopySelectedButton, SIGNAL(released()), this, SLOT(copySelectedPressed()));
    connect(filesDeleteAllButton, SIGNAL(released()), this, SLOT(deleteAllPressed()));
    connect(filesDeleteSelectedButton, SIGNAL(released()), this, SLOT(deleteSelectedPressed()));

    homeButton->setParent(filesWidget);

    return filesWidget;
}

QWidget* SettingsWidget::widgetForPassChange() {
    cpWidget = new QWidget(this);
    cpVLayout = new QVBoxLayout(cpWidget);
    cpTitle = new QLabel("PASSWORD", cpWidget);
    cpPassRow = new QHBoxLayout(cpWidget);
    cpPassLabel = new QLabel("Password: ", cpWidget);
    cpPassText = new QLineEdit(cpWidget);
    cpConfRow = new QHBoxLayout(cpWidget);
    cpConfirmLabel = new QLabel("Confirm: ", cpWidget);
    cpConfText = new QLineEdit(cpWidget);
    cpSaveButton = new QPushButton("SAVE", cpWidget);
    //Styling
    cpTitle->setFont(titleFont);
    cpTitle->setAlignment(Qt::AlignHCenter);
    cpPassLabel->setFont(labelFont);
    cpPassText->setEchoMode(QLineEdit::Password);
    cpConfirmLabel->setFont(labelFont);
    cpConfText->setEchoMode(QLineEdit::Password);
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

    connect(cpSaveButton, SIGNAL(released()), this, SLOT(changePassPressed()));

    homeButton->setParent(cpWidget);

    cpPassPad = new Keypad(cpPassText, false, cpWidget);
    cpConfPad = new Keypad(cpConfText, false, cpWidget);

    return cpWidget;
}

void SettingsWidget::homePressed() {
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
    connect(right, SIGNAL(released()), this, SLOT(showPassChange()));

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

void SettingsWidget::showPassChange() {
    clearView();
    QWidget *files = widgetForPassChange();

    QPushButton *left = new QPushButton(files);
    left->setIcon(QIcon(":/buttons/pics/left-arrow-icon.gif"));
    connect(left, SIGNAL(released()), this, SLOT(showFiles()));

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

void SettingsWidget::rOLowPressed() {
    sendMessage("o:a");
}

void SettingsWidget::rOHighPressed() {
    sendMessage("o:b");
}

void SettingsWidget::rOHelpPressed() {
    QMessageBox msg;
    msg.setText("This is the text for the relay one help message");
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

void SettingsWidget::copyAllPressed() {
    QStringList extFilter("*.csv");
    QDir currentDir = QDir("/"+device.device_name);
    QStringList list = currentDir.entryList(extFilter);
    FileWriter fileWriter;
    bool test = fileWriter.createDataFolder(device.device_name);
    QString filePath = fileWriter.getFull_data_path();
    qDebug()<<filePath;
    for(int i = 0; i < list.length(); i++) {
        QString src = QDir::currentPath()+"/"+list.at(i);
        QString dest = filePath+"/"+list.at(i);
        qDebug()<<src;
        qDebug()<<dest;
        if (QFile::copy(src, dest)) {
            qDebug()<<"Data copied successfully";
        } else {
            qDebug()<<"Could not copy data";
        }
    }
}

void SettingsWidget::copySelectedPressed() {
    FileWriter fileWriter;
    bool test = fileWriter.createDataFolder(device.device_name);
    QString filePath = fileWriter.getFull_data_path();

    for(int i = 0; i < filesTable->selectedItems().length(); i++) {
        QString src = "/"+ device.device_name + "/" + filesTable->selectedItems().at(i)->text();
        QString dest = filePath+"/"+filesTable->selectedItems().at(i)->text();
        if (QFile::copy(src, dest)) {
            qDebug()<<"Data copied successfully";
        } else {
            qDebug()<<"Could not copy data";
        }
    }
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
