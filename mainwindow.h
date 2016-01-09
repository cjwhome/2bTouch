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
#include "defines.h"
#include "showstats.h"
#include "displaygraph.h"
#include "xmldevicereader.h"
#include "twobtechdevice.h"
#include "deviceprofile.h"
#include "parseddata.h"

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
    QVector<double> x,y;

signals:
    void validDataReady();

public slots:
    void clearPlotData();
    
private slots:
    void newDataLine(QString dLine);
    bool parseDataLine(QString dLine);
    void displayBigPlot(void);

private:
	//bool yLessThan(const double &p1, const double &p2);
    Ui::MainWindow *ui;
    SerialThread *s_serialThread;
    ShowStats *showStats;
    QSerialPort *serialPort;
    DisplayGraph *displayGraph;
    QLabel *main_output;
    QLabel *main_label;
    QLabel *main_units_label;
    QLabel *temperature_output;
    QLabel *temperature_label;
    QLabel *temperature_units_label;
    QLabel *pressure_output;
    QLabel *pressure_label;
    QLabel *pressure_units_label;
    QLabel *current_time;
    QLabel *current_time_label;
    QLabel *current_date;
    QLCDNumber *mainDisplay;
    QPushButton *graph_button;


    int data_point;
	double start_time_seconds;
	

    TwobTechDevice twobTechDevice;
    DeviceProfile deviceProfile;



};

#endif // MAINWINDOW_H
