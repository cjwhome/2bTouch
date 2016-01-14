#ifndef SHOWSTATS_H
#define SHOWSTATS_H

#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtGui>
#include <QPushButton>
#include <QList>
#include <QGridLayout>
#include <algorithm>
#include "serialdataitem.h"
#include "deviceprofile.h"

namespace Ui {
class ShowStats;
}

class ShowStats : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ShowStats(QWidget *parent = 0);
    ~ShowStats();
    void setData(QList< QList<SerialDataItem> > *records, DeviceProfile *deviceProfile);    //send the data records list and device profile so the displays can be updated with the latest data
    void calculateMaxMinMedian(QList<QList<SerialDataItem> > *records, DeviceProfile *deviceProfile);
private:
    Ui::ShowStats *ui;
    QLabel *diagnosticA_output;
    QLabel *diagnosticA_label;
    QLabel *diagnosticA_units_label;
    QLabel *diagnosticB_output;
    QLabel *diagnosticB_label;
    QLabel *diagnosticB_units_label;
    QLabel *diagnosticC_output;
    QLabel *diagnosticC_label;
    QLabel *diagnosticC_units_label;
    QLabel *max_label;
    QLabel *max_output;
    QLabel *max_units;

};

#endif // SHOWSTATS_H
