#include "configform.h"
#include "ui_configform.h"

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm){
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
}

ConfigForm::~ConfigForm(){
    delete ui;
}
