#include "displaygraph.h"
#include "ui_displaygraph.h"

DisplayGraph::DisplayGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGraph)
{
    ui->setupUi(this);
}

DisplayGraph::~DisplayGraph()
{
    delete ui;
}
