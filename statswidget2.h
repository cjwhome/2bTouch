#ifndef STATSWIDGET2_H
#define STATSWIDGET2_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QGridLayout>
#include <QList>
#include <QtMath>

#include "gasdatastate.h"

namespace Ui {
class StatsWidget2;
}

class StatsWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit StatsWidget2(QWidget *parent = nullptr, QList<GasDataState *> * d = 0);
    ~StatsWidget2();
    void updateDisplay();


public slots:
    void iHateCpp();

private:
    Ui::StatsWidget2 *ui;

    int currentGasIndex = 0;
    int numberOfGases = 0;

    QString goodStylesheet;
    QString badStylesheet;

    QSize buttonSize;
    QSize widgetSize;
    QRect widgetGeo;

    QHBoxLayout *mainLayout;
    QPushButton *homeButton;
    QPushButton *left;
    QPushButton *right;
    QWidget *placeHolder; // This is used to create space between the left and right buttons

    QGridLayout *gasLayout;
    QLabel *gasName;
    QLabel *hourAverage;
    QLabel *hourValue;
    QLabel *eightAverage;
    QLabel *eightValue;

    QList<GasDataState *> * data;



private slots:
    void leftPressed();
    void rightPressed();
    void homePressed();
};

#endif // STATSWIDGET2_H
