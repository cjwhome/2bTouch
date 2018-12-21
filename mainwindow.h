#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include <QStringListModel>
#include <QList>
#include <QListWidgetItem>
#include <QDebug>

#include "richtextdelegate.h"
#include "calform.h"
#include "analogform.h"
#include "datetimeform.h"
#include "modform.h"
#include "averageform.h"
#include "uimanager.h"
#include "grabdata.h"
#include "modbusform.h"
#include "networkform.h"
#include "networkconnectedform.h"
#include "serialthread.h"
#include "statsaverageform.h"
#include "displaygraph.h"
#include "clickablelabel.h" //Not sure if using still
#include "twobtechdevice.h"
#include "xmldevicereader.h"
#include "deviceprofile.h"
#include "parseddata.h"
#include "filewriter.h"
#include "serialhandler.h"
#include "statsmenuform.h"

#include "testform.h"

#define MAXIMUM_PARSED_DATA_RECORDS 25

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool syncedWithBoard = false;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createDevice();
    void setupSerial();
    QVector<double> x,y,test;

    void initFile();            //determine where the file will be saved (usb, locally)
    void createFileName();      //use the device name and date-time.csv (ozone-11416-1553.csv)
    void writeFile();
    void listFonts();
    void i2c_test(void);

signals:
    void validDataReady();

public slots:
    void newDataLine(QString dLine);
    bool parseDataLine(QString dLine);
    void displayBigPlot(void);
    void displayStats(void);
    void displaySettings(void);
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void closeSerialPort();
    void updateAverage(double value);

    void usbTimerTick();
    void errorTimerTick();

    QString getCpuUsage();
    QString getFreeSpace();

    void updateMainDisplay(const QModelIndex);
    void showSettings();

    void powerDown();

signals:
    void receivedData(void);

private:
    int mainLabelContent = 0;
    Ui::MainWindow *ui;
    SerialThread *s_serialThread;
    QSerialPort *serial;
    DisplayGraph *displayGraph;

    ClickableLabel *ba;
    ClickableLabel *bb;
    ClickableLabel *bc;
    QLabel *label;
    QGridLayout *layout;

    QGroupBox *gBox;
    QLabel *mainL;
    QLabel *NO2;
    QLabel *NO2Value;
    QLabel *NO2Units;
    QLabel *NO;
    QLabel *NOValue;
    QLabel *NOUnits;
    QLabel *NOx;
    QLabel *NOxValue;
    QLabel *NOxUnits;

    QLabel *main_output;
    QLabel *main_label;
    QLabel *main_units_label;
    QLabel *main_measurement_display;
    QLabel *current_time;
    QLabel *current_time_label;
    QLabel *current_date;
    QLCDNumber *main_lcd_display;
    QPushButton *graph_button;
    QFile currentFile;
    QString tempDLine;

    QSize buttonSize;

    QHBoxLayout *statusRow;
    QPushButton *usbIcon;
    QPushButton *errorIcon;
    QPushButton *cpuIcon;
    QPushButton *diskSpaceIcon;
    QPushButton *warningIcon;
    QLabel *warningLabel;

    double data_point;
    int data_index;
    double start_time_seconds;
    double main_display_value;
    bool started_file;

    XmlDeviceReader* xmlDeviceReader;
    TwobTechDevice twobTechDevice;
    QList<TwobTechDevice> *devices;
    DeviceProfile deviceProfile;

    QList<double> avgList;
    double avg;
    QList<QList<SerialDataItem>> allParsedRecordsList;
    FileWriter fileWriter;
    SerialHandler *serialHandler;

    ModbusServer *modbus;

    QSettings *settings;
    bool usbMounted;
    QTimer *usbTimer;

    QTimer *errorTimer;

    QString msgBoxStyle;
    void play_jingle(void);

    QList<GasDataState *> *gases;

    QListView * mListView;
    QLabel * nmLabel;
    GrabData * grabData;

    StatsAverageForm * sAverage = nullptr;

    void createSettingViews();

    QStringListModel * model;

    int currentIndex = 0;
    void updateList();
};

#endif // MAINWINDOW_H
