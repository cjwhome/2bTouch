#include "maindisplay.h"
#include "ui_maindisplay.h"

MainDisplay::MainDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDisplay)
{
    ui->setupUi(this);
}

MainDisplay::~MainDisplay()
{
    delete ui;
}
