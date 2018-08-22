#include "clickablegroup.h"

ClickableGroup::ClickableGroup(QWidget *parent, QLabel * labelA, QLabel * labelB, QLabel * labelC) : QGroupBox(parent)
{

    lA = labelA;
    lB = labelB;
    lC = labelC;
}

void ClickableGroup::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void ClickableGroup::updateLabelA(QString value)
{
    lA->setText(value);
    QPalette p = lA->palette();
    p.setColor(QPalette::WindowText, Qt::green);
    lA->setPalette(p);
}

void ClickableGroup::updateLabelB(QString value)
{
    lB->setText(value);
    QPalette p = lB->palette();
    p.setColor(QPalette::WindowText, Qt::green);
    lB->setPalette(p);
}

void ClickableGroup::updateLabelC(QString value)
{
    lC->setText(value);
    QPalette p = lC->palette();
    p.setColor(QPalette::WindowText, Qt::green);
    lC->setPalette(p);
}
