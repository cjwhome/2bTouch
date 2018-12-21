#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QList>
#include <QNetworkInterface>
#include <QProcess>
#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager * getManager();
    void connect();
    void disconnect();
    void findNetworks();
    QString getIP();
    QString getNetworkName();

    int currentNetwork = 0; //index of network in networks
    QString password;
    bool connected = true;
    QList<QString> * networks;

signals:
    void getPassword(QString pass);

private:
    static NetworkManager * manager;
    explicit NetworkManager(QWidget*parent=nullptr);
};

#endif // NETWORKMANAGER_H
