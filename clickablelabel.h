#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = nullptr, int v = 0);

signals:
    void clicked(int val);

public slots:

protected:
    void mousePressEvent ( QMouseEvent * event );

private:
    int val;
};

#endif // CLICKABLELABEL_H
