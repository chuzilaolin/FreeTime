#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <functional>

using namespace std;

void func(int a, int b, int c, int d) {
    cout << "a = " << a << ", b = " << b 
        << ", c = " << c
        << ", d = " << d
        << endl;
}

void test0() {
    using namespace std::placeholders;
    auto f = bind(func, 2, _3, _1, _2);
    f(5, 9, 11);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

