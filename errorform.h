#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QWidget>
#include <QDebug>
#include <QMap>

namespace Ui {
class ErrorForm;
}

class ErrorForm : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorForm(int err = 0, QWidget *parent = nullptr);
    ~ErrorForm();

private slots:
    void on_home_clicked();

private:
    Ui::ErrorForm *ui;

    int errorNum = 0;//default to 0 which is no errors
    QMap<int, QString> * errors;// = new QMap<int, QString>();
};

#endif // ERRORFORM_H
