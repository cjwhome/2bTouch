#include "statsaverageform.h"
#include "ui_statsaverageform.h"

StatsAverageForm * StatsAverageForm::form = nullptr;

StatsAverageForm * StatsAverageForm::getForm(){
    //qDebug() << "Accessing stats average form";
    if(form == nullptr)
        form = new StatsAverageForm();
    return form;
}

StatsAverageForm::StatsAverageForm(QWidget *parent, QList<GasDataState *> * d) :
    QWidget(parent),
    ui(new Ui::StatsAverageForm){
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    data = d;

    if(form != nullptr){
        form = this;
    }

    if(d != 0x0){
        QStringList * list = new QStringList();
        for(int i = 0; i < data->size(); i++){
            if(data->at(i)->unit != ""){
                list->append(*data->at(i)->name);
            }
        }
        ui->selectGas->clear();
        ui->selectGas->addItems(*list);
    }
    form = this;
    currentGas = "No";
}

StatsAverageForm::~StatsAverageForm(){
    delete ui;
}

void StatsAverageForm::on_home_clicked(){
    hide();
}

void StatsAverageForm::on_mNext_clicked(){
    UiManager * manager = UiManager::getManager();
    if(manager->cStatIndex + 1 >= manager->statsWidgets->count()){
        manager->cStatIndex = 0;
    }else{
        manager->cStatIndex += 1;
    }
    manager->cStatWidget->hide();
    manager->cStatWidget = manager->statsWidgets->at(manager->cStatIndex);
    manager->cStatWidget->show();
}

void StatsAverageForm::on_mPrev_clicked(){
    UiManager * manager = UiManager::getManager();
    if(manager->cStatIndex - 1 <= -1){
        manager->cStatIndex = manager->statsWidgets->count() - 1;
    }
    manager->cStatWidget->hide();
    manager->cStatWidget = manager->statsWidgets->at(manager->cStatIndex);
    manager->cStatWidget->show();
}

void StatsAverageForm::on_selectGas_activated(int index){
    qDebug() << "Clicked: " << index;
    currentGasIndex = index;
    currentGas = *data->at(currentGasIndex)->name;

    int numDH = 2; // Numbers before being cut
    int numDE = 2;
    double avgHour = data->at(currentGasIndex)->getHourAverage();
    double avgEight = data->at(currentGasIndex)->getEightAverage();
    if(std::abs(avgHour) >= 10){
        numDH = 3;
    }
    if(std::abs(avgEight) >= 10){
        numDE = 3;
    }
    QString("<font color='green'>" + QString::number(avgHour, 'G', numDH) + "</font> " + data->at(currentGasIndex)->unit);
    QString("<font color='green'>" + QString::number(avgEight, 'G', numDE) + "</font> " + data->at(currentGasIndex)->unit);
}

void StatsAverageForm::updateAvg(){
    if(currentGas == "No"){
        qDebug() << "No";
    }
    else if(currentGas == "Nox"){
        qDebug() << "Nox";
    }
    else if(currentGas == "No2"){
        qDebug() << "No2";
    }else{
        if(currentGas == "")
        {
            qDebug() << "Got to bottom but was empty";
        }else{
            qDebug() << "Failed add new statement for '" << currentGas << "'";
        }
    }
}
