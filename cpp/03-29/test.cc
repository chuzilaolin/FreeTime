#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
public:
    LRUCache(const int &capacity)
        : _capacity(capacity)
          , _list(make_shared<list<pair<int, int>>>())
          , _map(make_shared<unordered_map<int, list<pair<int,int>>::iterator>>())
    {}
    int get(int key){
        if(_map->find(key) != _map->end() && (*_map)[key] != _list->end()){
            //更新链表节点
            pair<int, int> tmp;
            tmp = *(*_map)[key];
            //删除后移到尾部
            _list->erase((*_map)[key]);
            _list->push_back(tmp);
            (*_map)[key] = prev(_list->end());
            return (*_map)[key]->second;
        }else{
            return -1;
        }
    }
    void put(int key, int value){
       if(_map->find(key) != _map->end()){
            //判断元素是否存在
            //存在，但迭代器在_list尾部，需要从新插入；
            //存在，迭代器不在尾部，更新元素内容；
            get(key);
            if((*_map)[key] != _list->end()){
                *(*_map)[key] = {key, value};
            }else{
                //更新头部节点的_map位置；
                //删除头部节点
                (*_map)[_list->begin()->first] = _list->end();
                _list->pop_front();
                _list->push_back({key, value});
                (*_map)[key] = prev(_list->end());
            }
        }else{
            //插入节点逻辑
            //不存在
            if(_list->size() < _capacity){
                _list->push_back({key, value});
                (*_map)[key] = prev(_list->end());
            }else{
                (*_map)[_list->begin()->first] = _list->end();
                _list->pop_front();
                _list->push_back({key, value});
                (*_map)[key] = prev(_list->end());
            }
        }
    }
private:
    int _capacity;
    shared_ptr<list<pair<int,int>>> _list;
    shared_ptr<unordered_map<int, list<pair<int,int>>::iterator>> _map;
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

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

