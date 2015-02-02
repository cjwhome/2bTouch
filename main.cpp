#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QWidget>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>
#include <QThread>
#include <QWSServer>
#include <QProcess>


class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen *splash = new QSplashScreen();
    QPixmap pix(":/splash/pics/2B_Tech_Logo.jpg");

    QString versionString;		//needed because too close to edge of screen
    //versionString.append(QString(tmp));
    versionString.append(APP_NAME);
    versionString.append("\nVersion ");
    versionString.append(APP_VERSION);

    //QString ipString;
    //ipString.append("\nIP:");
    //ipString.append(QString(tmp));
    //versionString.append("\n\n");


    splash->setPixmap(pix);
    splash->show();
    Qt::Alignment topleft = Qt::AlignLeft | Qt::AlignTop;
    Qt::Alignment bottomright = Qt::AlignRight | Qt::AlignBottom;
    //splash->showMessage(versionString, bottomright, Qt::black);
    splash->showMessage(versionString, bottomright, Qt::black);
    //splash->showMessage(ipString, topleft, Qt::black);

    I::sleep(3);
    QTimer::singleShot(4500,splash,SLOT(close()));

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);			//hides the title bar

    w.show();
    
    return a.exec();
}
