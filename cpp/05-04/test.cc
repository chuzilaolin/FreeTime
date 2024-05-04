#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <queue>
#include <workflow/WFFacilities.h>

using namespace std;

template<typename T>
void printQue(T& q) {
    while(!q.empty()){
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

struct MyLess {
    bool operator()(int a, int b) {
        return a < b;
    }
};

void test0() {
    priority_queue<int, vector<int>, greater<int>> q1;
    for(int n : {1,8,5,6,3,4,0,9,7,2}) {
        q1.push(n);
    }
    printQue(q1);
    priority_queue<int, vector<int>, MyLess> q2;
    for(int n : {1,8,5,6,3,4,0,9,7,2}) {
        q2.push(n);
    }
    printQue(q2);
    cout << endl;
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

