#include "displaygraph.h"
#include "ui_displaygraph.h"

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
    ui->setupUi(this);
    centralWidget = new QWidget();
    horizontalLayout = new QHBoxLayout();
    buttonLayout = new QVBoxLayout();

    home_button = new QPushButton("Home");
    home_button->setFixedSize(70,62);

    clear_button = new QPushButton("Clear");
    clear_button->setFixedSize(70,62);

    settings_button = new QPushButton("Settings");
    settings_button->setFixedSize(70,62);

    buttonLayout->addWidget(home_button);
    buttonLayout->addWidget(clear_button);
    buttonLayout->addWidget(settings_button);

    //add the separator line:
    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::VLine);

    customPlot = new QCustomPlot();
    // create graph and assign data to it:
    customPlot->addGraph();
    horizontalLayout->addLayout(buttonLayout);
    horizontalLayout->addWidget(myFrame);
    horizontalLayout->addWidget(customPlot);
    this->setLayout(horizontalLayout);
    //horizontalLayout->setSpacing(35);
    //centralWidget->setLayout(horizontalLayout);
    //setCentralWidget(centralWidget);

    connect(home_button, SIGNAL(released()), this, SLOT(goback()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));


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

    //qDebug()<<"Size of x:"<<x.size();
    //qDebug()<<"Size of y:"<<y.size();
}
void DisplayGraph::blah(){
    drawPlot();

}

void DisplayGraph::clear(){
    emit userClearedPlot();
}

void DisplayGraph::drawPlot(){
    QVector<double> u;
    customPlot->xAxis->setRange(0, x.size());
    customPlot->graph(0)->setData(x, y);
    u = y;  //copy it so we can align them from lowest to highest to get the range
    // give the axes some labels:
    customPlot->xAxis->setLabel("Time");
    //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    //customPlot->yAxis->setLabel("Ozone (ppb)");
    // set axes ranges, so we see all data:
    //customPlot->xAxis->setRange(0, 100);
    std::sort(u.begin(),u.end());
    //int highest_value;
    //qDebug()<<"Max value is:"<<u.last();
    customPlot->yAxis->setRange(u.first()-1, u.last()+1);
    customPlot->replot();

}

void DisplayGraph::setYaxisLabel(QString label){
    customPlot->yAxis->setLabel(label);
}

