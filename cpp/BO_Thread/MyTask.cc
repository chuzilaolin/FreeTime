#include "Thread.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <memory>

using namespace std;

class MyTask {
public:
    void process(int x) {
        while (1) {
            cout << "MyTask is running, x = " << x << endl;
            sleep(x);
        }
    }
};


void test0() {
    MyTask task;
    auto func = bind(&MyTask::process, &task, 2);
    Thread th(func);
    th.start();
    th.stop();
}

void func(int x) {
    while (1) {
        cout << "MyTask is running, x = " << x << endl;
        sleep(x);
    }
}

void test1() {
    unique_ptr<Thread> th(new Thread(bind(func, 3))); 
    th->start();
    th->stop();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    /* test0(); */
    test1();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

