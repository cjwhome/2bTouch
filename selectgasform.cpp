#include "selectgasform.h"
#include "ui_selectgasform.h"

SelectGasForm::SelectGasForm(QWidget *parent, QList<GasDataState *> * states) :
    QWidget(parent),
    ui(new Ui::SelectGasForm)
{
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    boxes = new QList<QCheckBox*>();
    gasses = states;
    ui->setupUi(this);
    numGasses = states->size();

    apply = ui->apply;
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

void SelectGasForm::update()
{
    if(numGasses == 0)
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

void SelectGasForm::boxSelected(int state)
{
    QCheckBox *box = reinterpret_cast<QCheckBox*>(sender());
    int i = boxes->indexOf(box);
    gasses->at(i)->selected = (state == Qt::Checked);
}

SelectGasForm::~SelectGasForm()
{
    delete ui;
}
