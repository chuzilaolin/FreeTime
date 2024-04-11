#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <iostream>
#include <functional>

using std::queue;
using std::function;

using ElemType = function<void()>;

class TaskQueue {
public: 
    TaskQueue(size_t queSize);
    TaskQueue(const TaskQueue &taskQue) 
        : _notFull(taskQue._notFull)
          , _notEmpty(taskQue._notEmpty)
    {
        _queSize = taskQue._queSize;
        _que = taskQue._que;
        _mutex = taskQue._mutex;
        std::cout << "TaskQueue(const TaskQueue &taskQue)" << std::endl;
    }

    ~TaskQueue();

    // 添加任务
    void push(ElemType &&task);
    // 获取任务
    ElemType pop();
    // 任务队列是满
    bool full();
    // 任务队列是空
    bool empty();
    // 将所有等待在_notEmpty上的线程全部唤醒
    void wakeup();
private: 
    size_t _queSize; // 任务队列大小
    queue<ElemType> _que; // 存放任务的数据结构-队列
    MutexLock _mutex; // 互斥锁
    Condition _notFull; // 非满条件变量(生产者用)
    Condition _notEmpty; // 非空条件变量(消费者用)
    bool _flag; // 用于唤醒工作线程后,退出pop的while循环
};

#endif //_TASKQUEUE_H
