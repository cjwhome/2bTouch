#include "statsidgetdialog.h"
#include "ui_statsidgetdialog.h"

StatsidgetDialog::StatsidgetDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsidgetDialog)
{
    ui->setupUi(this);

    mainLayout = new QHBoxLayout(this);

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
    QPixmap rightPix(":/buttons/pics/right-arrow-icon.gif");
    QIcon rightIcon(leftPix);
    right->setMinimumSize(1,1);
    right->setIcon(rightIcon);
    right->setFixedSize(buttonSize);
    right->setIconSize(buttonSize);
    connect(left, SIGNAL(released()), this, SLOT(leftPressed()));

    widgetSize = QSize(380, 277);
    placeHolder = new QWidget(this);
    placeHolder->setFixedSize(widgetSize);
    widgetGeo = QRect(50, 0, 380, 277);

    gasLayout = new QGridLayout();

    mainLayout->addWidget(left);
    mainLayout->addWidget(placeHolder);
    mainLayout->addWidget(right);

    goodStylesheet = "QLabel { font-size: 25px; color: green; }";
    badStylesheet = "QLabel { font-size: 25px; color: red; }";

    this->setStyleSheet(goodStylesheet);

    //For testing purposes
}

void StatsidgetDialog::leftPressed()
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
    updateDisplay();
}

void StatsidgetDialog::rightPressed()
{
    if(numberOfGases == 0)
    {
        qDebug() << "No gases to display in statsWidgetDialog: leftPressed()";
    }

    if(currentGasIndex == numberOfGases - 1)
    {
        currentGasIndex = 0;
    }
    else
    {
        currentGasIndex += 1;
    }
    updateDisplay();
}

void StatsidgetDialog::updateDisplay()
{
    //Needs to be populated
}

void StatsidgetDialog::homePressed()
{
    this->close();
}

StatsidgetDialog::~StatsidgetDialog()
{
    delete ui;
}
