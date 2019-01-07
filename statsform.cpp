#include "statsform.h"
#include "ui_statsform.h"

StatsForm::StatsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsForm)
{
    ui->setupUi(this);
}

StatsForm::~StatsForm()
{
    delete ui;
}

void StatsForm::on_home_clicked()
{
    hide();
}

void StatsForm::on_mNext_clicked()
{

}

void StatsForm::on_mPrev_clicked()
{

}

void StatsForm::on_selectGas_activated(int index)
{

}
