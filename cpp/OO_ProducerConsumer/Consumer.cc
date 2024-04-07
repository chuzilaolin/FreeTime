#include "Consumer.h"
#include <iostream>
#include <unistd.h>

using namespace std;

/**
 * Consumer implementation
 */


/**
 * @param taskQue
 */
Consumer::Consumer(TaskQueue & taskQue)
: _taskQue(taskQue){

}
Consumer::~Consumer(){

}

/**
 * @return void
 */
void Consumer::run() {
    int cnt = 20;
    while(cnt--) {
        int value = _taskQue.pop();
        cout << "<< Consumer consume " << value << endl;
        /* sleep(1); */
    }
}
