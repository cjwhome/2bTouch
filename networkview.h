#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QWidget>
#include <QString>
#include <QLabel>


namespace Ui {
class NetworkView;
}

class NetworkView : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkView(QWidget *parent = 0);
    ~NetworkView();

private slots:
    void showScanNetworkView();

private:
    Ui::NetworkView *ui;
    //void getBashIPAddress(void);
    void getQtIPAddress(void);
    QLabel *qtIPaddress;
    QStringList scanNetworks(void);
    QString extractString(QString text);
    QLabel *networkName;
    //QLabel *bashIPaddress;
};

#endif // NETWORKVIEW_H
