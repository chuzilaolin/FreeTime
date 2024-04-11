#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

using std::vector;
using std::thread;

class ThreadPool {
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();
    void start(); 
    void stop();
    void addTask(Task *task);
private:
    Task *getTask();
    void doTask();
    
private:
    size_t _threadNum;
    size_t _queSize;
    vector<thread> _threads;
    bool _isExit;
    TaskQueue _taskQue;
};


#endif
