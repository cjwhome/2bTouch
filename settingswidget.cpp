  #include "settingswidget.h"
#include "ui_settingswidget.h"
#include <QSignalMapper>
#include <QDir>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    initializeViews();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::initializeViews() {
    //Universal Layout
    /*homeButton = new QPushButton(this);
    homeButton->setIcon(QIcon(":/buttons/pics/settings-icon.gif"));
    homeButton->setGeometry(15, (size().height() - 45), 30, 30);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

    QPushButton *Button = new QPushButton(this);
    Button->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    Button->setGeometry(15, (size().height() - 45), 50, 30);

    leftArrow = new QPushButton(this);
    leftArrow->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    leftArrow->setGeometry(32.5, (size().height() / 2), 45, 45);
    connect(leftArrow, SIGNAL(released()), this, SLOT(homePressed()));

    QIcon rightIcon(":/buttons/pics/settings-icon.gif");
    rightArrow = new QPushButton(this);
    rightArrow->setIcon(rightIcon);
    rightArrow->setGeometry(this->size().width() - 55, this->size().height() / 2, 45, 45);
    connect(rightArrow, SIGNAL(released()), this, SLOT(homePressed()));*/

    mainLayout = new QVBoxLayout(this);
    currentIndex = -1;

    QWidget *landing = widgetForLanding();
    mainLayout->addWidget(landing);
}

QWidget* SettingsWidget::widgetForLanding() {
    if(landingWidget) {
        return landingWidget;
    }
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
    //Landing Page - Fill Layout
    landingVLayout->addWidget(landingPassTitle);
    landingPassRow->addWidget(landingPassPrompt);
    landingPassRow->addWidget(landingPassField);
    landingVLayout->addLayout(landingPassRow);
    landingVLayout->addWidget(landingPassSubmit);
    landingVLayout->setAlignment(Qt::AlignHCenter);
    landingWidget->setLayout(landingVLayout);

    //Landing Page - Connect Buttons
    connect(landingPassSubmit, SIGNAL(released()), this, SLOT(landingSubmit()));

    return landingWidget;
}

QWidget* SettingsWidget::widgetForCal() {
    if(calWidget) {
        return calWidget;
    }
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

    return calWidget;
}

QWidget* SettingsWidget::widgetForAvg() {
    if(avgWidget) {
        return avgWidget;
    }
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
    connect(avgTwoSecButton, SIGNAL(released()),this, SLOT(map()));
    connect(avgTenSecButton, SIGNAL(released()),this, SLOT(map()));
    connect(avgOneMinButton, SIGNAL(released()),this, SLOT(map()));
    connect(avgOneHourButton, SIGNAL(released()),this, SLOT(map()));
    signalMapper->setMapping(avgTwoSecButton, 2);
    signalMapper->setMapping(avgTenSecButton, 10);
    signalMapper->setMapping(avgOneMinButton, 60);
    signalMapper->setMapping(avgOneHourButton, 60*60);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changeAvg(int)));



    return avgWidget;
}

QWidget* SettingsWidget::widgetForRelayOne() {
    if(rOWidget) {
        return rOWidget;
    }
    //RelayOne
    rOWidget = new QWidget(this);
    rOVLayout = new QVBoxLayout(rOWidget);
    relayOneTitle = new QLabel("RELAY ONE", rOWidget);
    rORow = new QHBoxLayout(rOWidget);
    rOLowButton = new QPushButton("↓LOW", rOWidget);
    rOHighButton = new QPushButton("HIGH↑", rOWidget);
    QPixmap pixmap(":/buttons/pics/stats-icon.gif");
    QIcon icon(pixmap);
    rOHelpButton = new QPushButton("HELP", rOWidget);
    rOHelpButton->setIcon(icon);
    rOHelpBox = QMessageBox::information(rOWidget, "HELP", "This is the text of the message box", QMessageBox::Ok);
    //Relay One - Fill Layout
    rOVLayout->addWidget(relayOneTitle);
    rORow->addWidget(rOLowButton);
    rORow->addWidget(rOHighButton);
    rOVLayout->addLayout(rORow);
    rOHelpButton->setGeometry(this->size().width()- 30, this->size().height() - 30, 45, 45);
    rOWidget->setLayout(rOVLayout);
    //Relay One - Connect Buttons
    connect(rOLowButton, SIGNAL(released()), this, SLOT(rOLowPressed()));
    connect(rOHighButton, SIGNAL(released()), this, SLOT(rOHighPressed()));

    return rOWidget;
}

QWidget* SettingsWidget::widgetForRelayTwo() {
    if(rTWidget) {
        return rTWidget;
    }
    //Relay Two
    rTWidget = new QWidget(this);
    rTVLayout = new QVBoxLayout(rTWidget);
    rTTitle = new QLabel("RELAY TWO", rTWidget);
    rTModeHLayout = new QHBoxLayout(rTWidget);
    rTModeLabel = new QLabel("Mode: ", rTWidget);
    rTOzoneButton = new QPushButton("Ozone", rTWidget);
    rTDiagnosticsButton = new QPushButton("Diagnostics", rTWidget);
    rTDiagnosticsLabel = new QLabel("Diagnostic Testing Components:");
    //TODO: Create Diagnostic Testing Buttons
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

    return rTWidget;
}

QWidget* SettingsWidget::widgetForVoltage() {
    if(voltWidget) {
        return voltWidget;
    }
    //Voltage
    voltWidget = new QWidget(this);
    voltVLayout = new QVBoxLayout(voltWidget);
    voltTitle = new QLabel("V AND I OUTPUT", voltWidget);
    voltVoltLabel = new QLabel("2.5 V & 20 mA = xxx ppb", voltWidget);
    //Voltage - Fill Layout
    voltVLayout->addWidget(voltTitle);
    voltVLayout->addWidget(voltVoltLabel);
    voltWidget->setLayout(voltVLayout);

    return voltWidget;
}

QWidget* SettingsWidget::widgetForFiles() {
    if(filesWidget) {
        return filesWidget;
    }
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
    QDir dir = QDir("/");
    QStringList files = dir.entryList(QStringList("*"), QDir::Files | QDir::NoSymLinks);
    for(int i = 0; i < files.size(); i++) {
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
    }

    return filesWidget;
}

QWidget* SettingsWidget::widgetForPassChange() {

}

void SettingsWidget::homePressed() {
    close();
}

void SettingsWidget::showCal() {
    clearView();
    QWidget *cal = widgetForCal();
    mainLayout->addWidget(cal);

    QPushButton *left = new QPushButton(cal);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showFiles()));

    QPushButton *right = new QPushButton(cal);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showAvg()));
}

void SettingsWidget::showAvg() {
    clearView();
    QWidget *avg = widgetForAvg();
    mainLayout->addWidget(avg);

    QPushButton *left = new QPushButton(avg);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showCal()));

    QPushButton *right = new QPushButton(avg);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showRO()));
}

void SettingsWidget::showRO() {
    clearView();
    QWidget *ro = widgetForRelayOne();
    mainLayout->addWidget(ro);

    QPushButton *left = new QPushButton(ro);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showAvg()));

    QPushButton *right = new QPushButton(ro);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showRT()));
}

void SettingsWidget::showRT() {
    clearView();
    QWidget *rt = widgetForRelayTwo();
    mainLayout->addWidget(rt);

    QPushButton *left = new QPushButton(rt);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showRO()));

    QPushButton *right = new QPushButton(rt);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showVolt()));
}

void SettingsWidget::showVolt() {
    clearView();
    QWidget *volt = widgetForVoltage();
    mainLayout->addWidget(volt);

    QPushButton *left = new QPushButton(volt);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showRT()));

    QPushButton *right = new QPushButton(volt);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showFiles()));
}

void SettingsWidget::showFiles() {
    clearView();
    QWidget *files = widgetForCal();
    mainLayout->addWidget(files);

    QPushButton *left = new QPushButton(files);
    left->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry(15, (height() / 2), 30, 30);
    connect(left, SIGNAL(released()), this, SLOT(showVolt()));

    QPushButton *right = new QPushButton(files);
    right->setIcon(QIcon(":/buttons/pics/stats-icon.gif"));
    left->setGeometry((width() - 15), (height() / 2), 30, 30);
    connect(right, SIGNAL(released()), this, SLOT(showCal()));
}

void SettingsWidget::showPassChange() {

}

void SettingsWidget::clearView() {
    QWidget *widget = mainLayout->itemAt(0)->widget();
    mainLayout->removeWidget(widget);
    widget->deleteLater();
}

void SettingsWidget::landingSubmit() {
    QString passTest = landingPassField->text();
    if(passTest == "password") {
        //this->setLayout(widgets[0]);
        //mainLayout->addWidget(widgets[0]);
        //showUnivLayout();
        showCal();
    }
}

void SettingsWidget::calSubmitReleased() {

}

void SettingsWidget::changeAvg(int time) {

}

void SettingsWidget::rOLowPressed() {

}

void SettingsWidget::rOHighPressed() {

}

void SettingsWidget::rTOzonePresed()  {

}

void SettingsWidget::rTDiagnosticsPressed() {

}
