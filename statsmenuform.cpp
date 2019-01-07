#include "statsmenuform.h"
#include "ui_statsmenuform.h"

StatsMenuForm::StatsMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsMenuForm)
{
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
}

StatsMenuForm::~StatsMenuForm(){
    delete ui;
}

//Index defined in uimanager.h
//If the user clicks on the calibration button jump to the calibration page
void StatsMenuForm::on_Calibration_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = calIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(calIndex);
    ui->cWidget->show();
}

//Index defined in uimanager.h
//If the user clicks on the Network button jump to the Network page
void StatsMenuForm::on_Network_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = networkIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(networkIndex);
    ui->cWidget->show();
}

//Index defined in uimanager.h
//If the user clicks on the Network button jump to the Network page
void StatsMenuForm::on_DateTime_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = dateTimeIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(dateTimeIndex);
    ui->cWidget->show();
}

//Index defined in uimanager.h
//If the user clicks on the analog button jump to the analog page
void StatsMenuForm::on_Analog_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = analogIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(analogIndex);
    ui->cWidget->show();
}

//Index defined in uimanager.h
//If the user clicks on the averages button jump to the averages page
void StatsMenuForm::on_Averages_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = averageIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(averageIndex);
    ui->cWidget->show();
}

//Index defined in uimanager.h
//If the user clicks on the modbus button jump to the modbus page
void StatsMenuForm::on_Modbus_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = modbusIndex;
    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(modbusIndex);
    ui->cWidget->show();
}

void StatsMenuForm::on_Home_clicked(){
    UiManager * ui = UiManager::getManager();
    ui->currentSIndex = 0;
    ui->cWidget->hide();
    ui->cWidget = nullptr;
}

void StatsMenuForm::on_mNext_clicked(){
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

void StatsMenuForm::on_mPrevious_clicked()
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
