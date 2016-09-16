#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QWidget>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>
#include <QThread>
#include <QProcess>
#include <QDebug>

int screen_height;
int screen_width;

class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
};


int main(int argc, char *argv[])
{
    qDebug()<<"1";
    QApplication a(argc, argv);
    MainWindow w;

	QRect rec = QApplication::desktop()->screenGeometry();
	screen_height = rec.height();
	screen_width = rec.width();
    //if(screen_width < MINIMUM_BIG_SCREEN_WIDTH){
       // w.setMinimumSize(screen_width,screen_height);						//only usefull for raspberrypi but make this different for pc version
       // w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);			//hides the title bar
    //}else{
        //w.setMinimumSize(screen_width-300, screen_height-250);
   // }
    QSplashScreen *splash = new QSplashScreen();
    QPixmap pix(":/splash/pics/2B_Screen_v1.jpg");

    QString versionString;		//needed because too close to edge of screen
    
    versionString.append(APP_NAME);
    //versionString.append("\nVersion ");
    //versionString.append(APP_VERSION);

    splash->setPixmap(pix);
    splash->show();
    Qt::Alignment topleft = Qt::AlignLeft | Qt::AlignTop;
    //Qt::Alignment bottomright = Qt::AlignRight | Qt::AlignBottom;
    //splash->showMessage(versionString, bottomright, Qt::black);
    splash->showMessage(versionString, topleft, Qt::black);
    //splash->showMessage(ipString, topleft, Qt::black);

    I::sleep(3);
    QTimer::singleShot(4500,splash,SLOT(close()));

   
	
    w.show();
    
    return a.exec();
}
