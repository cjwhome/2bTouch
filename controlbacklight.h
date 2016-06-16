#ifndef CONTROLBACKLIGHT_H
#define CONTROLBACKLIGHT_H
#include <QProcess>
#include <QDebug>


class ControlBacklight
{
public:
    ControlBacklight();
    void setPercentage(int percentage);
};

#endif // CONTROLBACKLIGHT_H
