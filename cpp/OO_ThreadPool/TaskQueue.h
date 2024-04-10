#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include <queue>

using std::queue;

using ElemType = Task *;

class TaskQueue {
public: 
    
TaskQueue(size_t queSize);
    
~TaskQueue();
    
// 添加任务
void push(ElemType task);
// 获取任务
ElemType pop();
// 任务队列是满
bool full();
// 任务队列是空
bool empty();
void weakup();
private: 
    size_t _queSize; // 任务队列大小
    queue<ElemType> _que; // 存放任务的数据结构-队列
    MutexLock _mutex; // 互斥锁
    Condition _notFull; // 非满条件变量(生产者用)
    Condition _notEmpty; // 非空条件变量(消费者用)
    bool _flag; // 用于唤醒工作线程时,正常退出pop的while循环
};

#endif //_TASKQUEUE_H
