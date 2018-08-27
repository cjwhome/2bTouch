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
    explicit StatsWidget( DeviceProfile profile,QWidget *parent = 0);
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

    QFont titleFont;
    QString goodStylesheet;
    QString badStylesheet;

    QSize buttonSize;
    QSize widgetSize;
    QRect widgetGeo;

    QWidget *avgWidget;
    QVBoxLayout *avgVLayout;
    QHBoxLayout *avgNonRow;
    QLabel *avgNonLabel;
    QLabel *avgNonTitle;
    QHBoxLayout *avgHourRow;
    QLabel *avgHourTitle;
    QLabel *avgHourLabel;
    QHBoxLayout *avgEightRow;
    QLabel *avgEightTitle;
    QLabel *avgEightLabel;

    QWidget *oneWidget;
    QVBoxLayout *oneVLayout;
    QHBoxLayout *oneARow;
    QLabel *oneATitle;
    QLabel *oneALabel;
    QHBoxLayout *oneBRow;
    QLabel *oneBTitle;
    QLabel *oneBLabel;

    QWidget *twoWidget;
    QVBoxLayout *twoVLayout;
    QHBoxLayout *twoARow;
    QLabel *twoATitle;
    QLabel *twoALabel;
    QHBoxLayout *twoBRow;
    QLabel *twoBTitle;
    QLabel *twoBLabel;

    QWidget *threeWidget;
    QVBoxLayout *threeVLayout;
    QHBoxLayout *threeARow;
    QLabel *threeATitle;
    QLabel *threeALabel;
    QHBoxLayout *threeBRow;
    QLabel *threeBTitle;
    QLabel *threeBLabel;

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
