#ifndef NETWORKFORM_H
#define NETWORKFORM_H

#include <QWidget>
#include <QProcess>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

#include "keylineedit.h"
#include "uimanager.h"
#include "networkconnectedform.h"
#include "networkmanager.h"

namespace Ui {
class NetworkForm;
}

class NetworkForm : public QWidget{
    Q_OBJECT

public:
    explicit NetworkForm(QWidget *parent = nullptr);
    ~NetworkForm();

private slots:
    void on_mPrev_clicked();

    void on_home_clicked();

    void on_mNext_clicked();

    void on_connect_clicked();

    void changePasswordEdit();

    void changeBackPasswordEdit();

    void test(int,int);

    void cPassword(QString);

private:
    KeyLineEdit * passwordEdit;
    QString passwordText;
    QTableWidget * connTable;
    Ui::NetworkForm *ui;

    NetworkManager * manager;
};

#endif // NETWORKFORM_H
