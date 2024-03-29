#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


void test0() {
    string a = "zs";
    string b = move(a);

    std::cout << "a: " << a << std::endl; // a 的值已经被转移，可能是未定义的
    std::cout << "b: " << b << std::endl; // b 的值为 5
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

