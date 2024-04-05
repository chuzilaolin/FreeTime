#include <bits/types/clock_t.h>
#include <cstddef>
#include <ctime>
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

int func1(int a, int b, int c, int d) {
    cout << "a = " << a << ", b = " << b 
        << ", c = " << c
        << ", d = " << d << endl;
    return 0;
}

void test0() {
    using namespace std::placeholders;
    auto f = bind(func, 2, _3, _1, _2);
    f(5, 9, 11);
}

void test1() {
    using namespace std::placeholders;
    function<void(int)> f = bind(func, 2, _1, _1, _1);
    f(5);
}

void test2() {
    using namespace std::placeholders;
    function<int(int)> f = bind(func1, 7, _1, _1, _1);
    f(3);
}

/* int rand() { */
/*     return 10; */
/* } */

void test3() {
    /* srand(clock()); */
    srand(time(NULL));
    cout << ::rand() << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
#if 0
    test0();
    test2();
#endif
    test3();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

