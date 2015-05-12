#ifndef SHOWSTATS_H
#define SHOWSTATS_H

#include <QMainWindow>

namespace Ui {
class ShowStats;
}

class ShowStats : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ShowStats(QWidget *parent = 0);
    ~ShowStats();
    
private:
    Ui::ShowStats *ui;
};

#endif // SHOWSTATS_H
