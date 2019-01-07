#ifndef STATSMENUFORM_H
#define STATSMENUFORM_H

#include <QWidget>

#include "uimanager.h"

namespace Ui {
class StatsMenuForm;
}

class StatsMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatsMenuForm(QWidget *parent = nullptr);
    ~StatsMenuForm();

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
    Ui::StatsMenuForm *ui;
};

#endif // STATSMENUFORM_H
