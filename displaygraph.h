#ifndef DISPLAYGRAPH_H
#define DISPLAYGRAPH_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QVector>
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

public slots:
    void blah();

private slots:
    void goback();

private:
    Ui::DisplayGraph *ui;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *buttonLayout;
    QPushButton *home_button;
    QPushButton *settings_button;
    QCustomPlot *customPlot;
    QVector<double> x,y;
};

#endif // DISPLAYGRAPH_H
