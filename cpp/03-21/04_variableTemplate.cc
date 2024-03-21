#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void print() {
    cout << "end..." << endl;
}

// void print(int x) {
//     cout << x << endl;
// }

template<typename T1, typename ...Args>
void print(T1 x, Args ...args) {
    cout << typeid(x).name() <<  " ---> " << x << endl;
    print(args...);
}

void test0() {
    print(9, "hello", 1, 5.4, 'x');
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

