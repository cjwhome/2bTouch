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
    boxes = new QList<QCheckBox*>();
    gasses = states;
    ui->setupUi(this);
    numGasses = states->size();

    apply = ui->pushButton;
    connect(apply, SIGNAL(pressed()), this, SLOT(close()));

    colors = new QList<QColor>();
    colors->append((Qt::blue));
    colors->append((Qt::black));
    colors->append((Qt::cyan));
    colors->append((Qt::red));
    colors->append((Qt::magenta));
    colors->append((Qt::green));
    colors->append((Qt::yellow));
    colors->append((Qt::gray));
    colors->append((Qt::darkRed));
    colors->append((Qt::darkMagenta));
    colors->append((Qt::darkGreen));
    colors->append((Qt::darkYellow));
    colors->append((Qt::darkBlue));
    colors->append((Qt::darkGray));
}


void SelectGasDialog::update()
{
    QColor c = Qt::blue;
    if(numGasses == 0 )
    {
        boxes->clear();
        numGasses = gasses->size();
        QGridLayout *layout = ui->gridLayout;
        for(int i = 0; i < gasses->size(); i++)
        {
            int row = i / 3;
            int column = i %3;
            QCheckBox * nBox = new QCheckBox();
            nBox->setText(*gasses->at(i)->name);
            nBox->setStyleSheet("QCheckBox {color:" + colors->at(i).name() + "}");
            layout->addWidget(nBox, row, column);
            boxes->append(nBox);

            connect(nBox, SIGNAL(stateChanged(int)), this, SLOT(boxSelected(int)));
        }
    }
}

SelectGasDialog::~SelectGasDialog()
{
    delete ui;
}

void SelectGasDialog::boxSelected(int state)
{
    QCheckBox *box = (QCheckBox *) sender();\
    int i = boxes->indexOf(box);
    gasses->at(i)->selected = (state == Qt::Checked);
}
