#include "errorform.h"
#include "ui_errorform.h"

ErrorForm::ErrorForm(int err, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorForm){
    errors = new QMap<int, QString>();

    errorNum = err;

    ui->setupUi(this);

    errors->insert(0, "No Errors");
    errors->insert(8, "Scrubber temp out of range.  Temp is either > 113 degrees or < 110.");
    errors->insert(128, "Pressure control out of range by > 1 mbar");
    errors->insert(4, "Cell flow out of range (< 1200 or >1600)");
    errors->insert(64, "Ozone flow out of range (< 30 or >110)");
    errors->insert(2, "Cell voltage out of range (< 0.1V or >2.4V)");
    errors->insert(32, "Ozone Generator voltage out of range (< 0.01V or >2.4V)");
    errors->insert(10, "Scrubber Temp and Cell Voltage");
    errors->insert(12, "Scrubber Temp and Cell Flow");
    errors->insert(14, "Scrubber Temp, Cell Flow, and Cell Voltage");
    errors->insert(34, "Cell Voltage, and Ozone Generator Voltage");
    errors->insert(38, "Cell Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(40, "Scrubber Temp and Cell Voltage ");
    errors->insert(36, "Cell Flow and Cell Voltage");
    errors->insert(42, "Scrubber Temp, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(44, "Scrubber Temp, Cell Flow, and Ozone Generator Voltage");
    errors->insert(46, "Scrubber Temp, Cell Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(66, "Ozone Flow and Cell Voltage");
    errors->insert(70, "Cell Flow, Ozone Flow, and Cell Voltage");
    errors->insert(72, "Scrubber Temp and Ozone Flow");
    errors->insert(74, "Scrubber Temp, Ozone Flow, and Cell Voltage");
    errors->insert(76, "Scrubber Temp, Cell Flow, and Ozone Flow");
    errors->insert(78, "Scrubber Temp, Cell Flow, Ozone Flow, and Cell Voltage ");
    errors->insert(130, "Pressure Control and Cell Voltage");
    errors->insert(132, "Pressure Control and Cell Flow");
    errors->insert(134, "Pressure Control, Cell Flow, and Cell Voltag");
    errors->insert(136, "Scrubber Temp and Pressure Control");
    errors->insert(138, "Scrubber Temp, Pressure Control, and Cell Voltage");
    errors->insert(140, "Scrubber Temp, Pressure Control, and Cell Flow");
    errors->insert(142, "Scrubber Temp, Pressure Control, Cell Flow, and Cell Voltage");
    errors->insert(160, "Pressure Control and Ozone Generator Voltage");
    errors->insert(162, "Pressure Control, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(164, "Pressure Control, Ozone Flow, and Ozone Generator Voltage");
    errors->insert(166, "Pressure Control, Ozone Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(168, "Scrubber Temp, Pressure Control, and Ozone Generator Voltage");
    errors->insert(170, "Scrubber Temp, Pressure Control, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(172, "Scrubber Temp, Pressure Control, Cell Flow, and Ozone Generator Voltage");
    errors->insert(192, "Pressure Control and Ozone Flow");
    errors->insert(194, "Pressure Control, Ozone Flow, and Cell Voltage");
    errors->insert(196, "Pressure Control, Cell Flow, and Ozone Flow");
    errors->insert(198, "Pressure Control, Cell Flow, Ozone Flow, and Cell Voltage");
    errors->insert(200, "Scrubber Temp, Pressure Control, and Ozone Flow");
    errors->insert(202, "Scrubber Temp, Pressure Control, Ozone Flow, and Cell Voltage");
    errors->insert(204, "Scrubber Temp, Pressure Control, Cell Flow, and Ozone Flow");
    errors->insert(206, "Scrubber Temp, Pressure Control, Cell Flow, Ozone Flow, and Cell Voltage");
    errors->insert(224, "Pressure Control, Ozone Flow, and Ozone Generator Voltage");
    errors->insert(226, "Pressure Control, Ozone Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(228, "Pressure Control, Cell Flow, Ozone Flow, Ozone Generator Voltage");
    errors->insert(230, "Pressure Control, Cell Flow, Ozone Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(232, "Scrubber Temp, Pressure Control, Ozone Flow, and Ozone Generator Voltage");
    errors->insert(234, "Scrubber Temp, Pressure Control, Ozone Flow, Cell Voltage, and Ozone Generator Voltage");
    errors->insert(236, "Scrubber Temp, Pressure Control, Cell Flow, Ozone Flow, and Ozone Generator Voltage");
    errors->insert(238, "Scrubber Temp, Pressure Control, Cell Flow, Ozone Flow, Cell Voltage and Ozone Generator Voltage");

    if(errors->contains(errorNum)){
        ui->label_2->setText(errors->value(errorNum));
    }else{
        ui->label_2->setText("Bad error code: " + QString::number(errorNum));
        qDebug() << "Bad error code: " << QString::number(errorNum);
    }
}

ErrorForm::~ErrorForm(){
    delete ui;
}

void ErrorForm::on_home_clicked(){
    close();
}
