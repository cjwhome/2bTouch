#include "scannetworksview.h"
#include "ui_scannetworksview.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>
#include <QScrollBar>


ScanNetworksView::ScanNetworksView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanNetworksView)
{
    ui->setupUi(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    networkListView = new QListView();
    networkListView->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
    QFrame* horizontalFrame = new QFrame();
    horizontalFrame->setFrameShape(QFrame::HLine);

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    QPushButton *scanButton = new QPushButton("Scan");
    verticalLayout->addWidget(scanButton);
    verticalLayout->addWidget(networkListView);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addWidget(homeButton);



    //QStringList blah = scanNetworks();
    connect(scanButton, SIGNAL(clicked()), this, SLOT(scanNetworks()));
    //qDebug()<<"Scanned networks:"<<blah;
    this->setLayout(verticalLayout);
}

ScanNetworksView::~ScanNetworksView()
{
    delete ui;
}

void ScanNetworksView::scanNetworks(void){

    QString prog = "/bin/bash";     //shell
    QStringList arguments;
    arguments << "-c" << "iwlist wlan0 scan | grep 'ESSID'";

    QProcess *process = new QProcess();
    process->start(prog , arguments);
    process->waitForFinished();
    QString networks = process->readAll();

    QStringList pieces = networks.split( "ESSID:" );
    QStringList parsedNetworkNames;
    //int i = 0;
    if(!pieces.isEmpty()){

        foreach(QString ssid, pieces){
            //ssid.remove("ESSID:");
            //ssid.remove(QRegExp(","));
            //ssid = ssid.replace("\"","");
            //ssid.replace(",","");
            parsedNetworkNames.append(extractString(ssid));
            //qDebug()<<"size:"<<ssid.size()<<" "<<ssid;
        }
        networkListModel = new QStringListModel(parsedNetworkNames, NULL);
        networkListView->setModel(networkListModel);
    }
    /*int count = 0;
    foreach(QString parsed_ssid, parsedNetworkNames){
        QString new_ssid = extractString(parsed_ssid);
        qDebug()<<count++<<":"<<new_ssid<<"End";
    }*/

    //qDebug()<<"ParsedNetworks:";
    //qDebug()<<parsedNetworkNames;
    //return parsedNetworkNames;
    //qDebug() << "Wifi Networks: "<<networks;
    //qDebug() << "List:"<<pieces;
}

//pulls out a string (ESSID) between two sets of quotation marks
QString ScanNetworksView::extractString(QString text){

    QString found_text;
    QRegExp re("\"([A-Za-z0-9_\\./\\-\\s]*)\"");

    int pos=0;
    pos=re.indexIn(text, pos);
    found_text=re.cap(1);

    return found_text;
}
