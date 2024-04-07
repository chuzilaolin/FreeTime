#include "MutexLock.h"
#include "Condition.h"
#include <iostream>

/**
 * Condition implementation
 */


/**
 * @param mutex
 */
Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
    int ret = pthread_cond_init(&_cond, nullptr);    
    if (ret) {
        perror("pthread_cond_init");
    }
}

Condition::~Condition() {
    int ret = pthread_cond_destroy(&_cond);    
    if (ret) {
        perror("pthread_cond_destroy");
    }
}

/**
 * @return void
 */
void Condition::wait() {
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());    
    if (ret) {
        perror("pthread_cond_wait");
    }
}

/**
 * @return void
 */
void Condition::notify() {
    int ret = pthread_cond_signal(&_cond);    
    if (ret) {
        perror("pthread_cond_signal");
    }
}

/**
 * @return void
 */
void Condition::nodtifyAll() {
    int ret = pthread_cond_broadcast(&_cond);    
    if (ret) {
        perror("pthread_cond_broadcast");
    }
}