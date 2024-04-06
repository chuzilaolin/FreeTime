/**
 * Project FreeTime
 */


#ifndef _CONSUMER_H
#define _CONSUMER_H

#include "Thread.h"


class Consumer: public Thread {
public: 
    
/**
 * @param taskQue
 */
void Consumer(TaskQueue & taskQue);
    
void run();
private: 
    TaskQueue & _taskQue;
};

#endif //_CONSUMER_H