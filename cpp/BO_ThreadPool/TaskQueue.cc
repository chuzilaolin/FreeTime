#include "TaskQueue.h"
#include "MutexLock.h"
#include <iostream>

using namespace std;


TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{
    cout << "TaskQueue::TaskQueue(size_t queSize)" << endl;
}

TaskQueue::~TaskQueue() {
    cout << "TaskQueue::~TaskQueue()" << endl;    
}

void TaskQueue::push(const int& value) {
    // 1. 上锁(自动解锁)
    MutexLockGuard autoLock(_mutex);
    // 2. 判断是否满
    while(full()) {
        _notFull.wait();
    }
    // 3. 加入队列 
    _que.push(value);   
    // 4. 通知消费者 
    _notEmpty.notify();
}

int TaskQueue::pop() {
    // 1. 上锁(自动解锁)
    MutexLockGuard autoLock(_mutex);
    // 2. 判断是否满
    while(empty()) {
        _notEmpty.wait();
    }
    // 3. 移出队列 
    int tmp = _que.front();
    _que.pop();
    // 4. 通知消费者 
    _notFull.notify();
    return tmp;
}

bool TaskQueue::full() {
    return _queSize == _que.size();
}

bool TaskQueue::empty() {

    return 0 == _que.size();
}
