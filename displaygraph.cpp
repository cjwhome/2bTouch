#include "displaygraph.h"
#include "ui_displaygraph.h"
#include <QDateTime>
#define MAXIMUM_X_AXIS 10

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
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
    QPixmap clearPixmap(":/buttons/pics/clear-icon.gif");
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

    settingsdialog = new GraphSettingsDialog(this);


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

    customPlot = new QCustomPlot();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    // create graph and assign data to it:
    customPlot->addGraph();
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
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(zoomInButton, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(pressed()), this, SLOT(zoomOut()));
    connect(settingsButton, SIGNAL(clicked(bool)), settingsdialog, SLOT(show()));
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

    customPlot->graph(0)->setData(x, y);
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

void DisplayGraph::setData(QVector<double> a, QVector<double> b){
    x = a;      //x is time
    y = b;      //y is measurement
    customPlot->graph(0)->setData(a, b);

}
void DisplayGraph::redrawPlot(){
    QVector<double> u;
    u = y;
    loadSettings();

    if(autoscalex) {
        customPlot->xAxis->setRange(x.first(), x.last());
    }

    if(autoscaley) {
        double min, max;
        for(int i = 0; i < u.length(); i++) {
            double val = u.at(i);
            if(val < min) {
                min = val;
            } else if(val > max) {
                max = val;
            }
        }
        customPlot->yAxis->setRange(min - 1, max + 1);
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

void DisplayGraph::drawPlot(){
    QVector<double> u;


    customPlot->graph(0)->setData(x, y);
    u = y;  //copy it so we can align them from lowest to highest to get the range
    // give the axes some labels:
    //customPlot->xAxis->setLabel("Time");
    //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    //customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    //customPlot->yAxis->setLabel("Ozone (ppb)");
    // set axes ranges, so we see all data:
    //customPlot->xAxis->setRange(0, 100);
    std::sort(u.begin(),u.end());
    //int highest_value;
    //qDebug()<<"Max value is:"<<u.last();
    //customPlot->yAxis->setRange(getYRange().lower, getYRange().upper);
    customPlot->replot();

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
