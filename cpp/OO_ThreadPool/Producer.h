#ifndef _PRODUCER_H
#define _PRODUCER_H

#include "Thread.h"
#include "TaskQueue.h"


class Producer: public Thread {
public: 
    
    Producer(TaskQueue & taskQue);
    
    ~Producer();
    void run() override;
private: 
    TaskQueue & _taskQue;
};

#endif //_PRODUCER_H
