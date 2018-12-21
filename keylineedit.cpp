#include "keylineedit.h"

KeyLineEdit::KeyLineEdit(QString currentString, QWidget *parent){
    setParent(parent);
    //qDebug()<<"currentString to keypad:"<<currentString;
    keypad = new Keypad(this, parent);
    this->setText(currentString);

    trigger = new QPushButton(this);
    this->setStyleSheet("QPushButton { background-color: rgba(10, 0, 0, 0); }");
    trigger->setGeometry(0, 0, this->width(), this->height());
    connect(trigger, SIGNAL(released()), keypad, SLOT(show()));
}

void KeyLineEdit::setText(const QString & text){
    QLineEdit::setText(text);
    keypad->setText(text);
}

QString KeyLineEdit::text(){
    return QLineEdit::text();
}
