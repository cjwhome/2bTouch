#include "showstats.h"
#include "ui_showstats.h"
#include <QDebug>

ShowStats::ShowStats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowStats)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QVBoxLayout *measurementDisplayLayoutArea = new QVBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();

    diagnosticA_label = new QLabel();
    diagnosticA_output = new QLabel();
    diagnosticA_units_label = new QLabel();

    diagnosticB_label = new QLabel();
    diagnosticB_output = new QLabel();
    diagnosticB_units_label = new QLabel();

    diagnosticC_label = new QLabel();
    diagnosticC_output = new QLabel();
    diagnosticC_units_label = new QLabel();

    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::VLine);

    QPushButton *home_button = new QPushButton("Home");
    home_button->setFixedSize(70,62);

    buttonLayout->addWidget(home_button);

    horizontalLayout->addLayout(buttonLayout);
    horizontalLayout->addWidget(myFrame);

    gridLayout->addWidget(diagnosticA_label,0,0,1,1,0);
    gridLayout->addWidget(diagnosticA_output,0,1,1,1,0);
    gridLayout->addWidget(diagnosticA_units_label,0,2,1,1,0);

    gridLayout->addWidget(diagnosticB_label,1,0,1,1,0);
    gridLayout->addWidget(diagnosticB_output,1,1,1,1,0);
    gridLayout->addWidget(diagnosticB_units_label,1,2,1,1,0);

    gridLayout->addWidget(diagnosticC_label,2,0,1,1,0);
    gridLayout->addWidget(diagnosticC_output,2,1,1,1,0);
    gridLayout->addWidget(diagnosticC_units_label,2,2,1,1,0);

    //measurementDisplayLayoutArea->addWidget();
    horizontalLayout->addLayout(gridLayout);

    centralWidget->setLayout(horizontalLayout);
    setCentralWidget(centralWidget);

}

ShowStats::~ShowStats()
{
    delete ui;
}


void ShowStats::setData(QList< QList<SerialDataItem> > *records, DeviceProfile *deviceProfile){
    SerialDataItem tempSerialDataItem;
    tempSerialDataItem = records->at(records->size()-1).at(deviceProfile->getDiagnosticA_position());
    diagnosticA_label->setText(deviceProfile->getDiagnosticA_name());
    diagnosticA_output->setText(QString::number(tempSerialDataItem.getDvalue()));
    diagnosticA_units_label->setText(deviceProfile->getDiagnosticA_units());

    tempSerialDataItem = records->at(records->size()-1).at(deviceProfile->getDiagnosticB_position());
    diagnosticB_label->setText(deviceProfile->getDiagnosticB_name());
    diagnosticB_output->setText(QString::number(tempSerialDataItem.getDvalue()));
    diagnosticB_units_label->setText(deviceProfile->getDiagnosticB_units());

    tempSerialDataItem = records->at(records->size()-1).at(deviceProfile->getDiagnosticC_position());
    diagnosticC_label->setText(deviceProfile->getDiagnosticC_name());
    diagnosticC_output->setText(QString::number(tempSerialDataItem.getDvalue()));
    diagnosticC_units_label->setText(deviceProfile->getDiagnosticC_units());



}

void ShowStats::calculateMaxMinMedian(QList< QList<SerialDataItem> > *records, DeviceProfile *deviceProfile){
    QList< QList<SerialDataItem> > *copied_records = records;
    for(int i=0;i<copied_records->size();i++){
        qDebug()<<"Records["<<i<<"]:";
        QList<SerialDataItem> tempList = copied_records->at(i);
        for(int a=0;a<tempList.size();a++)
            qDebug()<<"Item:"<<tempList.at(a).getDvalue();
        qDebug()<<"End";
    }



    int n;
    int i;
    for (n=0; n < copied_records->count(); n++)
    {
        for (i=n+1; i < copied_records->count(); i++)
        {
            QList<SerialDataItem> tempList = copied_records->at(n);
            double valorN=tempList.at(0).getDvalue();
            QList<SerialDataItem> tempListb = copied_records->at(i);
            double valorI=tempListb.at(0).getDvalue();
            if (valorN > valorI)
            {
                copied_records->move(i, n);
                n=0;
            }
        }
    }



    qDebug()<<"After sort:";
    for(int i=0;i<copied_records->size();i++){
        qDebug()<<"Records["<<i<<"]:";
        QList<SerialDataItem> tempList = copied_records->at(i);
        for(int a=0;a<tempList.size();a++)
            qDebug()<<"Item:"<<tempList.at(a).getDvalue();
        qDebug()<<"End";
    }
}
