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

    goodStylesheet = "QLabel { font-size: 16px; color: green; }";
    badStylesheet = "QLabel { font-size: 16px; color: red; }";

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
        avgNonLabel = new QLabel("Non Label", avgWidget);
        avgHourLabel = new QLabel("Hour Label", avgWidget);
        avgEightLabel = new QLabel("Eight Label", avgWidget);

        avgVLayout->addWidget(avgNonLabel);
        avgVLayout->addWidget(avgHourLabel);
        avgVLayout->addWidget(avgEightLabel);
        avgWidget->setLayout(avgVLayout);

        avgWidget->setFixedSize(widgetSize);
        avgWidget->setGeometry(widgetGeo);
        avgVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        avgWidget->hide();
    }
    return avgWidget;
}

QWidget* StatsWidget::widgetForOne() {
    if(!oneWidget) {
        oneWidget = new QWidget(this);
        oneVLayout = new QVBoxLayout(oneWidget);
        oneALabel = new QLabel("One A Label", oneWidget);
        oneBLabel = new QLabel("One B Label", oneWidget);

        oneVLayout->addWidget(oneALabel);
        oneVLayout->addWidget(oneBLabel);
        oneWidget->setLayout(oneVLayout);

        oneWidget->setFixedSize(widgetSize);
        oneWidget->setGeometry(widgetGeo);
        oneVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        oneWidget->hide();
    }
    return oneWidget;
}

QWidget* StatsWidget::widgetForTwo() {
    if(!twoWidget) {
        twoWidget = new QWidget(this);
        twoVLayout = new QVBoxLayout(twoWidget);
        twoALabel = new QLabel("Two A Label", twoWidget);
        twoBLabel = new QLabel("Two B Label", twoWidget);

        twoVLayout->addWidget(twoALabel);
        twoVLayout->addWidget(twoBLabel);
        twoWidget->setLayout(twoVLayout);

        twoWidget->setFixedSize(widgetSize);
        twoWidget->setGeometry(widgetGeo);
        twoVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        twoWidget->hide();
    }
    return twoWidget;
}

QWidget* StatsWidget::widgetForThree() {
    if(!threeWidget) {
        threeWidget = new QWidget(this);
        threeVLayout = new QVBoxLayout(threeWidget);
        threeALabel = new QLabel("Three A Label", threeWidget);

        threeVLayout->addWidget(threeALabel);
        threeWidget->setLayout(threeVLayout);

        threeWidget->setFixedSize(widgetSize);
        threeWidget->setGeometry(widgetGeo);
        threeVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        threeWidget->hide();
    }
    return threeWidget;
}

void StatsWidget::setData(QList< QList<SerialDataItem> > *records, DeviceProfile *profile) {
    SerialDataItem temp;
    QList<SerialDataItem> curr = records->last();

    //Non Avg
    temp = records->last().at(profile->getMain_display_position());
    avgNonLabel->setText(profile->getMain_display_name()+": "+QString::number(temp.getDvalue())+" "+profile->getMain_display_units());

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
    avgHourLabel->setText("Hour Avg "+profile->getMain_display_name()+": "+QString::number(hourAvg)+" "+profile->getMain_display_units());

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
    avgEightLabel->setText("Eight Hour Avg "+profile->getMain_display_name()+": "+QString::number(eightAvg)+" "+profile->getMain_display_units());

    QString strVal;
    double val;

    val = curr.at(profile->getDiagnosticA_position()).getDvalue();
    val -= 273;
    strVal = shortenString(QString::number(val));
    oneALabel->setText(profile->getDiagnosticA_name()+": "+strVal+" "+profile->getDiagnosticA_units());
    val = curr.at(profile->getDiagnosticB_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    oneBLabel->setText(profile->getDiagnosticB_name()+": "+strVal+" "+profile->getDiagnosticB_units());
    val = curr.at(profile->getDiagnosticC_position()).getDvalue();
    val -= 273;
    if(val < 80) {
        twoALabel->setStyleSheet(badStylesheet);
    } else {
        twoALabel->setStyleSheet(goodStylesheet);
    }
    strVal = shortenString(QString::number(val));
    twoALabel->setText(profile->getDiagnosticC_name()+": "+strVal+" C"+profile->getDiagnosticC_units());
    val = curr.at(profile->getDiagnosticD_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    twoBLabel->setText(profile->getDiagnosticD_name()+": "+strVal+" "+profile->getDiagnosticD_units());
    val = curr.at(profile->getDiagnosticE_position()).getDvalue();
    strVal = shortenString(QString::number(val));
    threeALabel->setText(profile->getDiagnosticE_name()+": "+strVal+" "+profile->getDiagnosticE_units());
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
