#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent, int v) : QLabel(parent)
{
    val = v;
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked(val);
}
