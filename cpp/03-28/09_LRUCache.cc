#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) :_capacity(capacity) ,_size(0) {
        if (capacity <= 0) { // 处理非法初始值
            capacity = 10;
        }
    }
    ~LRUCache() {
        _hashTable.clear();
        cout << "~LRUCache()" << endl;
        /* _recentData.clear(); */
    }
    int get(int key) {
        auto search = _hashTable.find(key);
        if (search == _hashTable.end()) {
            return -1;
        }
        // 获取数据
        auto it = _hashTable[key];
        int value = it->second;
        // 更新队列
        _recentData.splice(_recentData.begin(), _recentData, it, ++it);
        _hashTable[key] = _recentData.begin();
        return value;
    }
    void put(int key, int value) {
        // 判断是否存在
        auto search = _hashTable.find(key);
        if (search != _hashTable.end()) {
            // 更新值
            _hashTable[key]->second = value;
        } else {
            // 判断是否超出容量
            if (_size >= _capacity) {
                auto end = _recentData.end(); // 获取末尾的迭代器
                end--;
                _hashTable.erase(end->first); // 在hashtable里删除
                _recentData.erase(end); // 在队列里删除
                --_size; 
            }
            // 插入新数据
            _recentData.push_front({key,value});
            _hashTable[key] = _recentData.begin();
            ++_size;
        }
    }
private:
    int _capacity; // 最大容量
    int _size; // 元素个数
    list<pair<int, int>> _recentData; // 存放实际数据的队列
    unordered_map<int, list<pair<int, int>>::iterator> _hashTable; // 用于O(1)查询hash表
};


void test0() {
    LRUCache *lru = new LRUCache(2); 
    /* lru->put(1,1); */
    /* cout << lru->get(1) << endl; */
    /* lru->put(1,3); */
    /* cout << lru->get(1) << endl; */
    /* cout << "----------------->" << endl; */

    lru->put(1,1);
    lru->put(2,2);
    cout << lru->get(1) << endl;
    lru->put(3,3);
    cout << lru->get(2) << endl;
    lru->put(4,4);
    cout << lru->get(1) << endl;
    cout << lru->get(3) << endl;
    cout << lru->get(4) << endl;
    delete lru;
}

void test1() {
    LRUCache *lru = new LRUCache(2); 
    lru->put(2,1);
    cout << lru->get(2) << endl;
    delete lru;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test1();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

