#include "TaskQueue.h"
#include <iostream>
#include <mutex>

using namespace std;


TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
, _flag(true)
{

}

TaskQueue::~TaskQueue() {

}

void TaskQueue::push(ElemType task) {
    // 1. 上锁(自动解锁)
    unique_lock<mutex> autoLock(_mutex);
    // 2. 判断是否满
    while(full()) {
        _notFull.wait(autoLock);
    }
    // 3. 加入队列 
    _que.push(task);   
    // 4. 通知消费者 
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop() {
    // 1. 上锁(自动解锁)
    unique_lock<mutex> autoLock(_mutex); 
    // 2. 判断是否满
    while(empty() && _flag) {
        _notEmpty.wait(autoLock);
    }
    if (_flag) {
        // 3. 移出队列 
        ElemType tmp = _que.front();
        _que.pop();
        // 4. 通知消费者 
        _notFull.notify_one();
        return tmp;
    } else {
        return nullptr;
    }
}

bool TaskQueue::full() {
    return _queSize == _que.size();
}

bool TaskQueue::empty() {

    return 0 == _que.size();
}

void TaskQueue::weakup() {
    _flag = false;
    _notEmpty.notify_all(); 
}
