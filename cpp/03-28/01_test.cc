#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

struct Point{
    int age;
    string name;
    void print() const {
        cout << name << ", " << age << endl;
    }
};

Point test() {
    Point p;
    p.age = 18;
    p.name = "zs";
    return p;
}

void test0() {
    const Point &p = test();
    p.print();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

