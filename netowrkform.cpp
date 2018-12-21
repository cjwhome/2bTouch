#include "netowrkform.h"
#include "ui_netowrkform.h"

NetowrkForm::NetowrkForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetowrkForm)
{
    ui->setupUi(this);
}

NetowrkForm::~NetowrkForm()
{
    delete ui;
}
