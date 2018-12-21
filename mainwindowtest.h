#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QWidget>

namespace Ui {
class MainWindowTest;
}

class MainWindowTest : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowTest(QWidget *parent = nullptr);
    ~MainWindowTest();

private:
    Ui::MainWindowTest *ui;
};

#endif // MAINWINDOWTEST_H
