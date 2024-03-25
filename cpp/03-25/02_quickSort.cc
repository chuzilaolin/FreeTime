#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


template<typename T, typename Compare = less<T>>
class MyQsort {
public:
    MyQsort(T *arr, size_t size, Compare com);
    void quick(int left, int right, Compare &com);
    int partition(int left, int right, Compare &com);
    void print();
private:
    vector<T> vec;
};


void test0() {

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

