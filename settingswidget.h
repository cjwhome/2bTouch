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
#include <QtNetwork>
#include "xmldevicereader.h"
#include "twobtechdevice.h"
#include "filewriter.h"
#include "keypad.h"
#include "keylineedit.h"

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
    QFont messageBoxFont;
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
    KeyLineEdit *calSlopeField;
    QHBoxLayout *calOffsetRow;
    QLabel *calOffsetLabel;
    KeyLineEdit *calOffsetField;
    QPushButton *calSubmit;
    //Keypad *calSlopePad;
    //Keypad *calOffPad;

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
    QHBoxLayout *rOLowRow;
    QLabel *rOLowLabel;
    KeyLineEdit *rOLowField;
    //Keypad *rOLowPad;
    QHBoxLayout *rOHighRow;
    QLabel *rOHighLabel;
    KeyLineEdit *rOHighField;
    //Keypad *rOHighPad;
    QPushButton *rOSubmitButton;
    //QHBoxLayout *rORow;
    //QPushButton *rOLowButton;
    //QPushButton *rOHighButton;
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

private slots:
    void initializeViews();
    void homePressed();

    //Landing
    void landingSubmit();
    //Calibration
    void calSubmitReleased();
    //Avergaing
    void twoSecPressed();
    void tenSecPressed();
    void oneMinPressed();
    void oneHourPressed();
    //Relay One
    //void rOLowPressed();
    //void rOHighPressed();
    void rOSubmitPressed();
    void rOHelpPressed();
    //Relay Two
    void rTOzonePresed();
    void rTDiagnosticsPressed();
    void rTHelpPressed();
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

    QWidget* widgetForLanding();
    QWidget* widgetForCal();
    QWidget* widgetForAvg();
    QWidget* widgetForRelayOne();
    QWidget* widgetForRelayTwo();
    QWidget* widgetForVoltage();
    QWidget* widgetForFiles();
    QWidget* widgetForDate();
    QWidget* widgetForNet();
    QWidget* widgetForPassChange();

    void showCal();
    void showAvg();
    void showRO();
    void showRT();
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
