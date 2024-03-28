#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <unordered_set>


using namespace std;

void test() {
    unordered_set<int> us = {1, 4, 5, 4, 8 , 0};
    for (const auto &it : us) {
        cout << it << endl;
    }
    /* cout << us[0] << endl; */
}


void test0() {
    unordered_map<int, string> um = {
        {1, "zs"},
        {2, "ls"},
        {3, "ww"},
        {1, "zl"},
    };
    for (const auto &it : um) {
        cout << it.first << " " << it.second << endl;
    }
    /* cout << um[1].first << " " << um[1].second << endl; */
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    /* test0(); */
    test();
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

