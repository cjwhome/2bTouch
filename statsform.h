#ifndef STATSFORM_H
#define STATSFORM_H

#include <QWidget>

namespace Ui {
class StatsForm;
}

class StatsForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatsForm(QWidget *parent = nullptr);
    ~StatsForm();

private slots:
    void on_home_clicked();

    void on_mNext_clicked();

    void on_mPrev_clicked();

    void on_selectGas_activated(int index);

private:
    Ui::StatsForm *ui;
};

#endif // STATSFORM_H
