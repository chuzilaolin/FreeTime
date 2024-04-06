/**
 * Project FreeTime
 */


#include "MutexLock.h"

/**
 * MutexLock implementation
 */


MutexLock::MutexLock() {

}

MutexLock::~MutexLock() {

}

/**
 * @return void
 */
void MutexLock::lock() {
    return;
}

/**
 * @return void
 */
void MutexLock::unlock() {
    return;
}

/**
 * @return void
 */
void MutexLock::trylock() {
    return;
}

pthread_mutex_t *MutexLock::getMutexLockPtr() {
    return &_mutex;
}
