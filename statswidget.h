#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "serialdataitem.h"
#include "deviceprofile.h"

namespace Ui {
class StatsWidget;
}

class StatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatsWidget(QWidget *parent = 0);
    ~StatsWidget();

private:
    Ui::StatsWidget *ui;

    QHBoxLayout *mainLayout;
    QPushButton *homeButton;
    QPushButton *left;
    QWidget *placeHolder;
    QPushButton *right;
    QList<QWidget*> widgets;
    int currentIndex;

    QString goodStylesheet;
    QString badStylesheet;

    QSize buttonSize;
    QSize widgetSize;
    QRect widgetGeo;

    QWidget *avgWidget;
    QVBoxLayout *avgVLayout;
    QLabel *avgNonLabel;
    QLabel *avgHourLabel;
    QLabel *avgEightLabel;

    QWidget *oneWidget;
    QVBoxLayout *oneVLayout;
    QLabel *oneALabel;
    QLabel *oneBLabel;

    QWidget *twoWidget;
    QVBoxLayout *twoVLayout;
    QLabel *twoALabel;
    QLabel *twoBLabel;

    QWidget *threeWidget;
    QVBoxLayout *threeVLayout;
    QLabel *threeALabel;

private slots:
    void leftPressed();
    void rightPresed();
    void homePressed();

    QWidget* widgetForAvg();
    QWidget* widgetForOne();
    QWidget* widgetForTwo();
    QWidget* widgetForThree();

    QString shortenString(QString string);

public slots:
    void setData(QList< QList<SerialDataItem> > *records, DeviceProfile *profile);
    void calculateMaxMinMedian(QList< QList<SerialDataItem> > &records, int element_to_sort);
};

#endif // STATSWIDGET_H
