#ifndef STATSAVERAGEFORM_H
#define STATSAVERAGEFORM_H

#include <QWidget>
#include <QString>
#include <QDebug>

#include "uimanager.h"
#include "gasdatastate.h"

namespace Ui {
class StatsAverageForm;
}

class StatsAverageForm : public QWidget{
Q_OBJECT

public:
    explicit StatsAverageForm(QWidget *parent = nullptr, QList<GasDataState *> * d = nullptr);
    void updateAvg();
    ~StatsAverageForm();
    static StatsAverageForm * getForm();

private slots:
    void on_home_clicked();

    void on_mNext_clicked();

    void on_mPrev_clicked();

    void on_selectGas_activated(int index);

private:
    Ui::StatsAverageForm *ui;
    static StatsAverageForm * form;

    QString currentGas;
    QList<GasDataState *> * data = nullptr;
    int currentGasIndex = 0;

};

#endif // STATSAVERAGEFORM_H
