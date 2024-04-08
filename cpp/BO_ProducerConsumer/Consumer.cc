#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void Consumer::consume(TaskQueue & taskQue) {
    int cnt = 20;
    while(cnt--) {
        int value = taskQue.pop();
        cout << "<< Consumer consume " << value << endl;
        /* sleep(1); */
    }
}


