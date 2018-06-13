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
#include "defines.h"

#define MAX_RELAY_VALUE 1000
#define MIN_RELAY_VALUE 0
#define MIN_SLOPE_VALUE 50
#define MAX_SLOPE_VALUE 150
#define MIN_OFFSET_VALUE -30
#define MAX_OFFSET_VALUE 30
#define MAX_VOLT_PPB_VALUE 1000
#define MIN_VOLT_PPB_VALUE 5

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
    QFont labelFontSmall;
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


    //Voltage
    QWidget *voltWidget;
    QVBoxLayout *voltVLayout;
    QLabel *voltTitle;
    QLabel *voltVoltLabel;
    QHBoxLayout *voltPPBRow;
    QLabel *voltPPBField;
    QLabel *voltPPBLabel;
    QPushButton *voltSubmitButton;
    QPushButton *increaseVoltButton;
    QPushButton *decreaseVoltButton;
    QIcon *voltIcon;
    int voltPPBValue;

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
    QPushButton *dayTenButton;
    QPushButton *dayButton;
    QPushButton *monthButton;
    QPushButton *monthTenButton;
    QPushButton *yearButton;
    QPushButton *yearTenButton;
    QPushButton *hourTenButton;
    QPushButton *hourButton;
    QPushButton *minButton;
    QPushButton *minTenButton;
    QPushButton *secButton;
    QPushButton *secTenButton;

    QPushButton *increaseDTButton;
    QPushButton *decreaseDTButton;
    int dayTenValue;
    int dayValue;
    int monthTenValue;
    int monthValue;
    int yearTenValue;
    int yearValue;

    int hourTenValue;
    int hourValue;
    int minTenValue;
    int minValue;
    int secTenValue;
    int secValue;



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

    //About - display info about the software
    QWidget *aboutWidget;
    QVBoxLayout *aboutVLayout;
    QLabel *aboutTitle;
    QLabel *aboutNameLabel;
    QLabel *aboutVersionLabel;
    QLabel *aboutCopyrightLabel;
    QHBoxLayout *aboutVersionRow;
    QHBoxLayout *aboutCopyrightRow;

    //Modbus
    QWidget *modbusWidget;
    QVBoxLayout *modbusVLayout;
    QLabel *modbusTitle;
    QHBoxLayout *modbusFirstRow;
    KeyLineEdit *modbusCustomEntry;
    KeyLineEdit *modbusCustomAddress;
    QPushButton *modbusSaveButton;


    QSettings *settings;
    QString msgBoxStyle;

    TwobTechDevice device;
    bool firstTimeViewed;

private slots:
    void initializeViews();
    void homePressed();



    //Calibration
    void calSubmitReleased();
    void on_calIncreasePressed();
    void on_calDecreasePressed();
    void on_slopeCheckBoxPressed();
    void on_offsetCheckBoxPressed();

    //Relay
    void rOSubmitPressed();
    void rOHelpPressed();
    void on_relayIncreasePressed();
    void on_relayDecreasePressed();
    void on_relayLowCheckBoxPressed();
    void on_relayHighCheckBoxPressed();


    //Volt
    void voltSubmitPressed();
    void on_increaseVoltButton();
    void on_decreaseVoltButton();

    //Files
    void copySelectedPressed();
    void deleteAllPressed();
    void deleteSelectedPressed();

    //Date and Time
    void dateSubmitPressed();
    void on_increaseDTButtonPressed();
    void on_decreaseDTButtonPressed();

    //Network
    void netDisButtonPressed();
    void connSubmitPressed();

    //Modbus
    void modbusSavePressed();



    QWidget* widgetForCal();
    //QWidget* widgetForAvg();
    QWidget* widgetForRelayOne();
    //QWidget* widgetForRelayTwo();
    QWidget* widgetForVoltage();
    QWidget* widgetForFiles();
    QWidget* widgetForDate();
    QWidget* widgetForNet();
    QWidget* widgetForAbout();
    QWidget* widgetForModbus();


    void showCal();
    //void showAvg();
    void showRO();
    //void showRT();
    void showVolt();
    void showFiles();
    void showDate();
    void showNet();
    void showAbout();
    void showModbus();
    void widgetForLanding();

    void clearView();

    void sendMessage(QString msg);

    QString checkNetwork();
    QList<QString> availableNetworks();

public slots:
    void copyAllPressed();
};

#endif // SETTINGSWIDGET_H
