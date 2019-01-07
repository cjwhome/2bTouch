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
    //Removes the top window bar
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    //The graphettingsForm and selectGasForm are only used with this form
    settingsdialog = new GraphSettingsForm();
    gas = new SelectGasForm(nullptr, data);

    //this->setStyleSheet("background-color:white;");             //Sets the background to white
    //this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons

    settings = new QSettings("2B Technologies", "2B Touch");

    //add the separator line:
    QFrame* myFrame = new QFrame(ui->placeHolder);
    myFrame->setFrameShape(QFrame::HLine);

    //pens are used by the qtcustomplot class to color the plot
    //These are used as a key to represent each gas type
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
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes); // This is involved
    // create graph and assign data and pen to it
    for(int i = 0; i < gasses->size(); i++){
        customPlot->addGraph();
        customPlot->graph(i)->setPen(*pens->at(i));
        customPlot->graph(i)->setVisible(false);
    }
    customPlot->setParent(ui->placeHolder);
    customPlot->setGeometry(ui->placeHolder->geometry());

    connect(ui->homeButton, SIGNAL(released()), this, SLOT(goback()));
    connect(ui->selectGas_2, SIGNAL(clicked()), gas, SLOT(show()));//search
    connect(ui->selectGas_2, SIGNAL(clicked()), gas, SLOT(update()));//can combine into 1 function
    connect(ui->zIn, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(ui->zOut, SIGNAL(pressed()), this, SLOT(zoomOut()));
    connect(ui->settings, SIGNAL(clicked(bool)), settingsdialog, SLOT(show()));
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

    QString style("QPushButton { border: none;}");

    //These set the pictures oif the buttons
    QPixmap homePixmap(":/pics/home-icon.gif");
    ui->homeButton->setIcon(homePixmap);
    ui->homeButton->setIconSize(QSize(35,31));
    ui->homeButton->setStyleSheet(style);
    QPixmap zoomIn(":/pics/zoom-in-icon.gif");
    ui->zIn->setIcon(zoomIn);
    ui->zIn->setIconSize(QSize(35,31));
    ui->zIn->setStyleSheet(style);
    QPixmap zoomOut(":/pics/zoom-out-icon.gif");
    ui->zOut->setIcon(zoomOut);
    ui->zOut->setIconSize(QSize(35,31));
    ui->zOut->setStyleSheet(style);
    QPixmap selectGas(":/pics/select-gas-icon.png");
    ui->selectGas_2->setIcon(selectGas);
    ui->selectGas_2->setIconSize(QSize(35,31));
    ui->selectGas_2->setStyleSheet(style);
    QPixmap setting(":/pics/settings-icon.gif");
    ui->settings->setIcon(setting);
    ui->settings->setIconSize(QSize(35,31));
    ui->settings->setStyleSheet(style);
}

void DisplayGraph::goback(){
    close();
}

DisplayGraph::~DisplayGraph(){
    delete ui;
}

//This redraws the graph
void DisplayGraph::redrawPlot(){
    //This checks to make sure that the graph has plots for each gas
    //There was an issue where the gases list was not populated when creating the graphs
    if(gasses->size() != customPlot->graphCount()){
        customPlot->clearGraphs();
        for(int i = 0; i < gasses->size(); i++){
            customPlot->addGraph();
            customPlot->graph(i)->setPen(*pens->at(i));
            customPlot->graph(i)->setVisible(false);
        }
    }
    //Sets the selected plots to visible
    //The plots are set as selected in the selectGasForm
    for(int i = 0; i < gasses->size(); i++){
        if(gasses->at(i)->selected){
            customPlot->graph(i)->setVisible(true);
            customPlot->graph(i)->setData(gasses->at(i)->x,gasses->at(i)->data);
        }else{
            customPlot->graph(i)->setVisible(false);
        }
    }
    loadSettings();

    //min and max are y, min2 and max2 are x
    double min = gasses->at(0)->minT;
    double max = gasses->at(0)->maxT;
    double min2 = 0;
    double max2 = 0;
    bool setMin = false;
    bool setMax = false;

    //This scales the graph based on the selected gases
    //If the gas is selected it compared the min and max y values to current one and updates the value if applicable
    for(int i = 0; i < gasses->size(); i++){
        if(gasses->at(i)->selected){
            if(min > gasses->at(i)->minT){
                min = gasses->at(i)->minT;
            }
            if(max < gasses->at(i)->maxT){
                max = gasses->at(i)->maxT;
            }
            if(min2 > gasses->at(i)->min || setMin == false){
                setMin = true;
                min2 = gasses->at(i)->min;
            }
            if(max2 < gasses->at(i)->max || setMax == false){
                setMax = true;
                max2 = gasses->at(i)->max;
            }
        }
    }

    if(setMin == false){
        min2 = 0;
    }
    if(setMax == false){
        max2 = 0;
    }

    if(autoscalex){
        //qDebug() << "Min: " << min;
        //qDebug() << "Max: " << max;
        customPlot->xAxis->setRange(min, max);
    }

    if(autoscaley)
        customPlot->yAxis->setRange(min2 - 1, max2 + 1);

    fixScale();
    //This applies the selected changes to the graph
    customPlot->replot();

}

//This checks to see if the graph was autoscaling when last loaded
void DisplayGraph::loadSettings() {
    autoscalex = settings->value("xautoscale", true).toBool();
    autoscaley = settings->value("yautoscale", true).toBool();
}

//Clears the graph
void DisplayGraph::clear(){
    emit userClearedPlot();
}

//Sets the y axis label
void DisplayGraph::setYaxisLabel(QString label){
    customPlot->yAxis->setLabel(label);
}

//The customPlot class handles the majority of the click functions, but this stops the autoscale so that the grpah doesnt jump back
void DisplayGraph::mousePress()
{
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

void DisplayGraph::mouseWheel(){
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

//Handles when the user zooms in, stops it from autoscaling so that the user dosnt lose their place
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

//Handles when the user zooms out, stops it from autoscaling so that the user dosnt lose their place
void DisplayGraph::zoomOut(){
    settings->setValue("xautoscale", false);
    settings->setValue("yautoscale", false);

    QCPRange x_range = customPlot->xAxis->range();
    QCPRange y_range = customPlot->yAxis->range();

    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    {
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }
    else if(customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    {
        customPlot->yAxis->setRange(x_range.lower - 1, x_range.upper + 1);
    }
    else
    {
        customPlot->xAxis->setRange(x_range.lower - 1, x_range.upper + 1);
        customPlot->yAxis->setRange(y_range.lower - 1, y_range.upper + 1);
    }
    fixScale();
    customPlot->replot();
}

//This sets the scale of the axis based on the range of values on the graph
void DisplayGraph::fixScale() {
    QCPRange plotRange = customPlot->xAxis->range();
    double range = plotRange.upper - plotRange.lower;
    if(range < 120){
        customPlot->xAxis->setDateTimeFormat("mm:ss");
        customPlot->xAxis->setTickStep(10);
    }
    else if((range > 120) && (range < 60*60)){
        customPlot->xAxis->setDateTimeFormat("hh:mm");
        customPlot->xAxis->setTickStep(60);
    }
    else if((range > 60*60) && (range < 24*60*60)){
        customPlot->xAxis->setDateTimeFormat("ddd hh");
        customPlot->xAxis->setTickStep(60*60);
    }
    else if(range > 24*60*60){
        customPlot->xAxis->setDateTimeFormat("mm-dd-yy");
        customPlot->xAxis->setTickStep(24*60*60);
    }
}
