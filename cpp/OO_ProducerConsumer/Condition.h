#ifndef _CONDITION_H
#define _CONDITION_H

#include <pthread.h>

class MutexLock;

class Condition {
public:
    Condition(MutexLock &mutex);

    ~Condition();

    void wait();

    void notify();

    void nodtifyAll();
private: 
    pthread_cond_t _cond;
    MutexLock & _mutex;
};

#endif //_CONDITION_H