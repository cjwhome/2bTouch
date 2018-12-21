#ifndef MENUTREEFORM_H
#define MENUTREEFORM_H

#include <QWidget>

#include "uimanager.h"

namespace Ui {
class MenuTreeForm;
}

class MenuTreeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MenuTreeForm(QWidget *parent = nullptr);
    ~MenuTreeForm();

private slots:
    void on_Calibration_clicked();

    void on_Network_clicked();

    void on_DateTime_clicked();

    void on_Analog_clicked();

    void on_Averages_clicked();

    void on_Modbus_clicked();

    void on_Home_clicked();

    void on_mNext_clicked();

    void on_mPrevious_clicked();

private:
    Ui::MenuTreeForm *ui;
};

#endif // MENUTREEFORM_H
