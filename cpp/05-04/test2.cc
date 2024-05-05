#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <workflow/WFFacilities.h>

using namespace std;

void test0() {
    vector<string> vec = {"zs", "ls", "ww"}; 
    for (const string &it : vec) {
        cout << &it << ":" << it << endl;
    }
    string name;
    string &&ref = move(vec[0]);
    name = move(ref);
    cout << "name = " << name << endl;
    for (const string &it : vec) {
        cout << &it << ":" << it << endl;
    }
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

