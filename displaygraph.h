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
#include <QSettings>
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
    void setData2(QVector<double> a, QVector<double> b);

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
    GraphSettingsDialog *settingsdialog;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *zoomHLayout;
    QHBoxLayout *buttonLayout;

    QCustomPlot *customPlot;
    QVector<double> x,y, x2, y2;

    QString m_sSettingsFile;

    void loadSettings();
    void saveSettings();
    QSettings *settings;

    void fixScale();

    bool autoscalex;
    bool autoscaley;

    bool isVisible;
};

#endif // DISPLAYGRAPH_H
