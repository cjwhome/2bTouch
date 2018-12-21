#ifndef SELECTGASFORM_H
#define SELECTGASFORM_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>

#include "gasdatastate.h"

namespace Ui {
class SelectGasForm;
}

class SelectGasForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectGasForm(QWidget *parent = nullptr,  QList<GasDataState *> * states = nullptr);
    explicit SelectGasForm(QWidget *parent = nullptr);
    ~SelectGasForm();

public slots:
    void update();
    void boxSelected(int state);

private:
    Ui::SelectGasForm *ui;
    QList<GasDataState *> * gasses;
    int numGasses;
    QList<QCheckBox*> * boxes;
    QList<QColor> *colors;
    QPushButton *apply;
};

#endif // SELECTGASFORM_H
