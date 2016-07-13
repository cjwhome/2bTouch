#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include "keypad.h"

class KeyLineEdit : public QLineEdit
{
public:
    KeyLineEdit(QWidget *parent = 0);

private:
    Keypad *keypad;

protected:
    //bool event(QEvent *event);
};

#endif // KEYLINEEDIT_H
