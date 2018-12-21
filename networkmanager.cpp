#include "networkmanager.h"

NetworkManager * NetworkManager::manager = nullptr;

NetworkManager * NetworkManager::getManager()
{
    if(manager == nullptr)
    {
        manager = new NetworkManager();
    }
    return manager;
}

NetworkManager::NetworkManager(QWidget * parent) : QObject ()
{
    QObject::setParent(reinterpret_cast<QObject *>(parent));
    findNetworks();
    password = "****";
    connected = false;
}

void NetworkManager::findNetworks()
{
    networks = new QList<QString>();
    qDebug()<<"Looking For Available Networks";
    QString prog = "/bin/bash";
    QStringList args;
    args<<"-c"<<"sudo iwlist wlan0 scan";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();
    QString response = process->readAll();
    qDebug()<<"Response: "<<response;

    QStringList cells = response.split("Cell ");
    qDebug()<<"Cells: "<<cells;
    if(cells.length() > 1) {
        for(int i = 1; i < cells.length(); i++) {
            QString cell = cells.at(i);
            qDebug()<<"Cell: "<<cell;
            QStringList info = cell.split("\n");
            qDebug()<<"Info: "<<info;
            QString ssidLine = info.at(1);
            qDebug()<<"SSID Line: "<<ssidLine;
            QString ssid = ssidLine.split(":").at(1);
            ssid.remove("\"");
            if(!networks->contains(ssid)) {
                networks->append(ssid);
            }
        }
    } else {
        networks->append("No Networks Found");
    }
}

QString NetworkManager::getIP()
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

QString NetworkManager::getNetworkName()
{
    if(networks->count() == 0)
    {
        return "NULL";
    }
    return networks->at(currentNetwork);
}

void NetworkManager::connect()
{
    QString prog = "/bin/bash";

    QStringList args_write;
    QString new_net = "printf \" \n network={ \n ssid=\\\""+networks->at(currentNetwork)+"\\\" \n psk=\\\""+password+"\\\" \n } \n \" >> /etc/wpa_supplicant/wpa_supplicant.conf";
    args_write<<"-c"<<new_net;
    QProcess *write = new QProcess();
    write->start(prog, args_write);
    write->waitForFinished();

    QStringList args_down;
    args_down<<"-c"<<"sudo ifdown wlan0";

    QProcess *down = new QProcess();
    down->start(prog, args_down);
    down->waitForFinished();

    QStringList args_up;
    args_up<<"-c"<<"sudo ifup wlan0";

    QProcess *up = new QProcess();
    up->start(prog, args_up);
    up->waitForFinished();
    connected = true;
}

void NetworkManager::disconnect()
{
    QString prog = "/bin/bash";
    QStringList args;
    args<<"-c"<<"sudo iwconfig | grep wlan0";

    QProcess *process = new QProcess();
    process->start(prog, args);
    process->waitForFinished();

    QString ret = process->readAll();
    qDebug()<<args;
    qDebug()<<ret;
    ret = ret.split("wlan0").at(1);
    qDebug()<<ret;
    ret = ret.split(QString('"')).at(1);
    qDebug()<<ret;

    args.clear();
    args<<"-c"<<"awk '/"+ret+"/ {print NR;exit}' /etc/wpa_supplicant/wpa_supplicant.conf";
    qDebug()<<args;
    process->start(prog, args);
    process->waitForFinished();

    ret = process->readAll();
    qDebug()<<ret;
    int lineNum = ret.toInt();
    int bottom = lineNum-1;
    int top = lineNum+3;
    args.clear();
    args<<"-c"<<"sudo sed -i.back -e '"+QString::number(bottom)+","+QString::number(top)+"d' /etc/wpa_supplicant/wpa_supplicant.conf";
    qDebug()<<args;
    process->start(prog, args);
    process->waitForFinished();

    args.clear();
    args<<"-c"<<"sudo ifdown wlan0";
    process->start(prog, args);
    process->waitForFinished();
    connected = false;
}
