#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QWidget>
#include <QDebug>

//#include "serialhandler.h"
#include "serialqueue.h"

namespace Ui {
class LandingPage;
}

class LandingPage : public QWidget
{
    Q_OBJECT

public:
    explicit LandingPage(QWidget *parent = nullptr);
    ~LandingPage();

    bool done = false;
    bool log = false;
    int choice = 0;

signals:
    void picked(QString*);

private slots:
    void on_save_clicked();

    void on_gasSelect_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::LandingPage *ui;

    int cIndex = 0;
};

#endif // LANDINGPAGE_H
