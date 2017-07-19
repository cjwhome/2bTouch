#include "keylineedit.h"
#include <QEvent>
#include <QDebug>

KeyLineEdit::KeyLineEdit(QString currentString, QWidget *parent)
{
    qDebug()<<"currentString to keypad:"<<currentString;
    this->setText(currentString);
    keypad = new Keypad(this, false, parent);

    trigger = new QPushButton(this);
    this->setStyleSheet("QPushButton { background-color: rgba(10, 0, 0, 0); }");
    trigger->setGeometry(0, 0, this->width(), this->height());
    connect(trigger, SIGNAL(released()), keypad, SLOT(show()));
}

