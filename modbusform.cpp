#include "modbusform.h"
#include "ui_modbusform.h"

ModbusForm::ModbusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModbusForm){
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    entry = new KeyLineEdit("Custom Edit", this);
    address = new KeyLineEdit("0", this);

    ui->layout->addWidget(entry);
    ui->layout->addWidget(address);
}

ModbusForm::~ModbusForm(){
    delete ui;
}

/*!
 * This slot is called when the user clicks on the next button in the UI
 * */
void ModbusForm::on_mNext_clicked()
{
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

void ModbusForm::on_mPrev_clicked()
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

void ModbusForm::on_save_clicked()
{
    ModbusServer::getInstance()->deleteRegister(UiManager::getManager()->settings->value("modbus_CUSTOMADDR", 50).toInt());
    UiManager::getManager()->settings->setValue("modbus_CUSTOMSTR", entry->text());
    UiManager::getManager()->settings->setValue("modbus_CUSTOMADDR", address->text());
    ModbusServer::getInstance()->updateRegister(address->text().toInt(), entry->text());
}

/*!
 * This closes the mod bus page
 */
void ModbusForm::on_home_clicked()
{
    hide();
}
