#include "filesform.h"
#include "ui_filesform.h"

FilesForm::FilesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesForm)
{
    ui->setupUi(this);

    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
}

FilesForm::~FilesForm()
{
    delete ui;
}
