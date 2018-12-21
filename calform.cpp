#include "calform.h"
#include "ui_calform.h"

CalForm * CalForm::form = nullptr;

CalForm * CalForm::getForm(){
    //qDebug() << "Accessing calform";
    if(form == nullptr)
        form = new CalForm();
    return form;
}

CalForm::CalForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalForm){
    ui->setupUi(this);
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    hide();
}

//Initialize the starting values, this will be updated one the app gets the values from the pcb
void CalForm::getInitialvalues(double a,int b,double c,int d,double e,int f){
    noSlope = a;
    noOffset = b;
    no2Slope = c;
    no2Offset = d;
    //There are no nox slopes or offsets
    noxSlope = e;
    noxOffset = f;
}

//This is called when the app recives a new value for the offset from the pcb for eiter gase
//The int argument is used to designate which value is being changed and the strign holds the data
/*void CalForm::update(int num, QString data){

}*/

CalForm::~CalForm(){
    delete ui;
}

void CalForm::on_home_clicked(){
    hide();
}

void CalForm::on_goNext_clicked(){
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex + 1 == ui->settingWidgets->count()){
        ui->currentSIndex = 0;
    }else{
        ui->currentSIndex += 1;
    }

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

void CalForm::on_goPrev_clicked(){
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex - 1 == -1){
        ui->currentSIndex = ui->settingWidgets->count() - 1;
    }else{
        ui->currentSIndex -= 1;
    }

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

//This changes which gas values are shown
void CalForm::on_selectGas_activated(int index){
    cIndex = index;
    updateDisplay();
}

//This updates the slope and offset text fields with the values specific to the currently selected gas
void CalForm::updateDisplay(){
    if(cIndex == 0){
        ui->offset->setText("Offset: " + QString::number(noOffset));
        ui->slope->setText("Slope: " + QString::number(noSlope));
    }else if(cIndex == 1){
        ui->offset->setText("Offset: " + QString::number(no2Offset));
        ui->slope->setText("Slope: " + QString::number(no2Slope));
    }else if(cIndex == 2){
        ui->offset->setText("Offset: " + QString::number(noxOffset));
        ui->slope->setText("Slope: " + QString::number(noxSlope));
    }
}

//Use this to get the proper format for the output string
QString stripString(QString s){
    QString n = "";
    for(int i = 0; i < s.size(); i++){
        if(s.at(i) != ' ' && s.at(i) != '"'){
            n += s.at(i);
        }
    }
    return n;
}

//* signals the pcb that this is a command
//The char following * signals what function it needs to do
//This prints to the console so that the pcb can receive it
//qDebug prints to stderr not stdout and qDebug has the potential to be disabled when not debugging
//QTextStream(stdout) is gauranteed to print to the console
void CalForm::on_save_clicked(){
    /*if(cIndex == 0){
        //qDebug() << "Setting NO slope to " + QString::number(noSlope) + " and NO offset to " + QString::number(noOffset);
        QTextStream(stdout) << stripString("*L" + QString::number(noSlope) + "," + QString::number(noOffset));
    }else if(cIndex == 1){
        //qDebug() << "Setting NO2 slope to " + QString::number(no2Slope) + " and NO2 offset to " + QString::number(no2Offset);
        QTextStream(stdout) << stripString("*C" + QString::number(no2Slope) + "," + QString::number(no2Offset));
    }*/
    //QTextStream(stdout) << stripString("*C" + QString::number(no2Slope) + "\n");
    //QTextStream(stdout) << stripString("*O" + QString::number(no2Offset) + "\n");
    //QTextStream(stdout) << stripString("*L" + QString::number(noSlope) + "\n");
    //QTextStream(stdout) << stripString("*K" + QString::number(noOffset) + "\n");

    QThread * thread = new QThread();
    SerialHandler::getHandler(thread, this)->writeLine(stripString("*C" + QString::number((int)(no2Slope * 10))));//multiply by 10 to save significant digits
    SerialHandler::getHandler(thread, this)->writeLine(stripString("*O" + QString::number(no2Offset)));
    SerialHandler::getHandler(thread, this)->writeLine(stripString("*L" + QString::number((int)(noSlope * 10))));//multiply by 10 to save significant digits
    SerialHandler::getHandler(thread, this)->writeLine(stripString("*K" + QString::number(noOffset)));
}

//This increases the slope value of the selected gas
void CalForm::on_increaseS_clicked(){
    if(cIndex == 0){
        noSlope += .1;
    }else if(cIndex == 1){
        no2Slope += .1;
    }else if(cIndex == 2){
        noxSlope += .1;
    }else{
        qDebug() << "Bad index";
    }
    updateDisplay();
}

//This decreases the slope of the selected gas
void CalForm::on_decreaseS_clicked(){
    if(cIndex == 0){
        noSlope -= .1;
    }else if(cIndex == 1){
        no2Slope -= .1;
    }else if(cIndex == 2){
        noxSlope -= .1;
    }else{
        qDebug() << "Bad index";
    }
    updateDisplay();
}

//This increases the offset of the selected gas
void CalForm::on_increaseO_clicked(){
    if(cIndex == 0){
        noOffset += 1;
    }else if(cIndex == 1){
        no2Offset += 1;
    }else if(cIndex == 2){
        noxOffset += 1;
    }else{
        qDebug() << "Bad index";
    }
    updateDisplay();
}

//This decreases the offset of the selected gas
void CalForm::on_decreaseO_clicked(){
    if(cIndex == 0){
        noOffset -= 1;
    }else if(cIndex == 1){
        no2Offset -= 1;
    }else if(cIndex == 2){
        noxOffset -= 1;
    }else{
        qDebug() << "Bad index";
    }
    updateDisplay();
}

int CalForm::getNOOffset(){
    return noOffset;
}

void CalForm::setNOOffset(int val){
    noOffset = val;
}

int CalForm::getNO2Offset(){
    return  no2Offset;
}

void CalForm::setNO2Offset(int val){
    no2Offset = val;
}

double CalForm::getNOSlope(){
    return noSlope;
}

void CalForm::setNOSlope(double val){
    noSlope = val;
}

double CalForm::getNO2Slope(){
    return no2Slope;
}

void CalForm::setNO2Slope(double val){
    no2Slope = val;
}
