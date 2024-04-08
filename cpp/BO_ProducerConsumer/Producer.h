#ifndef _PRODUCER_H
#define _PRODUCER_H

#include "Thread.h"
#include "TaskQueue.h"


class Producer {
public: 
    
    void produce(TaskQueue &taskQue);
};

#endif //_PRODUCER_H
