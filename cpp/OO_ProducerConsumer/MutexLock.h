#ifndef _MUTEXLOCK_H
#define _MUTEXLOCK_H

#include <pthread.h>

class MutexLock {
public: 
    
MutexLock();
    
~MutexLock();
    
void lock();
    
void unlock();
    
void trylock();

pthread_mutex_t *getMutexLockPtr();

private: 
    pthread_mutex_t _mutex;
};

/*
 * 基于RALL思想的自动加解锁类
 */
class MutexLockGuard {
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard() {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};

#endif //_MUTEXLOCK_H
