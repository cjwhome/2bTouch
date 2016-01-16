#include "showstats.h"
#include "ui_showstats.h"
#include <QDebug>

#define SECONDS_IN_ONE_MINUTE 60
#define SECONDS_IN_ONE_HOUR 3600
#define SECONDS_IN_EIGHT_HOURS 28800

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

    non_avg_main_label = new QLabel();
    hour_avg_main_label = new QLabel();
    eight_hour_avg_main_label = new QLabel();

    non_avg_main_output = new QLabel();
    hour_avg_main_output = new QLabel();
    eight_hour_avg_main_output = new QLabel();

    non_avg_main_units_label = new QLabel();
    hour_avg_main_units_label = new QLabel();
    eight_hour_avg_main_units_label = new QLabel();

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

    gridLayout->addWidget(non_avg_main_label,0,0,1,1,0);
    gridLayout->addWidget(non_avg_main_output,0,1,1,1,0);
    gridLayout->addWidget(non_avg_main_units_label,0,2,1,1,0);

    gridLayout->addWidget(hour_avg_main_label,1,0,1,1,0);
    gridLayout->addWidget(hour_avg_main_output,1,1,1,1,0);
    gridLayout->addWidget(hour_avg_main_units_label,1,2,1,1,0);

    gridLayout->addWidget(eight_hour_avg_main_label,2,0,1,1,0);
    gridLayout->addWidget(eight_hour_avg_main_output,2,1,1,1,0);
    gridLayout->addWidget(eight_hour_avg_main_units_label,2,2,1,1,0);

    gridLayout->addWidget(diagnosticA_label,3,0,1,1,0);
    gridLayout->addWidget(diagnosticA_output,3,1,1,1,0);
    gridLayout->addWidget(diagnosticA_units_label,3,2,1,1,0);

    gridLayout->addWidget(diagnosticB_label,4,0,1,1,0);
    gridLayout->addWidget(diagnosticB_output,4,1,1,1,0);
    gridLayout->addWidget(diagnosticB_units_label,4,2,1,1,0);

    gridLayout->addWidget(diagnosticC_label,5,0,1,1,0);
    gridLayout->addWidget(diagnosticC_output,5,1,1,1,0);
    gridLayout->addWidget(diagnosticC_units_label,5,2,1,1,0);

    connect(home_button, SIGNAL(clicked()), this, SLOT(home()));

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

    tempSerialDataItem = records->at(records->size()-1).at(deviceProfile->getMain_display_position());
    non_avg_main_label->setText(deviceProfile->getMain_display_name());
    //non_avg_main_label->setText("O<sub>3</sub>");
    non_avg_main_output->setText(QString::number(tempSerialDataItem.getDvalue()));
    non_avg_main_units_label->setText(deviceProfile->getMain_display_units());

    //determine 1 hour average and 8 hour average

    //find 1 hour average
    //first, find the time 1 hour from timestamp
    tempSerialDataItem = records->at(records->size()-1).at(deviceProfile->getDate_position());
    QDateTime currentTimeStamp = tempSerialDataItem.getDateTime();

    int counter = records->size()-1;

    bool position_found = false;
    while(counter && !position_found){
        counter--;
        tempSerialDataItem = records->at(counter).at(deviceProfile->getDate_position());
        QDateTime tempTimeStamp = tempSerialDataItem.getDateTime();
        //qDebug()<<"Time:"<<tempTimeStamp.toString();
        double diff = tempTimeStamp.secsTo(currentTimeStamp);
        //qDebug()<<"Diff:"<<diff;
        if(diff>=SECONDS_IN_ONE_HOUR)
            position_found = true;
    }

    //using the found position for the 1 hour mark, sum up all readings in between and average
    double sum = 0;
    for(int i=counter;i<records->size()-1;i++){
        tempSerialDataItem = records->at(i).at(deviceProfile->getMain_display_position());
        sum += tempSerialDataItem.getDvalue();
        //qDebug()<<"Sum:"<<sum;
    }
    double hr_average = sum/((records->size()-1)-counter);



    hour_avg_main_label->setText("HrAvg "+deviceProfile->getMain_display_name());
    hour_avg_main_output->setText(QString::number(hr_average));
    hour_avg_main_units_label->setText(deviceProfile->getMain_display_units());


    counter = records->size()-1;
    position_found = false;
    while(counter && !position_found){
        counter--;
        tempSerialDataItem = records->at(counter).at(deviceProfile->getDate_position());
        QDateTime tempTimeStamp = tempSerialDataItem.getDateTime();
        //qDebug()<<"Time:"<<tempTimeStamp.toString();
        double diff = tempTimeStamp.secsTo(currentTimeStamp);
        //qDebug()<<"Diff:"<<diff;
        if(diff>=SECONDS_IN_EIGHT_HOURS)
            position_found = true;
    }

    double eight_hr_average = sum/((records->size()-1)-counter);



    eight_hour_avg_main_label->setText("8HrAvg "+deviceProfile->getMain_display_name());
    eight_hour_avg_main_output->setText(QString::number(eight_hr_average));
    //eight_hour_avg_main_output->setStyleSheet("QLabel { background-color : red; color : blue; }");
    if(eight_hr_average>100)
        eight_hour_avg_main_output->setStyleSheet("QLabel { color : red; }");       //just testing, in the future, all main display colors are set from user setting
    //eight_hour_avg_main_output->setText("<font color='red'>Some text</font>");
    eight_hour_avg_main_units_label->setText(deviceProfile->getMain_display_units());

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

void ShowStats::calculateMaxMinMedian(QList< QList<SerialDataItem> > &records, int element_to_sort){
    QList< QList<SerialDataItem> > copied_records = records;
    /*for(int i=0;i<copied_records->size();i++){
        qDebug()<<"Records["<<i<<"]:";
        QList<SerialDataItem> tempList = copied_records->at(i);
        for(int a=0;a<tempList.size();a++)
            qDebug()<<"Item:"<<tempList.at(a).getDvalue();
        qDebug()<<"End";
    }*/



    int n;
    int i;
    for (n=0; n < copied_records.count(); n++)
    {
        for (i=n+1; i < copied_records.count(); i++)
        {
            QList<SerialDataItem> tempList = copied_records.at(n);
            double valorN=tempList.at(element_to_sort).getDvalue();
            QList<SerialDataItem> tempListb = copied_records.at(i);
            double valorI=tempListb.at(element_to_sort).getDvalue();
            if (valorN > valorI)
            {
                copied_records.move(i, n);
                n=0;
            }
        }
    }



   /* qDebug()<<"After sort:";
    for(int i=0;i<copied_records->size();i++){
        qDebug()<<"Records["<<i<<"]:";
        QList<SerialDataItem> tempList = copied_records->at(i);
        for(int a=0;a<tempList.size();a++)
            qDebug()<<"Item:"<<tempList.at(a).getDvalue();
        qDebug()<<"End";
    }*/
}

void ShowStats::home()
{
    this->close();
}

