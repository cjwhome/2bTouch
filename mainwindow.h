#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "serialthread.h"
#include <QtSerialPort/QSerialPort>
#include <QDateTime>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include <QPushButton>
#include <QThread>
#include <QVector>
#include <QList>
#include <QFile>
#include "defines.h"
#include "statswidget.h"
#include "displaygraph.h"
#include "settingsview.h"
#include "xmldevicereader.h"
#include "twobtechdevice.h"
#include "deviceprofile.h"
#include "serialdataitem.h"
#include "parseddata.h"
#include "filewriter.h"
#include "controlbacklight.h"
#include "settingswidget.h"
#include "serialhandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createDevice();
    void setupSerial();
    void updateDisplay();
    QVector<double> x,y;

    void initFile();            //determine where the file will be saved (usb, locally)
    void createFileName();      //use the device name and date-time.csv (ozone-11416-1553.csv)
    void writeFile();
    void listFonts();




signals:
    void validDataReady();

public slots:
    void clearPlotData();
    void sendMsg(QString msg);
    
private slots:
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

private:
	//bool yLessThan(const double &p1, const double &p2);
    Ui::MainWindow *ui;
    SerialThread *s_serialThread;
    StatsWidget *statsWidget;
    SettingsView *settingsView;
    SettingsWidget *settingsWidget;
    QSerialPort *serial;
    DisplayGraph *displayGraph;
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

    QPushButton *usbIcon;
    QPushButton *errorIcon;
    QPushButton *warningIcon;
    QLabel *warningLabel;

    double data_point;
    int data_index;
	double start_time_seconds;
    double main_display_value;
    bool started_file;

    XmlDeviceReader* xmlDeviceReader;
    TwobTechDevice twobTechDevice;
    DeviceProfile deviceProfile;
    ParsedData parsedData;

    QList<double> avgList;
    double avg;
    QList< QList<SerialDataItem> > allParsedRecordsList;
    FileWriter fileWriter;
    SerialHandler *serialHandler;

    QSettings *settings;
    bool usbMounted;
    QTimer *usbTimer;

    QTimer *errorTimer;
};

#endif // MAINWINDOW_H
