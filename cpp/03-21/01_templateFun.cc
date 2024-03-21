#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

template <typename T> 
T add(T a, T b) {
    return a + b;
}

void test0() {
    int ia = 3, ib = 3;
    double da = 4.5, db = 7.9;
    cout << add(ia, ib) << endl;
    cout << add(da, db) << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

