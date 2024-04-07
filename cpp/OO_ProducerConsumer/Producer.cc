#include "Producer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

Producer::Producer(TaskQueue & taskQue)
: _taskQue(taskQue){

}

Producer::~Producer() {

}

/**
 * @return void
 */
void Producer::run() {
    srand(clock());
    int cnt = 20;
    while (cnt--) {
        int number = rand() % 100;
        _taskQue.push(number);
        cout << ">>Producer produce " << number << endl;  
        /* sleep(1); */
    }
}
