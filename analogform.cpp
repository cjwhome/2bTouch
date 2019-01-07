#include "analogform.h"
#include "ui_analogform.h"

AnalogForm * AnalogForm::form = nullptr;

AnalogForm * AnalogForm::getForm(){
    //qDebug() << "Accessing analog form";
    if(form == nullptr)
        form = new AnalogForm();
    return form;
}

AnalogForm::AnalogForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalogForm){
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
}


void AnalogForm::update(QString data){
    currentScale = data.toInt();
}

AnalogForm::~AnalogForm(){
    delete ui;
}

void AnalogForm::setStartSclae(int s){
    currentScale = s;
    ui->value->setText(QString::number(currentScale));
}

void AnalogForm::on_mNext_clicked(){
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex + 1 == ui->settingWidgets->count())
    {
        ui->currentSIndex = 0;
    }
    else
    {
        ui->currentSIndex += 1;
    }

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

void AnalogForm::on_mPrevious_clicked()
{
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex - 1 == -1)
    {
        ui->currentSIndex = ui->settingWidgets->count() - 1;
    }
    else
    {
        ui->currentSIndex -= 1;
    }

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

void AnalogForm::on_home_clicked()
{
    hide();
}

//When the save button is clicked send the new setting to the pcb to save and use it
void AnalogForm::on_save_clicked(){
   //QTextStream(stdout) << "*A" << QString::number(currentScale) << "\n";//* tells that this is a command and A tells what.
    QString s("*A" + QString::number(currentScale) + "\n");
    QThread * thread = new QThread();
    SerialHandler::getHandler(thread, this)->writeLine(s);
    //SerialHandler::getHandler()->serialPort->write(s.toStdString().c_str());
}

//Incriment the current scale up by 10 when clicked
void AnalogForm::on_increase_clicked(){
    if(currentScale < 1000){
        currentScale += 10;
        ui->value->setText(QString::number(currentScale));
    }
}

//Decrease the current scale by 10 when clicked
void AnalogForm::on_decrease_clicked(){
    if(currentScale > 0){
        currentScale -= 10;
        ui->value->setText(QString::number(currentScale));
    }
}

//get method for the scale
int AnalogForm::getScale(){
    return currentScale;
}

//setter method for the scale
void AnalogForm::setScale(int val){
    currentScale = val;
}
