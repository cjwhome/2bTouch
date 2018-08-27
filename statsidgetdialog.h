#ifndef STATSIDGETDIALOG_H
#define STATSIDGETDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class StatsidgetDialog;
}

class StatsidgetDialog : public QWidget
{
    Q_OBJECT

public:
    explicit StatsidgetDialog(QWidget *parent = 0);
    ~StatsidgetDialog();

private:
    Ui::StatsidgetDialog *ui;
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

    void updateDisplay();

private slots:
    void leftPressed();
    void rightPressed();
    void homePressed();


};

#endif // STATSIDGETDIALOG_H
