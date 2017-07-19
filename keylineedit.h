#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include "keypad.h"

class KeyLineEdit : public QLineEdit
{
public:
    KeyLineEdit(QString currentString, QWidget *parent = 0);

private:
    Keypad *keypad;
    QPushButton *trigger;
};

#endif // KEYLINEEDIT_H
