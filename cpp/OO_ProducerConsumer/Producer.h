/**
 * Project FreeTime
 */


#ifndef _PRODUCER_H
#define _PRODUCER_H

#include "Thread.h"


class Producer: public Thread {
public: 
    
/**
 * @param taskQue
 */
void Producer(TaskQueue & taskQue);
    
void run();
private: 
    TaskQueue & _taskQue;
};

#endif //_PRODUCER_H