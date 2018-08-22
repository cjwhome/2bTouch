#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QDialog>

namespace Ui {
class MainDisplay;
}

class MainDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit MainDisplay(QWidget *parent = nullptr);
    ~MainDisplay();

private:
    Ui::MainDisplay *ui;
};

#endif // MAINDISPLAY_H
