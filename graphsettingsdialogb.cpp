#include <QSettings>

#include "graphsettingsdialogb.h"
#include "ui_graphsettingsdialogb.h"

GraphSettingsDialogB::GraphSettingsDialogB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphSettingsDialogB)
{
    ui->setupUi(this);

    m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/2btouch_settings.ini";
    loadSettings();

    connect(ui->applyButton, SIGNAL(pressed()), this, SLOT(apply()));
}

GraphSettingsDialogB::~GraphSettingsDialogB()
{
    delete ui;
}

void GraphSettingsDialogB::apply()
{
    saveSettings();
    hide();
    emit applyGraphSettings();
}

void GraphSettingsDialogB::loadSettings()
{
     QSettings settings("2B Technologies", "2B Touch");

     autoscalex = settings.value("xautoscale").toBool();
     autoscaley = settings.value("yautoscale").toBool();

     if(autoscalex) {
         ui->autoscaleXcheckbox->setChecked(true);
     } else {
         ui->autoscaleXcheckbox->setChecked(false);
     }

     if(autoscaley) {
         ui->autoscaleYcheckbox->setChecked(true);
     } else {
         ui->autoscaleYcheckbox->setChecked(false);
     }
}

void GraphSettingsDialogB::saveSettings()
{
     QSettings settings("2B Technologies", "2B Touch");
     if(ui->autoscaleXcheckbox->isChecked()) {
         autoscalex = true;
     } else {
         autoscalex = false;
     }
     if(ui->autoscaleYcheckbox->isChecked()) {
         autoscaley = true;
     } else {
         autoscaley = false;
     }

     settings.setValue("xautoscale", autoscalex);
     settings.setValue("yautoscale", autoscaley);

}

