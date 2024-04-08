#include "Condition.h"
#include "Thread.h"
#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"
#include <iostream>
#include <chrono>
#include <memory>


using namespace std;



void test0() {
    TaskQueue que(10);
    Producer pro;
    Consumer con;
    
    /* unique_ptr<Thread> producer(new Thread(bind(&Producer::produce, &pro, que))); */
    /* unique_ptr<Thread> consumer(new Thread(bind(&Consumer::consume, &con, que))); */
    unique_ptr<Thread> producer(new Thread(bind(&Producer::produce, &pro, ref(que))));
    unique_ptr<Thread> consumer(new Thread(bind(&Consumer::consume, &con, ref(que))));
    
    producer->start();
    consumer->start();

    producer->stop();
    consumer->stop();
    cout << "---------->end......" << endl;
}


int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

