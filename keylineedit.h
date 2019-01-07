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
    KeyLineEdit(QWidget * parent = nullptr);
    KeyLineEdit(QString currentString, QWidget *parent = nullptr);

    QString * pPext = nullptr;

    virtual void setText(const QString &);
    virtual QString text();

public slots:
    void change();

private:
    Keypad *keypad = nullptr;
    QPushButton *trigger = nullptr;
};

#endif // KEYLINEEDIT_H
