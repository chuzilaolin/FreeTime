/**
 * Project FreeTime
 */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

class TaskQueue {
public: 
    
/**
 * @param queSize
 */
void TaskQueue(size_t queSize);
    
void ~TaskQueue();
    
/**
 * @param value
 */
void push(const int& value);
    
int pop();
    
bool empty();
private: 
    queue<int> _que;
    MutexLock _mutex;
    Condition _cond;
    size_t _queSize;
};

#endif //_TASKQUEUE_H