#include "keylineedit.h"
#include <QEvent>

KeyLineEdit::KeyLineEdit(QWidget *parent)
{
    keypad = new Keypad(this, false, parent);

    trigger = new QPushButton(this);
    this->setStyleSheet("QPushButton { background-color: rgba(10, 0, 0, 0); }");
    trigger->setGeometry(0, 0, this->width(), this->height());
    connect(trigger, SIGNAL(released()), keypad, SLOT(show()));
}

