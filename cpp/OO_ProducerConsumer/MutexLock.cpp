/**
 * Project FreeTime
 */


#include "MutexLock.h"
#include <iostream>
#include <pthread.h>

/**
 * MutexLock implementation
 */


MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&_mutex, nullptr); 
    if (ret) {
        perror("pthread_mutex_init");
    }
}

MutexLock::~MutexLock() {
    int ret = pthread_mutex_destroy(&_mutex); 
    if (ret) {
        perror("pthread_mutex_destroy");
    }
}

/**
 * @return void
 */
void MutexLock::lock() {
    int ret = pthread_mutex_lock(&_mutex); 
    if (ret) {
        perror("pthread_mutex_lock");
    }
}

/**
 * @return void
 */
void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&_mutex); 
    if (ret) {
        perror("pthread_mutex_unlock");
    }
}

/**
 * @return void
 */
void MutexLock::trylock() {
    int ret = pthread_mutex_trylock(&_mutex); 
    if (ret) {
        perror("pthread_mutex_trylock");
    }
}

pthread_mutex_t *MutexLock::getMutexLockPtr() {
    return &_mutex;
}
