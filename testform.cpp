#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::on_pushButton_clicked(){
    count++;
    for(int i = 0; i < 10; i++){
        //SerialHandler::getHandler()->writeAsync(new QString("Echo"));
        SerialHandler::getHandler()->writeAsync(new QString(QString::number(i)));
    }
    qDebug() << "Sent";
    if(count ==5)
        close();
    //close();
}
