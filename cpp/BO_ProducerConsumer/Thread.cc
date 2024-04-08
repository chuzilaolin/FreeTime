#include "Thread.h"
#include <iostream>
#include <map>
#include <pthread.h>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

Thread::Thread(ThreadCallback && cb)
: _thid(0)
, _isRunning(false)
, _cb(move(cb))
{}

Thread::~Thread() {}

void Thread::start() {
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if (ret) {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::stop() {
    if (_isRunning) {
        int ret = pthread_join(_thid, nullptr);
        cout << "pthread_join is start..." << endl;
        if (ret) {
            perror("pthread_join");
            return;
        }
        cout << "pthread_join is end..." << endl;
        _isRunning = false;
    }
}

void *Thread::threadFunc(void *args) {
    Thread *pth = static_cast<Thread *>(args);
    if (pth) {
        pth->_cb();
    } else {
        cerr << "nullptr == pth" << endl;
    }
    pthread_exit(nullptr);
}

