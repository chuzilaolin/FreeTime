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
    istream_iterator<int> isi(cin);
    vector<int> vec;
    copy(isi, istream_iterator<int>(), back_inserter(vec));
    cout << "--------" << endl;
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, "\n"));
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

