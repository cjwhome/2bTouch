#ifndef GASDATASTATE_H
#define GASDATASTATE_H

#include <QVector>
#include <QString>
#include "math.h"

struct GasDataState {
    int columnIndex = 0;
    bool selected = false;
    QString *name = new QString("ERROR");
    double min = 99999;
    double max = -99999;
    double minT = 999999999999999999;
    double maxT = -99999;
    QString unit = "";
    QVector<double> data;
    QVector<double> x;

    void addData(double time, double data) {
        x.append(time);
        this->data.append(data);
        if(data < min)
        {
            min = data;
        }
        if(data > max)
        {
            max = data;
        }

        if(time < minT)
        {
            minT = time;
        }
        if(time > maxT)
        {
            maxT = time;
        }
    }
};

#endif // GASDATASTATE_H
