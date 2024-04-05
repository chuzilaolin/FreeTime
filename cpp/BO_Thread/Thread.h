#ifndef __THREAD_H__
#define __THREAD_H__
#include <pthread.h>
#include <functional>

class Thread {
public: 
    using ThreadCallback = std::function<void()>; 
    Thread(ThreadCallback &&cb);
    virtual ~Thread();
    // 线程启动
    void start();
    // 线程停止
    void stop();
private:
    // 线程入口函数
    static void *threadFunc(void *args);
private:
    pthread_t _thid; // 线程id
    bool _isRunning; // 标识线程是否运行              
    ThreadCallback _cb;
};


#endif
