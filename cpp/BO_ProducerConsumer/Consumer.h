/**
 * Project FreeTime
 */


#ifndef _CONSUMER_H
#define _CONSUMER_H

#include "Thread.h"
#include "TaskQueue.h"


class Consumer {
public: 
    void consume(TaskQueue &taskQue);
};

#endif //_CONSUMER_H
