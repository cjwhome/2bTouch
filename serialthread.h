#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QtSerialPort>
#include <QDebug>
#include <QProcess>

class SerialThread : public QThread
{
    Q_OBJECT

public:
    bool startSerial(QSerialPort *port);
    void stopSerial();

signals:
    void newDataLine(QString dline);

protected:
    void run();

private:
    QSerialPort*s_port;
    volatile bool s_stop;
    QProcess*process;
    QString prog;
    QStringList arguments;
    QString tmp;
};

#endif // SERIALTHREAD_H
