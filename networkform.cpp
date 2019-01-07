#include "networkform.h"
#include "ui_networkform.h"

NetworkForm::NetworkForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkForm){
    UiManager * uManager = UiManager::getManager();
    if(NetworkManager::getManager()->connected && uManager->finishedCreating)
    {
        //Needs better spot to be created at
        uManager->cWidget = uManager->network;
        uManager->network->show();
        hide();
    }

    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    QString passString;
    passString = NetworkManager::getManager()->password = "Password";

    passwordEdit = new KeyLineEdit(passString, this);
    passwordEdit->setGeometry(ui->placeHolder->geometry());
    passwordEdit->setText(passString);

    connTable = new QTableWidget(0, 1, this);
    connTable->setGeometry(ui->mainPlace->geometry());
    connTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList labels;
    labels << tr("SSID");
    connTable->setHorizontalHeaderLabels(labels);
    connTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    connTable->verticalHeader()->hide();
    connTable->setShowGrid(false);

    QList<QString> * availableNets = NetworkManager::getManager()->networks;
    for(int i = 0; i < availableNets->length(); i++) {
        QString ssid = availableNets->at(i);
        QTableWidgetItem *item = new QTableWidgetItem(ssid);
        int row = connTable->rowCount();
        connTable->insertRow(row);
        connTable->setItem(row, 0, item);
    }

    manager = NetworkManager::getManager();
    connect(passwordEdit, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(test(int,int)));
}

void NetworkForm::test(int a, int b)
{
    qDebug() << "Old: " << a << " New: " << b;
}

NetworkForm::~NetworkForm()
{
    delete ui;
}

void NetworkForm::on_mPrev_clicked()
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

void NetworkForm::cPassword(QString pass)
{
    passwordText = pass;
}

void NetworkForm::on_home_clicked()
{
    hide();
}

void NetworkForm::on_mNext_clicked()
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

void NetworkForm::on_connect_clicked()
{
    NetworkManager::getManager()->connect();
    UiManager * ui = UiManager::getManager();
    ui->cWidget = ui->network;
    ui->cWidget->show();
    hide();
}

void NetworkForm::changePasswordEdit()
{
    QString temp = "";
    for(int i = 0; i < passwordEdit->text().length(); i++)
    {
        temp += '*';
    }
    passwordText = passwordEdit->text();
    passwordEdit->text() = temp;
}

void NetworkForm::changeBackPasswordEdit()
{
    passwordEdit->text() = passwordText;
}
