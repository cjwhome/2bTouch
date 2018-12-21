#include "graphsettingsform.h"
#include "ui_graphsettingsform.h"

GraphSettingsForm::GraphSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphSettingsForm)
{
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);

    m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/2btouch_settings.ini";
    loadSettings();

    connect(ui->applyButton, SIGNAL(pressed()), this, SLOT(apply()));
}

void GraphSettingsForm::apply()
{
    saveSettings();
    hide();
    emit applyGraphSettings();
}

//Loads values saved in the Qsettings class
void GraphSettingsForm::loadSettings(){
     QSettings settings("2B Technologies", "2B Touch");
     autoscalex = settings.value("xautoscale").toBool();
     autoscaley = settings.value("yautoscale").toBool();
     ui->autoscaleXcheckbox->setChecked(autoscalex);
     ui->autoscaleYcheckbox->setChecked(autoscaley);
}

//Saves settings to the QSettings class
void GraphSettingsForm::saveSettings(){
     QSettings settings("2B Technologies", "2B Touch");
     autoscalex = ui->autoscaleXcheckbox->isChecked();
     autoscaley = ui->autoscaleYcheckbox->isChecked();

     settings.setValue("xautoscale", autoscalex);
     settings.setValue("yautoscale", autoscaley);
}

GraphSettingsForm::~GraphSettingsForm(){
    delete ui;
}
