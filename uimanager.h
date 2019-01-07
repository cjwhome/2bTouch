#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QList>
#include <QSettings>

//Use these defines to access the forms in other classes, if an index changes than only 1 change is needed
#define menuIndex 0
#define calIndex 1
#define analogIndex 2
#define dateTimeIndex 3
#define averageIndex 4
#define modbusIndex 5
#define networkIndex 6

class UiManager{
public:
    static UiManager * getManager();

    QList<QWidget *> * settingWidgets = new QList<QWidget *>();
    int currentSIndex = 0;
    QWidget * cWidget = nullptr;
    QWidget * network = nullptr;
    QSettings *settings;

    //CalForm, AnalogForm, DateTimeForm, ModForm, AverageForm, ModBusForm, NetworkForm
    QList<QWidget *> * statsWidgets = new QList<QWidget *>();
    int cStatIndex = 0;
    QWidget * cStatWidget;

    bool finishedCreating = false;

private:
    static UiManager * manager;
    UiManager(){
        settings = new QSettings("2B Technologies", "2B Touch");
    }
};

#endif // UIMANAGER_H
