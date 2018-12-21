#ifndef NETWORKCONNECTEDFORM_H
#define NETWORKCONNECTEDFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QNetworkInterface>

#include "uimanager.h"
#include "networkmanager.h"

namespace Ui {
class NetworkConnectedForm;
}

class NetworkConnectedForm : public QWidget{
    Q_OBJECT

public:
    explicit NetworkConnectedForm(QWidget *parent = nullptr);
    ~NetworkConnectedForm();

private slots:
    void on_Home_clicked();

    void on_mNext_clicked();

    void on_mPrev_clicked();

    void on_Disconnect_clicked();

private:
    Ui::NetworkConnectedForm *ui;

    QString checkNetwork();
};

#endif // NETWORKCONNECTEDFORM_H
