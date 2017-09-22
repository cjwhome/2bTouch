#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QCheckBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtNetwork>
#include "xmldevicereader.h"
#include "twobtechdevice.h"
#include "filewriter.h"
#include "keypad.h"
#include "keylineedit.h"

#define MAX_RELAY_VALUE 1000
#define MIN_RELAY_VALUE 0
#define MIN_SLOPE_VALUE 50
#define MAX_SLOPE_VALUE 150
#define MIN_OFFSET_VALUE -30
#define MAX_OFFSET_VALUE 30

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

    void invalidate();

signals:
    void sendMsg(QString msg);
    void sendAMsg(QString *msg);


private:
    Ui::SettingsWidget *ui;

    //Universal Layout
    QPushButton *homeButton;
    QVBoxLayout *mainLayout;
    QFont titleFont;
    QFont labelFont;
    QSize buttonSize;
    QString regButtonStyle;
    QString selButtonStyle;
    QString univStyle;

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
    QLabel *calSlopeField;
    QHBoxLayout *calOffsetRow;
    QLabel *calOffsetLabel;
    QLabel *calOffsetField;
    QPushButton *calSubmit;

    QPushButton *calIncreaseButton;
    QPushButton *calDecreaseButton;
    float slopeValue;
    int offsetValue;
    QCheckBox *slopeCheckBox;
    QCheckBox *offsetCheckBox;


    //Relay One
    QWidget *rOWidget;
    QVBoxLayout *rOVLayout;
    QLabel *relayOneTitle;
    QHBoxLayout *rOLowRow;
    QLabel *rOLowLabel;
    QLabel *rOLowField;
    //Keypad *rOLowPad;
    QHBoxLayout *rOHighRow;
    QLabel *rOHighLabel;
    QLabel *rOHighField;
    //Keypad *rOHighPad;
    QPushButton *rOSubmitButton;
    //QHBoxLayout *rORow;
    //QPushButton *rOLowButton;
    //QPushButton *rOHighButton;
    QPushButton *rOHelpButton;
    QMessageBox::StandardButton rOHelpBox;
    QPushButton *relayIncreaseButton;
    QPushButton *relayDecreaseButton;
    int relayOneLowValue;
    int relayOneHighValue;
    QCheckBox *rOLowCheckBox;
    QCheckBox *rOHighCheckBox;
    //Relay Two
   /* QWidget *rTWidget;
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
    QMessageBox *rTHelp;*/

    //Voltage
    QWidget *voltWidget;
    QVBoxLayout *voltVLayout;
    QLabel *voltTitle;
    QLabel *voltVoltLabel;
    QHBoxLayout *voltPPBRow;
    KeyLineEdit *voltPPBField;
    QLabel *voltPPBLabel;
    QPushButton *voltSubmitButton;
    QIcon *voltIcon;
    //Keypad *voltPad;

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

    //Date and Time
    QWidget *dateWidget;
    QVBoxLayout *dateVLayout;
    QLabel *dateTitle;
    QHBoxLayout *dateDateRow;
    QLabel *dateDateLabel;
    KeyLineEdit *dateDateField;
    //Keypad *dateDatePad;
    QHBoxLayout *dateTimeRow;
    QLabel *dateTimeLabel;
    KeyLineEdit *dateTimeField;
    //Keypad *dateTimePad;
    QPushButton *dateSubmitButton;

    //Network - Display IP
    QWidget *netWidget;
    QVBoxLayout *netVLayout;
    QLabel *netTitle;
    QLabel *netSSIDLabel;
    QLabel *netIPLabel;
    QPushButton *netDisButton;

    //Network - Connect
    QWidget *connWidget;
    QVBoxLayout *connVLayout;
    QLabel *connTitle;
    QTableWidget *connTable;
    QHBoxLayout *connPassRow;
    QLabel *connPassTitle;
    KeyLineEdit *connPassField;
    //Keypad *connPassPad;
    QPushButton *connSubmitButton;

    //Change Password
    QWidget *cpWidget;
    QVBoxLayout *cpVLayout;
    QLabel *cpTitle;
    QHBoxLayout *cpPassRow;
    QLabel *cpPassLabel;
    KeyLineEdit *cpPassText;
    QHBoxLayout *cpConfRow;
    QLabel *cpConfirmLabel;
    KeyLineEdit *cpConfText;
    QPushButton *cpSaveButton;
    //Keypad *cpPassPad;
    //Keypad *cpConfPad;

    QSettings *settings;

    TwobTechDevice device;
    bool firstTimeViewed;

private slots:
    void initializeViews();
    void homePressed();

    //Landing
    void landingSubmit();
    //Calibration
    void calSubmitReleased();
    void on_calIncreasePressed();
    void on_calDecreasePressed();
    void on_slopeCheckBoxPressed();
    void on_offsetCheckBoxPressed();

    void rOSubmitPressed();
    void rOHelpPressed();
    void on_relayIncreasePressed();
    void on_relayDecreasePressed();
    void on_relayLowCheckBoxPressed();
    void on_relayHighCheckBoxPressed();
    //Relay Two
   /* void rTOzonePresed();
    void rTDiagnosticsPressed();
    void rTHelpPressed();*/
    //Volt
    void voltSubmitPressed();
    //Files
    void copySelectedPressed();
    void deleteAllPressed();
    void deleteSelectedPressed();
    //Date and Time
    void dateSubmitPressed();
    //Network
    void netDisButtonPressed();
    void connSubmitPressed();
    //Change Password
    void changePassPressed();

    void widgetForLanding();
    QWidget* widgetForCal();
    //QWidget* widgetForAvg();
    QWidget* widgetForRelayOne();
    //QWidget* widgetForRelayTwo();
    QWidget* widgetForVoltage();
    QWidget* widgetForFiles();
    QWidget* widgetForDate();
    QWidget* widgetForNet();
    QWidget* widgetForPassChange();

    void showCal();
    //void showAvg();
    void showRO();
    //void showRT();
    void showVolt();
    void showFiles();
    void showDate();
    void showNet();
    void showPassChange();

    void clearView();

    void sendMessage(QString msg);

    QString checkNetwork();
    QList<QString> availableNetworks();

public slots:
    void copyAllPressed();
};

#endif // SETTINGSWIDGET_H
