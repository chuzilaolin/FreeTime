#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void print(const vector<int> &vec) {
    cout << "size():" << vec.size() << endl; 
    cout << "capacity():" << vec.capacity() << endl; 
}

void test0() {
    vector<int> vec{10};
    vec.push_back(10);
    print(vec);
    vec.insert(vec.end(), 11);
    print(vec);

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

