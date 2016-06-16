#ifndef DISPLAYGRAPH_H
#define DISPLAYGRAPH_H

#include <QWidget>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QVector>
#include <QThread>
#include "qcustomplot.h"


namespace Ui {
class DisplayGraph;
}

class DisplayGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayGraph(QWidget *parent = 0);
    ~DisplayGraph();
    void setData(QVector<double> a, QVector<double> b);

    void drawPlot();


    void setYaxisLabel(QString label);
signals:
    void userClearedPlot(void);

public slots:
    void redrawPlot();
    void clear();

private slots:
    void goback();
    void mousePress();
    void mouseWheel();

    void zoomIn();
    void zoomOut();

    void fixScale();

    //void timerFired();
    //void showMenu();
    //void hideMenu();
private:
    Ui::DisplayGraph *ui;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *zoomHLayout;
    QWidget *menuWidget;
    QHBoxLayout *buttonLayout;

    //QTimer *timer;
    bool menuIsShowing;

    QCustomPlot *customPlot;
    QVector<double> x,y;

};

#endif // DISPLAYGRAPH_H
