#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <iterator>

using namespace std;


void test0() {
    vector<int> vec{1, 4, 8, 3, 2};
    ostream_iterator<int> osi(cout, "\n");
    copy(vec.begin(), vec.end(), osi);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

