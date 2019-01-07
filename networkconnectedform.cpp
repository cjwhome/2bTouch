#include "networkconnectedform.h"
#include "ui_networkconnectedform.h"

NetworkConnectedForm::NetworkConnectedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkConnectedForm){
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    ui->IPActual->text() = NetworkManager::getManager()->getIP();
    ui->NetworkNameActual->text() = (NetworkManager::getManager()->getNetworkName());
}

QString NetworkConnectedForm::checkNetwork()
{
    QNetworkInterface wlan0 = QNetworkInterface::interfaceFromName("wlan0");
    QList<QNetworkAddressEntry> entries = wlan0.addressEntries();
    if(!entries.isEmpty()) {
        return entries.first().ip().toString();
    } else {
        QNetworkInterface eth0 = QNetworkInterface::interfaceFromName("eth0");
        QList<QNetworkAddressEntry> entries_eth0 = eth0.addressEntries();
        if(!entries_eth0.isEmpty()) {
            return entries_eth0.first().ip().toString();
        } else {
            return "false";
        }
    }
}

NetworkConnectedForm::~NetworkConnectedForm()
{
    delete ui;
}

void NetworkConnectedForm::on_Home_clicked()
{
    hide();
}

void NetworkConnectedForm::on_mNext_clicked()
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

void NetworkConnectedForm::on_mPrev_clicked()
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

void NetworkConnectedForm::on_Disconnect_clicked()
{
    NetworkManager::getManager()->disconnect();
    UiManager * ui = UiManager::getManager();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
    hide();
}
