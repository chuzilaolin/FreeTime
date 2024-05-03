#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <workflow/WFFacilities.h>

using namespace std;

void test0() {
        unordered_set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    s.insert(5);
    s.insert(1);
    s.insert(7);
    for (const auto & it : s) {
        cout << it << " ";
    }
    cout << endl;
    string str("c");
    cout << str << endl;
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

