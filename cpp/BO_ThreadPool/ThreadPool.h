#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <functional>
#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

using Task = function<void()>;

class Thread;
class ThreadPool {
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();
    void start(); 
    void stop();
    void addTask(Task &&task);
private:
    Task getTask();
    void doTask();
    
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};


#endif
