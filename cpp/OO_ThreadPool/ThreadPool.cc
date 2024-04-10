#include "ThreadPool.h"
#include "Thread.h"
#include "WorkThread.h"
#include <memory>
#include <unistd.h>


using namespace std;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _isExit(false)
, _taskQue(_queSize)
{
    // 预留空间
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool() {

}

/**
 * 启动线程池 
 */
void ThreadPool::start() {
    for (size_t i = 0; i < _threadNum; ++i) {
        WorkThread *temp = new WorkThread(*this);  
        _threads.push_back(unique_ptr<Thread>(temp));
        temp->start(); // 启动线程
    }
} 

/**
 * 关闭线程池
 */
void ThreadPool::stop() {
    while (!_taskQue.empty()) {
        sleep(1);
    }
    _isExit = true;
    _taskQue.weakup();
    for (const auto &th: _threads) {
        th->stop();
    }
}

/**
 * 添加一个任务 
 */
void ThreadPool::addTask(Task *task) {
    if (task) { // 非空
        _taskQue.push(task);
    }
}

/**
 * 获取一个任务
 */
Task *ThreadPool::getTask() {
    return _taskQue.pop();
}

/**
 * 执行任务
 */
void ThreadPool::doTask() {
    while (!_isExit) {
        Task *task = getTask();
        if (task) {
            task->process();
        } else {
            cerr << "nullptr == task" << endl;
        }
    }
}



