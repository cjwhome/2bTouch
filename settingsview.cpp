#include "settingsview.h"
#include "ui_settingsview.h"
#include "networkview.h"
#include "adminview.h"
#include "usertypeview.h"
#include <QDebug>

SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color:white;");
    this->setStyleSheet("QPushButton { border: none;}");        //remove border on all buttons

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QGridLayout *settingsButtonsLayout = new QGridLayout();

    //settings buttons
    QFont settingsButtonFont("Cabin", 20, QFont::ForceIntegerMetrics);
    QPushButton *adminButton = new QPushButton("Admin");
    adminButton->setFont(settingsButtonFont);
    QPushButton *fileButton = new QPushButton("File");
    fileButton->setFont(settingsButtonFont);
    QPushButton *avgButton = new QPushButton("Average");
    avgButton->setFont(settingsButtonFont);
    QPushButton *outputButton = new QPushButton("Output");
    outputButton->setFont(settingsButtonFont);
    QPushButton *relayButton = new QPushButton("Relays");
    relayButton->setFont(settingsButtonFont);
    QPushButton *networkButton = new QPushButton("Network");
    networkButton->setFont(settingsButtonFont);

    settingsButtonsLayout->addWidget(adminButton,0,0,1,1,0);
    settingsButtonsLayout->addWidget(fileButton,0,1,1,1,0);
    settingsButtonsLayout->addWidget(avgButton,0,2,1,1,0);
    settingsButtonsLayout->addWidget(outputButton,1,0,1,1,0);
    settingsButtonsLayout->addWidget(relayButton,1,1,1,1,0);
    settingsButtonsLayout->addWidget(networkButton,1,2,1,1,0);

    QFrame* horizontalFrame = new QFrame();
    horizontalFrame->setFrameShape(QFrame::HLine);

    QPixmap configPixmap(":/buttons/pics/settings-icon.gif");
    QIcon configButtonIcon(configPixmap);

    QPushButton *configure_button = new QPushButton();
    configure_button->setIcon(configButtonIcon);
    configure_button->setIconSize(QSize(35,31));
    configure_button->setFixedSize(35,31);

    QPushButton *homeButton = new QPushButton();
    QPixmap homePixmap(":/buttons/pics/home-icon.gif");
    QIcon homeButtonIcon(homePixmap);
    homeButton->setIcon(homeButtonIcon);
    homeButton->setIconSize(QSize(35,31));
    homeButton->setFixedSize(35,31);

    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(configure_button);

    verticalLayout->addLayout(settingsButtonsLayout);
    verticalLayout->addWidget(horizontalFrame);
    verticalLayout->addLayout(buttonLayout);
    this->setLayout(verticalLayout);

    connect(homeButton, SIGNAL(released()), this, SLOT(home()));
    connect(networkButton, SIGNAL(released()), this, SLOT(showNetworkView()));
    connect(adminButton, SIGNAL(released()), this, SLOT(showAdminView()));
}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::home()
{
    close();
}

void SettingsView::showNetworkView(){
    NetworkView *networkView = new NetworkView();
    networkView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    networkView->show();
}

void SettingsView::showAdminView(){
    setPassword = "password";
    UserTypeView *userTypeView = new UserTypeView("Enter Password");
    connect(userTypeView, SIGNAL(outputUserString(QString)), this, SLOT(checkPassword(QString)));
    userTypeView->show();
}

void SettingsView::checkPassword(QString password){
    qDebug()<<"Got password:"<<password;
    if(!QString::compare(password, setPassword, Qt::CaseInsensitive)){
        qDebug()<<"Correct password";
        AdminView *adminView = new AdminView();
        adminView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        adminView->show();
    }else{
        qDebug()<<"Wrong password";
        close();
    }

}
