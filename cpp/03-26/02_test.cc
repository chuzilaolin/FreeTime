#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <list>

using namespace std;


void test0() {

    list<int> lst;
    list<int>::iterator iter1 = lst.begin(), iter2 = lst.end();
    while(iter1 != iter2)
    {
        //....
        cout << "------" << endl;
    }
    cout << "end..." << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

