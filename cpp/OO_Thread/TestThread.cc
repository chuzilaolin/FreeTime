#include "Thread.h"
#include <iostream>
#include <map>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>

using namespace std;

class MyThread 
: public Thread
{
public:
    MyThread() = default;
    ~MyThread(){};
private:
    void run() override {
        while(1) {
            cout << "MyThread is running" << endl;
            sleep(1);            
        }        
    }
};


void test0() {
     MyThread mth;
     mth.start();
     mth.stop();
}

void test1() {
    unique_ptr<MyThread> pmth(new MyThread());
    pmth->start();
    pmth->stop();
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

