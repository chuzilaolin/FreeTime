#include <functional>
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
    vector<int> vec{1, 3, 5, 6, 7, 1, 2};
    print(vec); 
    /* auto it = remove_if(vec.begin(), vec.end(), [](const int a) { */
    /*           return a > 4; */
    /*           }); */
    auto it = remove_if(vec.begin(), vec.end(), bind1st(less<int>(), 4));
    print(vec); 
}

void test1() {
    vector<int> vec{1, 3, 5, 6, 7, 1, 2};
    print(vec); 
    auto it = remove_if(vec.begin(), vec.end(), [](const int a) {
              return a > 4;
              });
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

