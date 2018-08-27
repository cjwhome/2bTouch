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
    int enteriesPerHour = -1;

    float getHourAverage()
    {
        if(enteriesPerHour != -1 && data.size() >= enteriesPerHour)
        {
            float count = 0;
            float num = 0;
            for(int i = data.size() - enteriesPerHour; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
        else
        {
            float count = 0;
            float num;
            for(int i = 0; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
    }

    float getEightAverage()
    {
        if(enteriesPerHour != -1 && data.size() >= (enteriesPerHour * 8))
        {
            float count = 0;
            float num = 0;
            for(int i = data.size() - (enteriesPerHour * 8); i < data.size(); i++)
            {
                count += data.at(i);
                num++;
            }
            //return 2.2f;
            return count / num;
        }
        else
        {
            float count = 0;
            float num = 0;
            for(int i = 0; i < data.size(); i++)
            {
                count += data.at(i);
                num++;
            }
            //return 2.2f;
            return count / num;
        }
    }

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
