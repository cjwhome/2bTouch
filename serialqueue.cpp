#include "serialqueue.h"

SerialQueue * SerialQueue::queue = nullptr;

QList<QString> * SerialQueue::q = nullptr;

SerialQueue * SerialQueue::getQueue(){
    if(queue == nullptr){
        queue = new SerialQueue();
        q = new QList<QString>();
    }
    return queue;
}

void SerialQueue::add(QString s){
    q->append(s);
}

QString SerialQueue::getFirst(){
    QString s = q->first();
    q->removeFirst();
    return s;
}

SerialQueue::SerialQueue()
{

}
