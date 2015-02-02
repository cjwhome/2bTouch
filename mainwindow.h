#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialthread.h"
#include <QSerialPort>
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
    SerialThread *s_serialThread;
    QSerialPort *serialPort;
};

#endif // MAINWINDOW_H
