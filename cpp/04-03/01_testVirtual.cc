#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class A {
public:
    // virtual void print() {
    //     cout << "this is A" << endl;
    // }
    // virtual ~A() {
    //     cout << "~A()" << endl;
    // }
    virtual void print() = 0;
    virtual ~A() = 0;
};

class B
: public A 
{
public:
    void print() override {
        cout << "this is B" << endl;
    }
    ~B() {
        cout << "~B()" << endl;
    }
};

void test0() {
    B *b = new B();
    A *aPtr = b; // 用A的指针接收B
    aPtr->print(); // 调用B的print函数
    delete aPtr;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

