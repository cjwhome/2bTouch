#include "displaygraph.h"
#include "ui_displaygraph.h"
#define MAXIMUM_X_AXIS 10

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
    ui->setupUi(this);
    centralWidget = new QWidget();
    horizontalLayout = new QHBoxLayout();
    zoomHLayout = new QHBoxLayout();
    buttonLayout = new QVBoxLayout();

    home_button = new QPushButton("Home");
    home_button->setFixedSize(70,62);

    clear_button = new QPushButton("Clear");
    clear_button->setFixedSize(70,62);

    settings_button = new QPushButton("Settings");
    settings_button->setFixedSize(70,62);
    zoom_in_button = new QPushButton("+");
    zoom_in_button->setFixedSize(30,30);
    zoomHLayout->addWidget(zoom_in_button);

    zoom_out_button = new QPushButton("-");
    zoom_out_button->setFixedSize(30,30);
    zoomHLayout->addWidget(zoom_out_button);

    buttonLayout->addLayout(zoomHLayout);
    buttonLayout->addWidget(home_button);
    buttonLayout->addWidget(clear_button);

    buttonLayout->addWidget(settings_button);

    //add the separator line:
    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::VLine);

    customPlot = new QCustomPlot();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    // create graph and assign data to it:
    customPlot->addGraph();
    horizontalLayout->addLayout(buttonLayout);
    horizontalLayout->addWidget(myFrame);
    horizontalLayout->addWidget(customPlot);
    this->setLayout(horizontalLayout);
    //horizontalLayout->setSpacing(35);
    //centralWidget->setLayout(horizontalLayout);
    //setCentralWidget(centralWidget);
    zoom_in_button->setAutoRepeat(true);
    zoom_in_button->setAutoRepeatInterval(25);
    zoom_in_button->setAutoRepeatDelay(500);
    zoom_out_button->setAutoRepeat(true);
    zoom_out_button->setAutoRepeatInterval(25);
    zoom_out_button->setAutoRepeatDelay(500);

    connect(home_button, SIGNAL(released()), this, SLOT(goback()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
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

