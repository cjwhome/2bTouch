#include "selectgasdialog.h"
#include "ui_selectgasdialog.h"

#include <QGridLayout>
#include <QCheckBox>

SelectGasDialog::SelectGasDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectGasDialog)
{
    ui->setupUi(this);
}

SelectGasDialog::SelectGasDialog (QWidget *parent, QList<GasDataState *> * states) :
    QDialog(parent),
    ui(new Ui::SelectGasDialog)
{
    gasses = states;
    ui->setupUi(this);
    numGasses = states->size();
    /*QGridLayout *layout = ui->gridLayout;
    for(int i = 0; i < states->size(); i++)
    {
        int row = i / 3;
        int column = i %3;
        QCheckBox * nBox = new QCheckBox();
        nBox->setText("Gas " + QString(i));
        layout->addWidget(nBox, row, column);
    }*/
}

void SelectGasDialog::update()
{
    if(numGasses == 0 )
    {
        numGasses = gasses->size();
        QGridLayout *layout = ui->gridLayout;
        for(int i = 0; i < gasses->size(); i++)
        {
            int row = i / 3;
            int column = i %3;
            QCheckBox * nBox = new QCheckBox();
            nBox->setText("Gas " + *gasses->at(i)->name);
            layout->addWidget(nBox, row, column);
        }
    }
}

SelectGasDialog::~SelectGasDialog()
{
    delete ui;
}
