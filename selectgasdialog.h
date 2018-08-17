#ifndef SELECTGASDIALOG_H
#define SELECTGASDIALOG_H

#include <QDialog>
#include <QObject>

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

private:
    Ui::SelectGasDialog *ui;
    QList<GasDataState *> * gasses;
    int numGasses;
};

#endif // SELECTGASDIALOG_H
