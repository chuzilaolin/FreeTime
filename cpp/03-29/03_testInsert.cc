#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <list>

using namespace std;


void test0() {
    list<int> vec1{5, 6, 7, 8, 9};
    list<int> vec2{1, 2, 3};

    /* vec1.insert(vec1.begin(), vec2.begin(), vec2.end()); */

    /* copy(vec2.begin(), vec2.end(), front_inserter(vec1)); */
    copy(vec2.begin(), vec2.end(), front_insert_iterator<list<int>>(vec1));


    copy(vec1.begin(), vec1.end(), ostream_iterator<int>(cout, " "));
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

