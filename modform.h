#ifndef MODFORM_H
#define MODFORM_H

#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "keylineedit.h"
#include "uimanager.h"

namespace Ui {
class ModForm;
}

class ModForm : public QWidget
{
    Q_OBJECT

public:
    explicit ModForm(QWidget *parent = nullptr);
    ~ModForm();

private slots:
    void on_home_clicked();

    void on_mNext_clicked();

    void on_mPrev_clicked();

private:
    Ui::ModForm *ui = nullptr;


};

#endif // MODFORM_H
