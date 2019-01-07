#ifndef ANALOGFORM_H
#define ANALOGFORM_H

#include <QWidget>
#include <QDebug>

#include "uimanager.h"
#include "serialhandler.h"

//Notes
//It might be worth adding a valueChanged bool to prevent the user spamming too many requests to the pcb

namespace Ui {
class AnalogForm;
}

class AnalogForm : public QWidget{
    Q_OBJECT

public:
    explicit AnalogForm(QWidget *parent = nullptr);
    ~AnalogForm();

    void setStartSclae(int);

    virtual void update(QString); //Leftover from IUpdateData, but still might be used

    static AnalogForm * getForm();

    void setScale(int);
    int getScale(void);

private slots:
    void on_mNext_clicked();
    void on_mPrevious_clicked();
    void on_home_clicked();
    void on_save_clicked();
    void on_increase_clicked();
    void on_decrease_clicked();

private:
    Ui::AnalogForm *ui;
    int currentScale = 250;

    static AnalogForm * form;
};

#endif // ANALOGFORM_H
