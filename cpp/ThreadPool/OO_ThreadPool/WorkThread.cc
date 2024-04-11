#include "WorkThread.h"
#include "ThreadPool.h"


WorkThread::WorkThread(ThreadPool &pool)
: _pool(pool)
{

}
void WorkThread::run() {
    _pool.doTask();
}
