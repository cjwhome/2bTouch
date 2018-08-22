#ifndef SELECTGASDIALOG_H
#define SELECTGASDIALOG_H

#include <QDialog>
#include <QObject>
#include <QCheckBox>

#include "gasdatastate.h"

namespace Ui {
class SelectGasDialog;
}

class SelectGasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectGasDialog(QWidget *parent = nullptr,  QList<GasDataState *> * states = nullptr);
    explicit SelectGasDialog(QWidget *parent = nullptr);
    ~SelectGasDialog();

public slots:
    void update();
    void boxSelected(int state);

private:
    Ui::SelectGasDialog *ui;
    QList<GasDataState *> * gasses;
    int numGasses;
    QList<QCheckBox*> * boxes;
    QList<QColor> *colors;
    QPushButton *apply;
};

#endif // SELECTGASDIALOG_H
