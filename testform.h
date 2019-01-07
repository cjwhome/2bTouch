#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>

#include "serialhandler.h"

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestForm *ui;

    int count = 0;
};

#endif // TESTFORM_H
