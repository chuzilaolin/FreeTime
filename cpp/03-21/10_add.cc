#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

double add() {
    return 0.0;
}

template<typename T, typename ...Args>
double add(T t, Args ...args) {
    return t + add(args...);
}

void test0() {
    cout << "res: " << add(1, 2.35, 4, 8.81) << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

