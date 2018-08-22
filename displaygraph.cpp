#include "displaygraph.h"
#include "ui_displaygraph.h"
#include <QDateTime>
#define MAXIMUM_X_AXIS 10

DisplayGraph::DisplayGraph(QWidget *parent, QList<GasDataState *> * data) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
    gasses = data;

    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons
    centralWidget = new QWidget();
    verticalLayout = new QVBoxLayout();
    zoomHLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    settings = new QSettings("2B Technologies", "2B Touch");

    QSize buttonSize(50, 50);

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(buttonSize);

    QPushButton *clearButton = new QPushButton();
    QPixmap clearPixmap(":/buttons/pics/select-gas-icon.gif");
    QIcon clearButtonIcon(clearPixmap);
    clearButton->setIcon(clearButtonIcon);
    clearButton->setIconSize(QSize(35,31));
    clearButton->setFixedSize(buttonSize);

    QPushButton *settingsButton = new QPushButton();
    QPixmap settingsPixmap(":/buttons/pics/settings-icon.gif");
    QIcon settingsButtonIcon(settingsPixmap);
    settingsButton->setIcon(settingsButtonIcon);
    settingsButton->setIconSize(QSize(35,31));
    settingsButton->setFixedSize(buttonSize);

    settingsdialog = new GraphSettingsDialogB(this);
    gas = new SelectGasDialog(this,data);


    QPushButton *zoomInButton = new QPushButton();
    QPixmap zoomInPixmap(":/buttons/pics/zoom-in-icon.gif");
    QIcon zoomInButtonIcon(zoomInPixmap);
    zoomInButton->setIcon(zoomInButtonIcon);
    zoomInButton->setIconSize(QSize(35,31));
    zoomInButton->setFixedSize(buttonSize);

    QPushButton *zoomOutButton = new QPushButton();
    QPixmap zoomOutPixmap(":/buttons/pics/zoom-out-icon.gif");
    QIcon zoomOutButtonIcon(zoomOutPixmap);
    zoomOutButton->setIcon(zoomOutButtonIcon);
    zoomOutButton->setIconSize(QSize(35,31));
    zoomOutButton->setFixedSize(buttonSize);

    zoomHLayout->addWidget(zoomOutButton);
    zoomHLayout->addWidget(zoomInButton);

    buttonLayout->addWidget(homeButton);
    buttonLayout->addLayout(zoomHLayout);
    buttonLayout->addWidget(clearButton);

    buttonLayout->addWidget(settingsButton);

    //add the separator line:
    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::HLine);

    pens = new QList<QPen*>();
    pens->append(new QPen(Qt::blue));
    pens->append(new QPen(Qt::black));
    pens->append(new QPen(Qt::cyan));
    pens->append(new QPen(Qt::red));
    pens->append(new QPen(Qt::magenta));
    pens->append(new QPen(Qt::green));
    pens->append(new QPen(Qt::yellow));
    pens->append(new QPen(Qt::gray));
    pens->append(new QPen(Qt::darkRed));
    pens->append(new QPen(Qt::darkMagenta));
    pens->append(new QPen(Qt::darkGreen));
    pens->append(new QPen(Qt::darkYellow));
    pens->append(new QPen(Qt::darkBlue));
    pens->append(new QPen(Qt::darkGray));

    customPlot = new QCustomPlot();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    // create graph and assign data to it:
    for(int i = 0; i < gasses->size(); i++)
    {
        customPlot->addGraph();
        customPlot->graph(i)->setPen(*pens->at(i));
        customPlot->graph(i)->setVisible(false);
    }
    verticalLayout->addWidget(customPlot);
    verticalLayout->addWidget(myFrame);
    verticalLayout->addLayout(buttonLayout);
    //menuWidget->setLayout(buttonLayout);
    //verticalLayout->addWidget(menuWidget);

    //menuIsShowing = true;

    //showMenuWidget = new ShowMenuWidget(this);
    //connect(showMenuWidget, SIGNAL(pressed()), this, SLOT(showMenu()));

    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(timerFired()));
    //timer->start(2000);

    this->setLayout(verticalLayout);
    //horizontalLayout->setSpacing(35);
    //centralWidget->setLayout(horizontalLayout);
    //setCentralWidget(centralWidget);
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(25);
    zoomInButton->setAutoRepeatDelay(500);
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(25);
    zoomOutButton->setAutoRepeatDelay(500);

    connect(homeButton, SIGNAL(released()), this, SLOT(goback()));
    //connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(clearButton, SIGNAL(clicked()), gas, SLOT(show()));
    connect(zoomInButton, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(pressed()), this, SLOT(zoomOut()));
    connect(settingsButton, SIGNAL(clicked(bool)), settingsdialog, SLOT(show()));
    connect(clearButton, SIGNAL(clicked()), gas, SLOT(update()));
    connect(settingsdialog, SIGNAL(applyGraphSettings()), this, SLOT(redrawPlot()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("MM/dd/yy hh:mm:ss");
    double now = QDateTime::currentDateTime().toTime_t();
    customPlot->xAxis->setRange(now, now+60);
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(10);
    customPlot->xAxis->setSubTickCount(3);

    //customPlot->xAxis->setLabel("Time");
    //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setTickLabelFont(QFont("Cabin", 8));
    customPlot->yAxis->setTickLabelFont(QFont("Cabin", 8));

    customPlot->xAxis->setTickLabelRotation(-30);
    fixScale();
}

void DisplayGraph::goback(){

    close();
}

DisplayGraph::~DisplayGraph()
{
    delete ui;
}

void DisplayGraph::redrawPlot(){
    if(gasses->size() != customPlot->graphCount())
    {
        customPlot->clearGraphs();
        for(int i = 0; i < gasses->size(); i++)
        {
            customPlot->addGraph();
            customPlot->graph(i)->setPen(*pens->at(i));
            customPlot->graph(i)->setVisible(false);
        }
    }

    for(int i = 0; i < gasses->size(); i++)
    {
        if(gasses->at(i)->selected)
        {
            customPlot->graph(i)->setVisible(true);
            customPlot->graph(i)->setData(gasses->at(i)->x,gasses->at(i)->data);
        }
        else
        {
            customPlot->graph(i)->setVisible(false);
        }
    }

    loadSettings();

    double min = gasses->at(0)->minT;
    double max = gasses->at(0)->maxT;
    double min2 = 0;
    double max2 = 0;
    bool setMin = false;
    bool setMax = false;

    for(int i = 0; i < gasses->size(); i++)
    {
        if(gasses->at(i)->selected)
        {
            if(min > gasses->at(i)->minT)
            {
                min = gasses->at(i)->minT;
            }
            if(max < gasses->at(i)->maxT)
            {
                max = gasses->at(i)->maxT;
            }
            if(min2 > gasses->at(i)->min || setMin == false)
            {
                setMin = true;
                min2 = gasses->at(i)->min;
            }
            if(max2 < gasses->at(i)->max || setMax == false)
            {
                setMax = true;
                max2 = gasses->at(i)->max;
            }
        }
    }

    if(setMin == false)
    {
        min2 = 0;
    }
    if(setMax == false)
    {
        max2 = 0;
    }

    if(autoscalex) {
        customPlot->xAxis->setRange(min, max);
    }

    if(autoscaley) {
        customPlot->yAxis->setRange(min2 - 1, max2 + 1);
    }

    fixScale();

    customPlot->replot();

}

void DisplayGraph::loadSettings() {
    autoscalex = settings->value("xautoscale", true).toBool();
    autoscaley = settings->value("yautoscale", true).toBool();
}

void DisplayGraph::clear(){
    emit userClearedPlot();
}

void DisplayGraph::setYaxisLabel(QString label){
    customPlot->yAxis->setLabel(label);
}

void DisplayGraph::mousePress()
{
    qDebug()<<"Mouse Press Event: "<<QDateTime::currentDateTime().toTime_t();
    settings->setValue("xautoscale", false);
    settings->setValue("yautoscale", false);
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  /*if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);*/
}

void DisplayGraph::mouseWheel()
{
    qDebug()<<"Mouse Wheel Event: "<<QDateTime::currentDateTime().toTime_t();
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

  fixScale();
}

void DisplayGraph::zoomIn(){
    settings->setValue("xautoscale", false);
    settings->setValue("yautoscale", false);

    QCPRange x_range = customPlot->xAxis->range();
    QCPRange y_range = customPlot->yAxis->range();

    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->xAxis->setRange(x_range.lower + 1, x_range.upper - 1);
    }else if(customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->yAxis->setRange(x_range.lower + 1, x_range.upper - 1);
    }else{
        customPlot->xAxis->setRange(x_range.lower + 1, x_range.upper - 1);
        customPlot->yAxis->setRange(y_range.lower + 1, y_range.upper - 1);
    }
    fixScale();
    customPlot->replot();
}

void DisplayGraph::zoomOut(){
    settings->setValue("xautoscale", false);
    settings->setValue("yautoscale", false);

    QCPRange x_range = customPlot->xAxis->range();
    QCPRange y_range = customPlot->yAxis->range();

    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }else if(customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->yAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }else{
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
        customPlot->yAxis->setRange(y_range.lower - 1, y_range.upper + 1);
    }
    fixScale();
    customPlot->replot();
}

void DisplayGraph::fixScale() {
    QCPRange plotRange = customPlot->xAxis->range();
    double range = plotRange.upper - plotRange.lower;
    if(range < 120) {
        customPlot->xAxis->setDateTimeFormat("mm:ss");
        customPlot->xAxis->setTickStep(10);
    } else if((range > 120) && (range < 60*60)) {
        customPlot->xAxis->setDateTimeFormat("hh:mm");
        customPlot->xAxis->setTickStep(60);
    } else if((range > 60*60) && (range < 24*60*60)) {
        customPlot->xAxis->setDateTimeFormat("ddd hh");
        customPlot->xAxis->setTickStep(60*60);
    } else if(range > 24*60*60) {
        customPlot->xAxis->setDateTimeFormat("mm-dd-yy");
        customPlot->xAxis->setTickStep(24*60*60);
    }
}
