#include "displaygraph.h"
#include "ui_displaygraph.h"
#define MAXIMUM_X_AXIS 10

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    centralWidget = new QWidget();
    verticalLayout = new QVBoxLayout();
    zoomHLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.jpg");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    QPushButton *clearButton = new QPushButton();
    QPixmap clearPixmap(":/buttons/pics/Clear-icon.jpg");
    QIcon clearButtonIcon(clearPixmap);
    clearButton->setIcon(clearButtonIcon);
    clearButton->setIconSize(QSize(35,31));
    clearButton->setFixedSize(35,31);

    QPushButton *settingsButton = new QPushButton();
    QPixmap settingsPixmap(":/buttons/pics/Settings-icon.jpg");
    QIcon settingsButtonIcon(settingsPixmap);
    settingsButton->setIcon(settingsButtonIcon);
    settingsButton->setIconSize(QSize(35,31));
    settingsButton->setFixedSize(35,31);

    zoom_in_button = new QPushButton("+");
    zoom_in_button->setFixedSize(30,30);
    zoomHLayout->addWidget(zoom_in_button);

    zoom_out_button = new QPushButton("-");
    zoom_out_button->setFixedSize(30,30);
    zoomHLayout->addWidget(zoom_out_button);

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


    this->setLayout(verticalLayout);
    //horizontalLayout->setSpacing(35);
    //centralWidget->setLayout(horizontalLayout);
    //setCentralWidget(centralWidget);
    zoom_in_button->setAutoRepeat(true);
    zoom_in_button->setAutoRepeatInterval(25);
    zoom_in_button->setAutoRepeatDelay(500);
    zoom_out_button->setAutoRepeat(true);
    zoom_out_button->setAutoRepeatInterval(25);
    zoom_out_button->setAutoRepeatDelay(500);

    connect(homeButton, SIGNAL(released()), this, SLOT(goback()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(zoom_in_button, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(zoom_out_button, SIGNAL(clicked()), this, SLOT(zoomOut()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    customPlot->xAxis->setRangeLower(0);
    customPlot->xAxis->setRangeUpper(10);
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("Time");
    //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));

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
    //drawPlot();

    customPlot->replot();

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

