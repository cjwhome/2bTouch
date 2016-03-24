#include "adminview.h"
#include "ui_adminview.h"
#include "usertypeview.h"
#include <QSettings>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


AdminView::AdminView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminView)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);
    verticalLayout->addWidget(homeButton);

    this->setLayout(verticalLayout);
    loadSettings();
    getPassword();

}

void AdminView::getPassword(void){

    UserTypeView *userTypeView = new UserTypeView();
    userTypeView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(userTypeView, SIGNAL(outputUserString(QString)), this, SLOT(checkPassword(QString)));
    userTypeView->setWindowState(Qt::WindowActive) ;
    userTypeView->show();
}

void AdminView::checkPassword(QString password){
    //qDebug()<<"Got password:"<<password;
    if(!QString::compare(password, setPassword, Qt::CaseInsensitive)){
        qDebug()<<"Correct password";
    }else{
        qDebug()<<"Wrong password";
        close();
    }
}
void AdminView::loadSettings(void)
{
 QSettings settings("2btech", "touchscreen");

 setPassword = settings.value("password").toString();
 if(setPassword.isEmpty()){
     setPassword = "password";
     qDebug()<<"Setting password to default";
     settings.setValue("password", setPassword);
 }

}

/*void AdminView::saveSettings()
{
 QSettings settings("2btech", "touchscreen");
 //qDebug()<<"Before writing,";

 settings.setValue("xautoscale", autoscalex);
 settings.setValue("yautoscale", autoscaley);

}*/

AdminView::~AdminView()
{
    delete ui;
}
