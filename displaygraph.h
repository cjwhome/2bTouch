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
#include "graphsettingsdialog.h"


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
    GraphSettingsDialog *settingsdialog;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *zoomHLayout;
    QWidget *menuWidget;
    QHBoxLayout *buttonLayout;

<<<<<<< HEAD
    //QTimer *timer;
    bool menuIsShowing;

=======
>>>>>>> 53d69c6e0f6780facc0408cc9525eb5e30bd5129
    QCustomPlot *customPlot;
    QVector<double> x,y;

    QString m_sSettingsFile;

    void loadSettings();
    void saveSettings();

    bool autoscalex;
    bool autoscaley;
};

#endif // DISPLAYGRAPH_H
