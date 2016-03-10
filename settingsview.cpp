#include "settingsview.h"
#include "ui_settingsview.h"

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
    QFont settingsButtonFont("Cabin", 30, QFont::ForceIntegerMetrics);
    QPushButton *adminButton = new QPushButton("Admin");
    adminButton->setFont(settingsButtonFont);
    QPushButton *fileButton = new QPushButton("File");
    QPushButton *avgButton = new QPushButton("Average");
    QPushButton *outputButton = new QPushButton("Output");
    QPushButton *relayButton = new QPushButton("Relays");

    settingsButtonsLayout->addWidget(adminButton,0,0,1,1,0);
    settingsButtonsLayout->addWidget(fileButton,0,1,1,1,0);
    settingsButtonsLayout->addWidget(avgButton,0,2,1,1,0);
    settingsButtonsLayout->addWidget(outputButton,1,0,1,1,0);
    settingsButtonsLayout->addWidget(relayButton,1,1,1,1,0);

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
}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::home()
{
    close();
}
