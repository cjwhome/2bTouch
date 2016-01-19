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
private:
    Ui::DisplayGraph *ui;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *zoomHLayout;
    QVBoxLayout *buttonLayout;
    QPushButton *home_button;
    QPushButton *clear_button;
    QPushButton *settings_button;
    QPushButton *zoom_in_button;
    QPushButton *zoom_out_button;
    QCustomPlot *customPlot;
    QVector<double> x,y;

};

#endif // DISPLAYGRAPH_H
