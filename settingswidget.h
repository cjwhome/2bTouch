#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "xmldevicereader.h"
#include "twobtechdevice.h"
#include "filewriter.h"
#include "keypad.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

signals:
    void sendMsg(QString msg);

private:
    Ui::SettingsWidget *ui;

    //Universal Layout
    QPushButton *homeButton;
    QVBoxLayout *mainLayout;
    QFont titleFont;
    QFont labelFont;


    //Landing Page
    QWidget *landingWidget;
    QVBoxLayout *landingVLayout;
    QHBoxLayout *landingPassRow;
    QLabel *landingPassTitle;
    QLabel *landingPassPrompt;
    QLineEdit *landingPassField;
    QPushButton *landingPassSubmit;
    QIcon *landingSettingsIcon;
    Keypad *landingPad;

    //Calibration
    QWidget *calWidget;
    QVBoxLayout *calVLayout;
    QLabel *calTitle;
    QHBoxLayout *calSlopeRow;
    QLabel *calSlopeLabel;
    QLineEdit *calSlopeField;
    QHBoxLayout *calOffsetRow;
    QLabel *calOffsetLabel;
    QLineEdit *calOffsetField;
    QPushButton *calSubmit;
    Keypad *calSlopePad;
    Keypad *calOffPad;

    //Averaging
    QWidget *avgWidget;
    QVBoxLayout *avgVLayout;
    QLabel *avgTitle;
    QHBoxLayout *avgRowOne;
    QPushButton *avgTwoSecButton;
    QPushButton *avgTenSecButton;
    QHBoxLayout *avgRowTwo;
    QPushButton *avgOneMinButton;
    QPushButton *avgOneHourButton;
    QIcon *avgIcon;

    //Relay One
    QWidget *rOWidget;
    QVBoxLayout *rOVLayout;
    QLabel *relayOneTitle;
    QHBoxLayout *rORow;
    QPushButton *rOLowButton;
    QPushButton *rOHighButton;
    QPushButton *rOHelpButton;
    QMessageBox::StandardButton rOHelpBox;

    //Relay Two
    QWidget *rTWidget;
    QVBoxLayout *rTVLayout;
    QLabel *rTTitle;
    QPushButton *rTHelpButton;
    QHBoxLayout *rTModeHLayout;
    QLabel *rTModeLabel;
    QPushButton *rTOzoneButton;
    QLabel *rTDiagnosticsLabel;
    QPushButton *rTDiagnosticsButton;
    QLabel *rTCompLabel;
    QPushButton *rTDiagnosticButtons[3][2];
    QMessageBox *rTHelp;

    //Voltage
    QWidget *voltWidget;
    QVBoxLayout *voltVLayout;
    QLabel *voltTitle;
    QLabel *voltVoltLabel;
    QIcon *voltIcon;

    //Files
    QWidget *filesWidget;
    QVBoxLayout *filesVLayout;
    QLabel *filesTitle;
    QHBoxLayout *filesCopyActionsMenu;
    QPushButton *filesCopyAllButton;
    QPushButton *filesCopySelectedButton;
    QHBoxLayout *filesDeleteActionsMenu;
    QPushButton *filesDeleteAllButton;
    QPushButton *filesDeleteSelectedButton;
    QTableWidget *filesTable;

    //Change Password
    QWidget *cpWidget;
    QVBoxLayout *cpVLayout;
    QLabel *cpTitle;
    QHBoxLayout *cpPassRow;
    QLabel *cpPassLabel;
    QLineEdit *cpPassText;
    QHBoxLayout *cpConfRow;
    QLabel *cpConfirmLabel;
    QLineEdit *cpConfText;
    QPushButton *cpSaveButton;
    Keypad *cpPassPad;
    Keypad *cpConfPad;

    QSettings *settings;

private slots:
    void initializeViews();
    void homePressed();

    //Landing
    void landingSubmit();
    //Calibration
    void calSubmitReleased();
    //Avergaing
    void changeAvg(int time);
    //Relay One
    void rOLowPressed();
    void rOHighPressed();
    void rOHelpPressed();
    //Relay Two
    void rTOzonePresed();
    void rTDiagnosticsPressed();
    void rTHelpPressed();
    //Files
    void copyAllPressed();
    void copySelectedPressed();
    void deleteAllPressed();
    void deleteSelectedPressed();
    //Change Password
    void changePassPressed();

    QWidget* widgetForLanding();
    QWidget* widgetForCal();
    QWidget* widgetForAvg();
    QWidget* widgetForRelayOne();
    QWidget* widgetForRelayTwo();
    QWidget* widgetForVoltage();
    QWidget* widgetForFiles();
    QWidget* widgetForPassChange();

    void showCal();
    void showAvg();
    void showRO();
    void showRT();
    void showVolt();
    void showFiles();
    void showPassChange();

    void clearView();

    void sendMessage(QString msg);
};

#endif // SETTINGSWIDGET_H
