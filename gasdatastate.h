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
    double minT = 99999;
    double maxT = -99999;
    QString unit = "";
    QVector<double> data;
    QVector<double> x;
    int enteriesPerHour = -1;
    int enteriesPerMinute = -1;
    QString *richTextName = new QString("Null");

    double getMinAverage()
    {
        if(enteriesPerMinute != -1 && data.size() >= enteriesPerMinute)
        {
            double count = 0;
            double num = 0;
            for(int i = data.size() - (enteriesPerMinute); i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
        else
        {
            double count = 0;
            double num = 0;
            for(int i = 0; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
    }

    double get5MinAverage()
    {
        if(enteriesPerMinute != -1 && data.size() >= (enteriesPerMinute * 5))
        {
            double count = 0;
            double num = 0;
            for(int i = data.size() - (enteriesPerMinute * 5); i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
        else
        {
            double count = 0;
            double num = 0;
            for(int i = 0; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
    }

    double getHourAverage()
    {
        if(enteriesPerHour != -1 && data.size() >= enteriesPerHour)
        {
            double count = 0;
            double num = 0;
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
            double count = 0;
            double num = 0;
            for(int i = 0; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
    }
    double getEightAverage()
    {
        if(enteriesPerHour != -1 && data.size() >= (enteriesPerHour * 8))
        {
            double count = 0;
            double num = 0;
            for(int i = data.size() - (enteriesPerHour * 8); i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2f;
            return count / num;
        }
        else
        {
            double count = 0;
            double num = 0;
            for(int i = 0; i < data.size(); i++)
            {
                num++;
                count += data.at(i);
            }
            //return 2.2;
            return count / num;
        }
    }
    void addData(double time, double data) {
        x.append(time);
        this->data.append(data);
        if(data < min){
            min = data;
        }
        if(data > max){
            max = data;
        }
        if(time < minT){
            minT = time;
        }
        if(time > maxT){
            maxT = time;
        }
    }
    void setRichName(){
        if(*name == "ERROR")
            return;
        for(int j = 0; j < name->length(); j++){
            if(name->at(j) >= 48 && name->at(j) <= 57){
                richTextName->append("<sub>" + QString(name->at(j)) + "</sub>");
            }else{
                richTextName->append(QString(name->at(j)));
            }
        }
    }
};

#endif // GASDATASTATE_H
