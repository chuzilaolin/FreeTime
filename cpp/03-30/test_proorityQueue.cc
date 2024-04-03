#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <queue>
#include <functional>

using namespace std;

void print(priority_queue<int> &pq) {
    cout << "size is :" << pq.size() << endl;
    int count = pq.size();
    for (int i = 0; i < count; ++i) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

void print1(priority_queue<int, vector<int>, function<bool(int, int)>> &pq) {
    cout << "size is :" << pq.size() << endl;
    int count = pq.size();
    for (int i = 0; i < count; ++i) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}


void test0() {
    vector<int> vec{1, 4, 2, 9, 4, 3, 6};
    priority_queue<int, vector<int>, less<int>> pq;
    for (int n : vec) {
        pq.push(n);
    }
    print(pq);
}

void test1() {
    vector<int> vec{1, 4, 2, 9, 4, 3, 6};
    priority_queue<int, vector<int>, function<bool(int, int)>> pq([](int a, int b){
                                                                  return a > b;
                                                                  });
    for (int n : vec) {
        pq.push(n);
    }
    print1(pq);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test1();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

