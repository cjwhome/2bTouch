#include "statswidget2.h"
#include "ui_statswidget2.h"

StatsWidget2::StatsWidget2(QWidget *parent, QList<GasDataState *> * d) :
    QWidget(parent),
    ui(new Ui::StatsWidget2)
{
    ui->setupUi(this);

    data = d;

    buttonSize = QSize(40,40);

    //QGridLayout * tLayout = new QGridLayout(this);



//    homeButton = new QPushButton(this);
//    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
//    homeButton->setFixedSize(buttonSize);
//    homeButton->setIconSize(buttonSize);
//    //homeButton->setGeometry(10, 10, 30, 30);
//    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));
//    tLayout->addWidget(homeButton,0, 0);
//    QLabel * l = new QLabel(this);
//    l->setText("I hope this works");
//    QLabel * l2 = new QLabel(this);
//    l2->setText("I hope this works");
//    tLayout->addWidget(l,0, 1);
//    tLayout->addWidget(l2,1, 0);



//    QLabel * l = new QLabel(this);
//    l->setText("I hope this works");

    mainLayout = new QHBoxLayout(this);

//    QPushButton * p = new QPushButton(this);
//    p->setText("Test");
//    p->setStyleSheet("background-color: red");
//    mainLayout->addWidget(p);

    homeButton = new QPushButton(this);
    homeButton->setIcon(QIcon(":/buttons/pics/home-icon.gif"));
    homeButton->setFixedSize(buttonSize);
    homeButton->setIconSize(buttonSize);
    homeButton->setGeometry(10, 10, 30, 30);
    connect(homeButton, SIGNAL(released()), this, SLOT(homePressed()));

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
    connect(right, SIGNAL(released()), this, SLOT(rightPressed()));

    widgetSize = QSize(380, 277);
    placeHolder = new QWidget(this);
    placeHolder->setFixedSize(widgetSize);
    widgetGeo = QRect(50, 0, 380, 277);

    gasLayout = new QGridLayout(placeHolder);
    gasLayout->setAlignment(Qt::AlignCenter);

    gasName = new QLabel();
    gasName->setText("Gas Name");
    gasName->setAlignment(Qt::AlignCenter);

    hourAverage = new QLabel();
    hourAverage->setText("Hour Avg: ");
    hourAverage->setAlignment(Qt::AlignCenter);

    hourValue = new QLabel();
    hourValue->setText("0.0 ppb");
    hourValue->setAlignment(Qt::AlignCenter);

    eightAverage = new QLabel();
    eightAverage->setText("Eight Avg: ");
    eightAverage->setAlignment(Qt::AlignCenter);

    eightValue = new QLabel();
    eightValue->setText("0.0 ppb");
    eightAverage->setAlignment(Qt::AlignCenter);

    gasLayout->addWidget(gasName, 0, 0);
    gasLayout->addWidget(hourAverage, 1, 0);
    gasLayout->addWidget(hourValue, 1, 1);
    gasLayout->addWidget(eightAverage, 2, 0);
    gasLayout->addWidget(eightValue, 2, 1);

    mainLayout->addWidget(left);
    mainLayout->addWidget(placeHolder);
    mainLayout->addWidget(right);

    goodStylesheet = "QLabel { font-size: 35px;}";
    //badStylesheet = "QLabel { font-size: 25px; color: red; }";

    this->setStyleSheet(goodStylesheet);

    numberOfGases = data->size();

    updateDisplay();
}

void StatsWidget2::iHateCpp()
{
    updateDisplay();
}

void StatsWidget2::leftPressed()
{
    if(numberOfGases == 0)
    {
        qDebug() << "No gases to display in statsWidgetDialog: leftPressed()";
    }

    if(currentGasIndex == 0)
    {
        currentGasIndex = numberOfGases - 1;
    }
    else
    {
        currentGasIndex -= 1;
    }

    if(data->at(currentGasIndex)->unit == "")
    {
        leftPressed();
    }
    else
    {
        updateDisplay();
    }
}

void StatsWidget2::rightPressed()
{
    if(numberOfGases == 0)
    {
        qDebug() << "No gases to display in statsWidgetDialog: rightPressed()";
    }

    if(currentGasIndex == numberOfGases - 1)
    {
        currentGasIndex = 0;
    }
    else
    {
        currentGasIndex += 1;
    }

    if(data->at(currentGasIndex)->unit == "")
    {
        rightPressed();
    }
    else
    {
        updateDisplay();
    }
}

void StatsWidget2::updateDisplay()
{
    if(numberOfGases == 0)
    {
        return;
    }
    if(data->at(0)->data.size() == 0)
    {
        return;
    }
    int numDH = 2;
    int numDE = 2;
    float avgHour = data->at(currentGasIndex)->getHourAverage();
    float avgEight = data->at(currentGasIndex)->getEightAverage();
    if(std::abs(avgHour) >= 10)
    {
        numDH = 3;
    }
    if(std::abs(avgEight) >= 10)
    {
        numDE = 3;
    }

    //<font color='green'>" + QString::number(gases->at(0)->data.at(gases->at(0)->data.size() - 1)) + "</font>
    gasName->setText(*(data->at(currentGasIndex)->name));
    hourValue->setText("<font color='green'>" + QString::number(avgHour, 'G', numDH) + "</font> " + data->at(currentGasIndex)->unit);
    eightValue->setText("<font color='green'>" + QString::number(avgEight, 'G', numDE) + "</font> " + data->at(currentGasIndex)->unit);
}

void StatsWidget2::homePressed()
{
    this->close();
}

StatsWidget2::~StatsWidget2()
{
    delete ui;
}
