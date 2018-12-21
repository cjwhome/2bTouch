#ifndef NETOWRKFORM_H
#define NETOWRKFORM_H

#include <QWidget>

namespace Ui {
class NetowrkForm;
}

class NetowrkForm : public QWidget
{
    Q_OBJECT

public:
    explicit NetowrkForm(QWidget *parent = nullptr);
    ~NetowrkForm();

private:
    Ui::NetowrkForm *ui;
};

#endif // NETOWRKFORM_H
