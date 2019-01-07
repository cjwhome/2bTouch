#ifndef USERTYPEVIEW_H
#define USERTYPEVIEW_H

#include <QWidget>
#include "keypad.h"

namespace Ui {
class UserTypeView;
}

class UserTypeView : public QWidget
{
    Q_OBJECT

public:
    explicit UserTypeView(QString label, QWidget *parent = 0);
    ~UserTypeView();

private slots:

    bool showKeyPad(QLineEdit *line);
    bool eventFilter(QObject *, QEvent *);

signals:
    void outputUserString(QString userString);

private:

    Keypad *k;
    Ui::UserTypeView *ui;
};

#endif // USERTYPEVIEW_H
