#ifndef MODBUSFORM_H
#define MODBUSFORM_H

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "uimanager.h"
#include "keylineedit.h"
#include "modbusserver.h"

namespace Ui {
class ModbusForm;
}

class ModbusForm : public QWidget{
    Q_OBJECT

public:
    explicit ModbusForm(QWidget *parent = nullptr);
    ~ModbusForm();

private slots:


    void on_mNext_clicked();

    void on_mPrev_clicked();

    void on_save_clicked();

    void on_home_clicked();

private:
    Ui::ModbusForm *ui;

    KeyLineEdit * entry;
    KeyLineEdit * address;
};

#endif // MODBUSFORM_H
