#include "modform.h"
#include "ui_modform.h"

ModForm::ModForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModForm)
{
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
}

ModForm::~ModForm()
{
    delete ui;
}

void ModForm::on_home_clicked()
{
    hide();
}

void ModForm::on_mNext_clicked()
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

void ModForm::on_mPrev_clicked()
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
