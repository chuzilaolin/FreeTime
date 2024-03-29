#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void print(const vector<int> &vec) {
    for (const auto &it : vec) {
        cout << it << " ";
    }
    cout << endl;
}

void test0() {
    vector<int> vec{1, 3, 5, 7, 9};
    auto it1 = vec.begin();
    it1++;
    it1++;
    cout << *it1 << endl;
    auto it2 = vec.erase(it1);
    cout << *it2 << endl;
}

void test1() {
    vector<int> vec{1, 3, 5, 7, 9};
    print(vec);
    auto it1 = vec.begin();
    for (;it1 != vec.end();) {
        it1 = vec.erase(it1);
    }
    print(vec);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test1();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

