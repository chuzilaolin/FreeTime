#include "Task.h"
#include "ThreadPool.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <memory>

using namespace std;

class MyTask 
: public Task
{
public:
    void process() override{
        ::srand(clock());
        int num = ::rand() % 100;
        cout << "MyTask produce a num is " << num << endl;
    }
};


void test0() {
    ThreadPool tp(4, 10); 
    tp.start();
    unique_ptr<MyTask> uptr(new MyTask);
    int cnt = 20;
    while (cnt--) {
        tp.addTask(uptr.get());
    }
    tp.stop();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

