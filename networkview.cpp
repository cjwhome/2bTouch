#include "networkview.h"
#include "ui_networkview.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <QtNetwork>
#include "scannetworksview.h"

//using namespace std;

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    //bashIPaddress = new QLabel("BashIP");
    qtIPaddress = new QLabel("IP Address");
    networkName = new QLabel("Network Name");
    QPushButton *findNetworksButton = new QPushButton("Find New Network");

    QFrame* horizontalFrame = new QFrame();
    horizontalFrame->setFrameShape(QFrame::HLine);

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    //verticalLayout->addWidget(bashIPaddress);
    verticalLayout->addWidget(networkName);
    verticalLayout->addWidget(qtIPaddress);
    verticalLayout->addWidget(findNetworksButton);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addWidget(homeButton);

    this->setLayout(verticalLayout);

    connect(homeButton, SIGNAL(released()), this, SLOT(close()));
    connect(findNetworksButton, SIGNAL(clicked()), this, SLOT(showScanNetworkView()));

    getQtIPAddress();

}

NetworkView::~NetworkView()
{
    delete ui;
}

void NetworkView::showScanNetworkView()
{
    ScanNetworksView *scanNetworksView = new ScanNetworksView();
    scanNetworksView->show();
}




void NetworkView::getQtIPAddress(void){
    QNetworkInterface wlan0Ip = QNetworkInterface::interfaceFromName("wlan0");
    QList<QNetworkAddressEntry> entries = wlan0Ip.addressEntries();
    if (!entries.isEmpty()) {
        QNetworkAddressEntry entry = entries.first();

        qtIPaddress->setText("wifi address: " + entry.ip().toString());
    }else{
        //qtIPaddress->setText("Check wifi");
        QNetworkInterface eth0Ip = QNetworkInterface::interfaceFromName("eth0");
        entries = eth0Ip.addressEntries();
        if(!entries.isEmpty()){
            QNetworkAddressEntry entry = entries.first();
            qtIPaddress->setText("eth address: " + entry.ip().toString());
        }else{
            qtIPaddress->setText("Check network connection");
        }
    }
}

