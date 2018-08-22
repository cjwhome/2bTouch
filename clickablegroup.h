#ifndef CLICKABLEGROUP_H
#define CLICKABLEGROUP_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QGroupBox>
#include <QLabel>

class ClickableGroup : public QGroupBox
{
    Q_OBJECT

public:
    explicit ClickableGroup(QWidget *parent = nullptr, QLabel * labelA = nullptr, QLabel * labelB = nullptr, QLabel * labelC = nullptr);
    void updateLabelA(QString value);
    void updateLabelB(QString value);
    void updateLabelC(QString value);


signals:
    void clicked();

public slots:

protected:
    void mousePressEvent ( QMouseEvent * event );

private:
    QLabel * lA;
    QLabel * lB;
    QLabel * lC;
};

#endif // CLICKABLEGROUP_H
