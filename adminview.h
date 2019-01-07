#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QWidget>

namespace Ui {
class AdminView;
}

class AdminView : public QWidget
{
    Q_OBJECT

public:
    explicit AdminView(QWidget *parent = 0);
    ~AdminView();
public slots:

    void checkPassword(QString password);
private slots:
    //void home();
private:
    Ui::AdminView *ui;
    void getPassword(void);
    void loadSettings(void);
    QString setPassword;
};

#endif // ADMINVIEW_H
