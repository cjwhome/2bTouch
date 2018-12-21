#ifndef CALFORM_H
#define CALFORM_H

#include <QWidget>
#include <QDebug>
#include <QTextStream>

#include "uimanager.h"
#include "serialhandler.h"

namespace Ui {
class CalForm;
}

class CalForm : public QWidget
{
    Q_OBJECT

public:
    explicit CalForm(QWidget *parent = nullptr);
    ~CalForm();

    void getInitialvalues(double,int,double,int,double,int);
    void updateDisplay();

    //virtual void update(int, QString);//Leftover from IUpdateDate, but might still be used

    static CalForm * getForm();

    int getNOOffset(void);
    void setNOOffset(int);
    int getNO2Offset(void);
    void setNO2Offset(int);
    double getNOSlope(void);
    void setNOSlope(double);
    double getNO2Slope(void);
    void setNO2Slope(double);

private slots:
    void on_home_clicked();

    void on_goNext_clicked();

    void on_goPrev_clicked();

    void on_selectGas_activated(int index);

    void on_save_clicked();

    void on_increaseS_clicked();

    void on_decreaseS_clicked();

    void on_increaseO_clicked();

    void on_decreaseO_clicked();

private:
    Ui::CalForm *ui;
    static CalForm * form;
    int cIndex = 0;
    double noSlope;//NO_slope
    int noOffset;//NO_zero
    double no2Slope;//NO_slope
    int no2Offset;//NO_zero
    double noxSlope;
    int noxOffset;

};

#endif // CALFORM_H
