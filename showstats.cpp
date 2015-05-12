#include "showstats.h"
#include "ui_showstats.h"

ShowStats::ShowStats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowStats)
{
    ui->setupUi(this);
}

ShowStats::~ShowStats()
{
    delete ui;
}
