#ifndef KEYPAD_H
#define KEYPAD_H

#include <QDialog>
#include <QLineEdit>

#include "networkmanager.h"

namespace Ui {
class Keypad;
}

class Keypad : public QDialog
{
    Q_OBJECT

public:
    explicit Keypad(QLineEdit *line,QWidget *parent = nullptr);
    explicit Keypad(QLineEdit *line, QString * string, QWidget *parent = nullptr);
    ~Keypad();
    void setText(QString);
    QString getText();

public slots:
    void setalphabet();

private slots:
    void keypadHandler();
    void symbolChange();
    void keyclose();
    void boardchange();

private:
    Ui::Keypad *ui;
    QLineEdit *pad_edit;
    bool capitals,t1;
    void setsymbol();
    void setnumeric();
};

#endif // KEYPAD_H
