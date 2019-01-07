#ifndef THREADINTERFACE_H
#define THREADINTERFACE_H

class ThreadInterface
{
public:
    ThreadInterface(){}
    virtual ~ThreadInterface() {}
    virtual void threadMethod();
};

#endif // THREADINTERFACE_H
