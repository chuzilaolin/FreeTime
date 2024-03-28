#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {

    }
    int get(int key) {

    }
    void put(int key, int value) {

    }
private:
    int _capacity; // 最大容量
    int _size; // 元素个数
    map<int,int> _data;
    
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

