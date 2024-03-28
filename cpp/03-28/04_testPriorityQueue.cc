#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <queue>

using namespace std;

template<typename T> 
void print_queue(T &q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

void test0() {
    vector<int> vec = {3, 5, 8, 4, 11, 2, 1};
    /* priority_queue<int> pque(vec.begin(), vec.end()); */
    priority_queue<int, vector<int>, greater<int>> pque(vec.begin(), vec.end());
    /* for (size_t i = 0; i < pque.size(); ++i) { */
    /*     cout << pque.top() << " "; */
    /*     pque.pop(); */
    /* } */
    print_queue(pque);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

