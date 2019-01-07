#ifndef DATETIMEFORM_H
#define DATETIMEFORM_H

#include <QDebug>
#include <QWidget>
#include <QTextStream>
#include <QThread>

#include "uimanager.h"
#include "serialhandler.h"
//#include "grabdata.h"

namespace Ui {
class DateTimeForm;
}

class DateTimeForm : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeForm(QWidget *parent = nullptr);
    ~DateTimeForm();

    static DateTimeForm * getForm();

    void getCurrent(int,int,int,int,int,int);

    void updateDisplay();

    QString returnCurrent();

    void addSec();

private:
    int hour;
    int min;
    int sec;
    int month;
    int day;
    int year;

    int currentTIndex = 0;
    int currentCIndex = 0;

    void updateTime();
    void updateDate();

    int daysInMonth();

    QString stripString(QString);

    static DateTimeForm * form;

public slots:
    void on_save_clicked();

private slots:
    void on_home_clicked();

    void on_gonext_clicked();

    void on_goPrev_clicked();

    void on_mRightT_clicked();

    void on_mLeftT_clicked();

    void on_increaseT_clicked();

    void on_decreaseT_clicked();

    void on_increaseC_clicked();

    void on_decreaseC_clicked();

    void on_mRightC_clicked();

    void on_mLeftC_clicked();

    void updateDis();

signals:
    void addSecond();

private:
    Ui::DateTimeForm *ui;
};

#endif // DATETIMEFORM_H
