#ifndef SERIALQUEUE_H
#define SERIALQUEUE_H

#include <QList>

class SerialQueue
{

public:
    static SerialQueue * getQueue();

    void add(QString);
    QString getFirst();
private:
    static QList<QString> * q;
    SerialQueue();
    static SerialQueue * queue;
};

#endif // SERIALQUEUE_H
