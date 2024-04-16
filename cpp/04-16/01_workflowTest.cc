#include <func.h>
#include <workflow/WFFacilities.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum) {
    printf("signum = %d\n", signum);
    gWaitGroup.done();
}
void test0() {
    signal(SIGINT, handler);
    gWaitGroup.wait(); 
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

