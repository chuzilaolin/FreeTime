#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

struct Example {
    int age = 1;
    string name = "zs";
    void print() {
        cout << name << " " << age << endl;
    }
    void operator()() {
        cout << "operator()" << endl;
    }
} ExampleAAA;

void test(Example &example) {
    example();
}

void test0() {
    Example example;
    test(example);
    test(ExampleAAA);
}


int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

