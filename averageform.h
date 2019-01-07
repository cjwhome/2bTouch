#ifndef AVERAGEFORM_H
#define AVERAGEFORM_H

#include <QWidget>
#include <QDebug>
#include <QStringListModel>
#include <QListWidgetItem>

#include "uimanager.h"
#include "gasdatastate.h"
#include "richtextdelegate.h"

namespace Ui {
class AverageForm;
}

class AverageForm : public QWidget{
    Q_OBJECT

public:
    explicit AverageForm(QWidget *parent = nullptr, QList<GasDataState *> * = nullptr, bool sts = false);
    ~AverageForm();

private slots:
    void on_pushButton_clicked();
    void on_mNext_clicked();
    void on_mPrevious_clicked();
    void on_listView_pressed(const QModelIndex &index);
    void update();

private:
    QStringListModel * model = nullptr;
    int currentGasIndex = 0;
    Ui::AverageForm *ui = nullptr;
    QList<GasDataState *> * gases = nullptr;
    bool stats = false; //Determines if it is in the stats list or the settings list
};

#endif // AVERAGEFORM_H
