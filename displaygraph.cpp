#include "displaygraph.h"
#include "ui_displaygraph.h"
#include <QSettings>
#include <QApplication>


#define MAXIMUM_X_AXIS 10

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{

    //m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/2btouch_settings.ini";
    loadSettings();
    settingsdialog = new GraphSettingsDialog();

    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons
    centralWidget = new QWidget();
    verticalLayout = new QVBoxLayout();
    zoomHLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    QPushButton *clearButton = new QPushButton();
    QPixmap clearPixmap(":/buttons/pics/clear-icon.gif");
    QIcon clearButtonIcon(clearPixmap);
    clearButton->setIcon(clearButtonIcon);
    clearButton->setIconSize(QSize(35,31));
    clearButton->setFixedSize(35,31);

    QPushButton *settingsButton = new QPushButton();
    QPixmap settingsPixmap(":/buttons/pics/settings-icon.gif");
    QIcon settingsButtonIcon(settingsPixmap);
    settingsButton->setIcon(settingsButtonIcon);
    settingsButton->setIconSize(QSize(35,31));
    settingsButton->setFixedSize(35,31);

    QPushButton *zoomInButton = new QPushButton();
    QPixmap zoomInPixmap(":/buttons/pics/zoom-in-icon.gif");
    QIcon zoomInButtonIcon(zoomInPixmap);
    zoomInButton->setIcon(zoomInButtonIcon);
    zoomInButton->setIconSize(QSize(35,31));
    zoomInButton->setFixedSize(35,31);

    QPushButton *zoomOutButton = new QPushButton();
    QPixmap zoomOutPixmap(":/buttons/pics/zoom-out-icon.gif");
    QIcon zoomOutButtonIcon(zoomOutPixmap);
    zoomOutButton->setIcon(zoomOutButtonIcon);
    zoomOutButton->setIconSize(QSize(35,31));
    zoomOutButton->setFixedSize(35,31);

    zoomHLayout->addWidget(zoomOutButton);
    zoomHLayout->addWidget(zoomInButton);

    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(settingsButton);
    buttonLayout->addLayout(zoomHLayout);
    buttonLayout->addWidget(clearButton);

    

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
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(settingsButton,SIGNAL(clicked(bool)), settingsdialog, SLOT(show()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    //customPlot->xAxis->setRangeLower(0);
    //customPlot->xAxis->setRangeUpper(10);

    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("Time");
    //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setTickLabelFont(QFont("Cabin", 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));


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
    customPlot->graph(0)->setData(x, y);

}
void DisplayGraph::redrawPlot(){
    QVector<double> u;
    u = y;
    loadSettings();
    if(autoscalex){
        customPlot->xAxis->setRange(0, x.size());
    }

    if(autoscaley){
        std::sort(u.begin(),u.end());
        customPlot->yAxis->setRange(u.first()-1, u.last()+1);
    }


    customPlot->replot();

}

void DisplayGraph::clear(){
    emit userClearedPlot();
}

void DisplayGraph::drawPlot(){
    QVector<double> u;

    loadSettings();
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

    if(autoscalex){
        customPlot->xAxis->setRange(0, x.size());
    }else{
        customPlot->xAxis->setRange(0, 10);
    }

    if(autoscaley){
        std::sort(u.begin(),u.end());
        customPlot->yAxis->setRange(u.first()-1, u.last()+1);
    }else{
        customPlot->yAxis->setRange(0, 10);
    }

    customPlot->replot();

}

void DisplayGraph::setYaxisLabel(QString label){
    customPlot->yAxis->setLabel(label);
}

void DisplayGraph::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void DisplayGraph::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void DisplayGraph::zoomIn(){
    QCPRange x_range = customPlot->xAxis->range();
    QCPRange y_range = customPlot->yAxis->range();
    autoscaley = false;
    autoscalex = false;
    saveSettings();
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->xAxis->setRange(x_range.lower + 1, x_range.upper - 1);
    }else if(customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->yAxis->setRange(x_range.lower + 1, x_range.upper - 1);
    }else{
        customPlot->xAxis->setRange(x_range.lower + 1, x_range.upper - 1);
        customPlot->yAxis->setRange(y_range.lower + 1, y_range.upper - 1);
    }
    customPlot->replot();
}

void DisplayGraph::zoomOut(){
    QCPRange x_range = customPlot->xAxis->range();
    QCPRange y_range = customPlot->yAxis->range();
    autoscaley = false;
    autoscalex = false;
    saveSettings();

    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }else if(customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
        customPlot->yAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }else{
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
        customPlot->yAxis->setRange(y_range.lower - 1, y_range.upper + 1);
    }
    customPlot->replot();
}

void DisplayGraph::loadSettings()
{
 QSettings settings("2btech", "touchscreen");

 autoscalex = settings.value("xautoscale").toBool();
 autoscaley = settings.value("yautoscale").toBool();
 //qDebug()<<"Read X scale:"<<QString::number(autoscalex);
 //qDebug()<<"Read Y scale:"<<QString::number(autoscaley);
}

void DisplayGraph::saveSettings()
{
 QSettings settings("2btech", "touchscreen");
 //qDebug()<<"Before writing,";

 settings.setValue("xautoscale", autoscalex);
 settings.setValue("yautoscale", autoscaley);

}
