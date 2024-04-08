#include "Producer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

void Producer::produce(TaskQueue &taskQue) {
    srand(clock());
    int cnt = 20;
    while (cnt--) {
        int number = rand() % 100;
        taskQue.push(number);
        cout << ">>Producer produce " << number << endl;  
        /* sleep(1); */
    }
}



