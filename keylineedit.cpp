#include "keylineedit.h"
#include <QEvent>

KeyLineEdit::KeyLineEdit(QWidget *parent)
{
    keypad = new Keypad(this, false, this);
    this->setAttribute(Qt::WA_AcceptTouchEvents);
}

/*bool KeyLineEdit::event(QEvent *event) {
    if(event->type() == QEvent::TouchEnd) {
        keypad->show();
    }

    return true;
}*/
