#include "landingpage.h"
#include "ui_landingpage.h"

LandingPage::LandingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandingPage)
{
    ui->setupUi(this);
}

LandingPage::~LandingPage(){
    delete ui;
}

void LandingPage::on_save_clicked(){
    //qDebug() << "Sending index: " << cIndex;
    //SerialHandler->getSer
    emit picked(new QString(cIndex));
    SerialQueue::getQueue()->add(QString::number(cIndex));
    SerialQueue::getQueue()->add(QString("*l" + QString::number(log)));
    //printf("*%i", cIndex);
    hide();
}

void LandingPage::on_gasSelect_currentIndexChanged(int index){
    cIndex = index;
}

void LandingPage::on_checkBox_stateChanged(int arg1){
    qDebug() << "check box: " << arg1;
    if(arg1 == 2){
        log = true;
    }else{
        log = false;
    }
}
