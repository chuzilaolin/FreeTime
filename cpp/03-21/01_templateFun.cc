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
template <typename T1, typename T2>
T1 add(T1 a, T2 b) {
    cout << "template 1" << endl;
    return a + b;
}
template <typename T1, typename T2>
T1 add(T2 a, T1 b) {
    cout << "template 2" << endl;
    return a + b;
}
template <typename T1, typename T2, typename T3>
T2 add(T2 a, T3 b) {
    cout << "template 3" << endl;
    return a + b;
}


// template <typename T1, int kBase>
template <typename T1, int kBase = 9>
T1 multiply(T1 a, T1 b) {
    return a * b * kBase;
}

void test0() {
    int ia = 3, ib = 3;
    double da = 4.5, db = 7.9;
    cout << add(ia, ib) << endl;
    cout << add<int, int, double>(da, ib) << endl;
    cout << add(ia, ib) << endl; 
    // cout << add<int>(ia, da) << endl;
    // cout << add<int>(da, ia) << endl;
    // cout << add<double, int>(da, ia) << endl;
    // cout << add<double, int>(ia, da) << endl;
    // cout << add<double, int>(ia, da) << endl;
    // cout << add<int, double>(da, ia) << endl;
    // cout << multiply<int,10>(ia, ib) << endl;
    // cout << multiply<int>(ia, ib) << endl;
    // cout << multiply(ia, ib) << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

