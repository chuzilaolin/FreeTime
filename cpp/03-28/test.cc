#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


void test0() {
    map<string, string> m = {
        {"zs", "xxx"},
        {"zs", "hhh"},
        {"zs", "bbb"},
        {"ls", "hhh"},
        {"ww", "hhh"},
    };
    for (const auto & it : m) {
        cout << it.first << " " << it.second << endl;
    }
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

