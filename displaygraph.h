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
#include <QPen>

#include "selectgasform.h"
#include "qcustomplot.h"
#include "graphsettingsform.h"
#include "gasdatastate.h"


namespace Ui {
class DisplayGraph;
}

class DisplayGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayGraph(QWidget *parent = nullptr, QList<GasDataState *> * data = nullptr);
    ~DisplayGraph();
    void setData(QVector<double> a, QVector<double> b);
    void setData(QVector<double> a, QVector<double> b, int gIndex);

    void drawPlot();

    void addPlot();
    void setPlotData();


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
    GraphSettingsForm *settingsdialog;
    SelectGasForm* gas;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *zoomHLayout;
    QHBoxLayout *buttonLayout;
    QList<QPen*> *pens;

    QCustomPlot *customPlot;
    QVector<double> x,y;

    QString m_sSettingsFile;

    void loadSettings();
    void saveSettings();
    QSettings *settings;

    void fixScale();

    bool autoscalex = true;
    bool autoscaley = true;

    bool isVisible;

    double minY = 0;
    double maxY = 10;

    QList<GasDataState *> * gasses;
};

#endif // DISPLAYGRAPH_H
