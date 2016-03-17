#include "networkview.h"
#include "ui_networkview.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <QtNetwork>

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    bashIPaddress = new QLabel("BashIP");
    qtIPaddress = new QLabel("QtIP");

    QFrame* horizontalFrame = new QFrame();
    horizontalFrame->setFrameShape(QFrame::HLine);

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    verticalLayout->addWidget(bashIPaddress);
    verticalLayout->addWidget(qtIPaddress);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addWidget(homeButton);

    this->setLayout(verticalLayout);

    connect(homeButton, SIGNAL(released()), this, SLOT(close()));

    //getBashIPAddress();
    getQtIPAddress();
}

NetworkView::~NetworkView()
{
    delete ui;
}


void NetworkView::getBashIPAddress(void){
    QString prog = "/bin/bash";     //shell
    QStringList arguments;
    //arguments << "-c" << "ifconfig eth0 | grep 'inet ' | awk '{print $2}' | sed 's/addr://'";
    arguments << "-c" << "ifconfig wlan0 | grep 'inet ' | awk '{print $2}' | sed 's/addr://'";
    QProcess *process = new QProcess();
    process->start(prog , arguments);
    process->waitForFinished();
    QString ipaddress = process->readAll();
    qDebug() << "Bash Ipaddress: "<<ipaddress;
    bashIPaddress->setText(ipaddress);
    //return ipaddress;

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
