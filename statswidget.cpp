#include "statswidget.h"
#include "ui_statswidget.h"
#include <QDebug>

StatsWidget::StatsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWidget)
{
    ui->setupUi(this);

    QSize buttonSize(30, 30);

    homeButton = new QPushButton(this);
    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    homeButton->setFixedSize(buttonSize);
    homeButton->setIconSize(buttonSize);
    homeButton->setGeometry(10, 10, 30, 30);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

    mainLayout = new QHBoxLayout(this);

    left = new QPushButton(this);
    QPixmap leftPix(":/buttons/pics/left-arrow-icon.gif");
    QIcon leftIcon(leftPix);
    left->setIcon(leftIcon);
    left->setFixedSize(buttonSize);
    left->setIconSize(buttonSize);
    connect(left, SIGNAL(released()), this, SLOT(leftPressed()));

    right = new QPushButton(this);
    QPixmap rightPix(":/buttons/pics/right-arrow-icon.png");
    QIcon rightIcon(rightPix);
    right->setIcon(rightIcon);
    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    connect(right, SIGNAL(released()), this, SLOT(rightPresed()));

    widgetSize = QSize(380, 277);
    placeHolder = new QWidget(this);
    placeHolder->setFixedSize(widgetSize);
    widgetGeo = QRect(50, 0, 380, 277);

    mainLayout->addWidget(left);
    mainLayout->addWidget(placeHolder);
    mainLayout->addWidget(right);

    currentIndex = 0;
    widgets<<widgetForAvg();
    widgets<<widgetForOne();
    widgets<<widgetForTwo();
    widgets<<widgetForThree();
    widgets.at(currentIndex)->show();

    widgets.at(0)->setStyleSheet(widgets.at(1)->styleSheet());

    goodStylesheet = "QLabel { font-size: 25px; color: green; }";
    badStylesheet = "QLabel { font-size: 25px; color: red; }";

    titleFont = QFont("Times serif", 20, 2);

    this->setStyleSheet(goodStylesheet);
}

void StatsWidget::leftPressed() {
    QWidget *currentWidget = widgets.at(currentIndex);
    if(currentIndex == 0) {
        currentIndex = widgets.size();
    }
    currentIndex--;
    currentWidget->hide();

    QWidget *newWidget = widgets.at(currentIndex);
    newWidget->show();
    //homeButton->setParent(newWidget);       //This allows the button to be hit
}

void StatsWidget::rightPresed() {
    QWidget *currentWidget = widgets.at(currentIndex);
    currentIndex++;
    if(currentIndex == widgets.length()) {
        currentIndex = 0;
    }
    currentWidget->hide();

    QWidget *newWidget = widgets.at(currentIndex);
    newWidget->show();
    //homeButton->setParent(newWidget);
}

void StatsWidget::homePressed() {
    this->hide();
}

QWidget* StatsWidget::widgetForAvg() {
    if(!avgWidget) {
        avgWidget = new QWidget(this);
        avgVLayout = new QVBoxLayout(avgWidget);
        avgNonRow = new QHBoxLayout(avgWidget);
        avgNonTitle = new QLabel("O3", avgWidget);;
        avgNonLabel = new QLabel("Non Label", avgWidget);
        avgHourRow = new QHBoxLayout(avgWidget);
        avgHourTitle = new QLabel("Hour Avg", avgWidget);
        avgHourLabel = new QLabel("Hour Label", avgWidget);
        avgEightRow = new QHBoxLayout(avgWidget);
        avgEightTitle = new QLabel("Eight Avg", avgWidget);
        avgEightLabel = new QLabel("Eight Label", avgWidget);

        avgNonRow->addWidget(avgNonTitle);
        avgNonRow->addWidget(avgNonLabel);
        avgVLayout->addLayout(avgNonRow);
        avgHourRow->addWidget(avgHourTitle);
        avgHourRow->addWidget(avgHourLabel);
        avgVLayout->addLayout(avgHourRow);
        avgEightRow->addWidget(avgEightTitle);
        avgEightRow->addWidget(avgEightLabel);
        avgVLayout->addLayout(avgEightRow);
        avgWidget->setLayout(avgVLayout);

        avgWidget->setFixedSize(widgetSize);
        avgWidget->setGeometry(widgetGeo);
        avgVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        avgNonTitle->setFont(titleFont);
        avgNonLabel->setFont(titleFont);
        avgHourTitle->setFont(titleFont);
        avgHourLabel->setFont(titleFont);
        avgEightTitle->setFont(titleFont);
        avgEightLabel->setFont(titleFont);
        avgWidget->hide();
    }
    return avgWidget;
}

QWidget* StatsWidget::widgetForOne() {
    if(!oneWidget) {
        oneWidget = new QWidget(this);
        oneVLayout = new QVBoxLayout(oneWidget);
        oneARow = new QHBoxLayout(oneWidget);
        oneATitle = new QLabel("One A ", oneWidget);
        oneALabel = new QLabel("One A Label", oneWidget);
        oneBRow = new QHBoxLayout(oneWidget);
        oneBTitle = new QLabel("One B", oneWidget);
        oneBLabel = new QLabel("One B Label", oneWidget);

        oneARow->addWidget(oneATitle);
        oneARow->addWidget(oneALabel);
        oneVLayout->addLayout(oneARow);
        oneBRow->addWidget(oneBTitle);
        oneBRow->addWidget(oneBLabel);
        oneVLayout->addLayout(oneBRow);
        oneWidget->setLayout(oneVLayout);

        oneWidget->setFixedSize(widgetSize);
        oneWidget->setGeometry(widgetGeo);
        oneVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        oneATitle->setFont(titleFont);
        oneALabel->setFont(titleFont);
        oneBTitle->setFont(titleFont);
        oneBLabel->setFont(titleFont);
        oneWidget->hide();
    }
    return oneWidget;
}

QWidget* StatsWidget::widgetForTwo() {
    if(!twoWidget) {
        twoWidget = new QWidget(this);
        twoVLayout = new QVBoxLayout(twoWidget);
        twoARow = new QHBoxLayout(twoWidget);
        twoATitle = new QLabel("Two A", twoWidget);
        twoALabel = new QLabel("Two A Label", twoWidget);
        twoBRow = new QHBoxLayout(twoWidget);
        twoBTitle = new QLabel("Two B", twoWidget);
        twoBLabel = new QLabel("Two B Label", twoWidget);

        twoARow->addWidget(twoATitle);
        twoARow->addWidget(twoALabel);
        twoVLayout->addLayout(twoARow);
        twoBRow->addWidget(twoBTitle);
        twoBRow->addWidget(twoBLabel);
        twoVLayout->addLayout(twoBRow);
        twoWidget->setLayout(twoVLayout);

        twoWidget->setFixedSize(widgetSize);
        twoWidget->setGeometry(widgetGeo);
        twoVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        twoATitle->setFont(titleFont);
        twoALabel->setFont(titleFont);
        twoBTitle->setFont(titleFont);
        twoBLabel->setFont(titleFont);
        twoWidget->hide();
    }
    return twoWidget;
}

QWidget* StatsWidget::widgetForThree() {
    if(!threeWidget) {
        threeWidget = new QWidget(this);
        threeVLayout = new QVBoxLayout(threeWidget);
        threeARow = new QHBoxLayout(threeWidget);
        threeATitle = new QLabel("Three A", threeWidget);
        threeALabel = new QLabel("Three A Label", threeWidget);
        threeBRow = new QHBoxLayout(threeWidget);
        threeBTitle = new QLabel("Three A", threeWidget);
        threeBLabel = new QLabel("Three B Label", threeWidget);

        threeARow->addWidget(threeATitle);
        threeARow->addWidget(threeALabel);
        threeVLayout->addLayout(threeARow);
        threeBRow->addWidget(threeBTitle);
        threeBRow->addWidget(threeBLabel);
        threeVLayout->addLayout(threeBRow);
        threeWidget->setLayout(threeVLayout);

        threeWidget->setFixedSize(widgetSize);
        threeWidget->setGeometry(widgetGeo);
        threeVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        threeATitle->setFont(titleFont);
        threeALabel->setFont(titleFont);
        threeWidget->hide();
    }
    return threeWidget;
}

void StatsWidget::setData(QList< QList<SerialDataItem> > *records, DeviceProfile *profile) {
    SerialDataItem temp;
    QList<SerialDataItem> curr = records->last();

    //Non Avg
    temp = records->last().at(profile->getMain_display_position());
    avgNonTitle->setText(profile->getMain_display_name()+": ");
    avgNonLabel->setText(QString::number(temp.getDvalue())+" "+profile->getMain_display_units());

    //One Hour
    QDateTime currentTimeStamp = records->last().at(profile->getDate_position()).getDateTime();
    bool found = false;
    int pos = records->length() - 1;
    while(!found && (pos > -1)) {
        QDateTime stamp = records->at(pos).at(profile->getDate_position()).getDateTime();
        double secs = stamp.secsTo(currentTimeStamp);
        if(secs >= (60 * 60)) {
            found = true;
        }
        pos--;
    }
    double hourAvg = 0;
    for(int i = records->length() - 1; i > pos; i--) {
        hourAvg += records->at(i).at(profile->getMain_display_position()).getDvalue();
    }
    hourAvg /= ((records->length() - 1) - pos);
    avgHourTitle->setText("Hour Avg "+profile->getMain_display_name()+": ");
    avgHourLabel->setText(QString::number(hourAvg)+" "+profile->getMain_display_units());

    //Eight Hours
    found = false;
    pos = records->length() - 1;
    while(!found && (pos > -1)) {
        QDateTime stamp = records->at(pos).at(profile->getDate_position()).getDateTime();
        double secs = stamp.secsTo(currentTimeStamp);
        if(secs >= (60 *60 * 8)) {
            found = true;
        }
        pos--;
    }
    double eightAvg = 0;
    for(int i = records->length() - 1; i > pos; i--) {
        eightAvg += records->at(i).at(profile->getMain_display_position()).getDvalue();
    }
    eightAvg /= ((records->length() - 1) - pos);
    avgEightTitle->setText("Eight Hour Avg "+profile->getMain_display_name()+": ");
    avgEightLabel->setText(QString::number(eightAvg)+" "+profile->getMain_display_units());

    QString strVal;
    double val;

    //Diagnostic A - A
    val = curr.at(profile->getDiagnosticA_position()).getDvalue();
    val -= 273;
    strVal = shortenString(QString::number(val));
    oneATitle->setText(profile->getDiagnosticA_name()+": ");
    oneALabel->setText(strVal+" "+profile->getDiagnosticA_units());

    //Diagnostic A - B
    val = curr.at(profile->getDiagnosticB_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    oneBTitle->setText(profile->getDiagnosticB_name()+": ");
    oneBLabel->setText(strVal+" "+profile->getDiagnosticB_units());

    //Diagnostic B - A
    val = curr.at(profile->getDiagnosticC_position()).getDvalue();
    val -= 273;
    if(val < 80) {
        twoALabel->setStyleSheet(badStylesheet);
    } else {
        twoALabel->setStyleSheet(goodStylesheet);
    }
    strVal = shortenString(QString::number(val));
    twoATitle->setText(profile->getDiagnosticC_name()+": ");
    twoALabel->setText(strVal+" C"+profile->getDiagnosticC_units());

    //Diagnostic B - B
    val = curr.at(profile->getDiagnosticD_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    twoBTitle->setText(profile->getDiagnosticD_name()+": ");
    twoBLabel->setText(strVal+" "+profile->getDiagnosticD_units());

    //Diagnostic C - A
    val = curr.at(profile->getDiagnosticE_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    threeATitle->setText(profile->getDiagnosticE_name()+": ");
    threeALabel->setText(strVal+" "+profile->getDiagnosticE_units());

    //Diagnostic C - B
    val = curr.at(profile->getDiagnosticF_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    threeBTitle->setText(profile->getDiagnosticF_name() + ": ");
    threeBLabel->setText(strVal + " " + profile->getDiagnosticF_units());
}

void StatsWidget::calculateMaxMinMedian(QList<QList<SerialDataItem> > &records, int element_to_sort) {
    QList< QList<SerialDataItem> > copied_records = records;

    int n;
    int i;
    for (n=0; n < copied_records.count(); n++)
    {
        for (i=n+1; i < copied_records.count(); i++)
        {
            QList<SerialDataItem> tempList = copied_records.at(n);
            double valorN=tempList.at(element_to_sort).getDvalue();
            QList<SerialDataItem> tempListb = copied_records.at(i);
            double valorI=tempListb.at(element_to_sort).getDvalue();
            if (valorN > valorI)
            {
                copied_records.move(i, n);
                n=0;
            }
        }
    }
}

QString StatsWidget::shortenString(QString string) {
    if(string.contains('.')) {
        while(string.at(string.length() - 2) != '.') {
            string = string.mid(0, string.length() - 1);
        }
    } else {
        string.append(".0");
    }
    return string;
}

StatsWidget::~StatsWidget()
{
    delete ui;
}
