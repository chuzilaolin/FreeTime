#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void test() {
    int a = 10;
    double b = 13;
}

void test0() {
    int a = 10;
    test();
    int b = 13;
    cout << "this is a simple cpp" << endl;
    int c = 13;
    cout << a << ", " << b << ", ------>" << c << endl;
    cout << "this is a test" << endl;
}

int main(void) {
    test0();
    return 0;
}

