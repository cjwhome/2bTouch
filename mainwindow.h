#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialthread.h"
#include <QSerialPort>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include "defines.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupSerial();
    
private slots:
    void newDataLine(QString dLine);
    void parseDataLine(QString dLine);

private:
    Ui::MainWindow *ui;
    SerialThread *s_serialThread;
    QSerialPort *serialPort;
    QLabel *ozone_output;
    QLabel *ozone_label;
    QLabel *ozone_units_label;
    QLabel *temperature_output;
    QLabel *temperature_label;
    QLabel *temperature_units_label;
    QLabel *pressure_output;
    QLabel *pressure_label;
    QLabel *pressure_units_label;
    QLabel *current_time;
    QLabel *current_time_label;

    double current_ozone;
    double current_temp;
    double current_press;
    double current_pdv;


};

#endif // MAINWINDOW_H
