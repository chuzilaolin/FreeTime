#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


using namespace std;

void print(int x) {
    cout << "x = " << x << endl;
    struct sockaddr_in serv_addr;
}

void test0() {
    thread th(print, 3);
    th.join();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

