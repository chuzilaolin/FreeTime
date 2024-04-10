/**
 * Project FreeTime
 */


#ifndef _CONSUMER_H
#define _CONSUMER_H

#include "Thread.h"
#include "TaskQueue.h"


class Consumer: public Thread {
public: 
    Consumer(TaskQueue & taskQue);
    ~Consumer();
    void run() override;
private: 
    TaskQueue & _taskQue;
};

#endif //_CONSUMER_H
