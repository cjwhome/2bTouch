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

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

private:
    Ui::SettingsWidget *ui;

    //Universal Layout
    QPushButton *homeButton;
    QPushButton *leftArrow;
    QPushButton *rightArrow;
    QWidget *widgets[5];
    QVBoxLayout *mainLayout;
    int currentIndex;

    //Landing Page
    QWidget *landingWidget;
    QVBoxLayout *landingVLayout;
    QHBoxLayout *landingPassRow;
    QLabel *landingPassTitle;
    QLabel *landingPassPrompt;
    QLineEdit *landingPassField;
    QPushButton *landingPassSubmit;
    QIcon *landingSettingsIcon;

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
    QLabel *cpTitle;
    QLabel *cpPassLabel;
    QLineEdit *cpPassText;
    QLabel *cpConfirmLabel;
    QLineEdit *cpConfText;
    QPushButton *cpSaveButton;

private slots:
    void initializeViews();
    void homePressed();

    void landingSubmit();
    void calSubmitReleased();
    void changeAvg(int time);
    void rOLowPressed();
    void rOHighPressed();
    void rTOzonePresed();
    void rTDiagnosticsPressed();

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
};

#endif // SETTINGSWIDGET_H
