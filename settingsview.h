#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>


namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = 0);
    ~SettingsView();
    QString getBashIPAddress(void);
private slots:
    void home();
    void showNetworkView();
    void showAdminView();
    void checkPassword(QString password);
private:
    Ui::SettingsView *ui;
    QString setPassword;


};

#endif // SETTINGSVIEW_H
