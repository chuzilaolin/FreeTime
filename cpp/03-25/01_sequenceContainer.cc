#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <deque>
#include <list>

using namespace std;


void useVector() {
    // 创建容器
    // 1. 无参
    vector<int> vec1;
    vec1.push_back(1);
    // 2. 有参
    vector<int> vec2(3, 1);
    // 3. 迭代器
    int arr[] = {1, 2, 4};
    vector<int> vec3(arr, arr+3);
    // 4. 拷贝构造函数
    vector<int> vec4(vec3);
    // 5. 移动构造函数 
    vector<int> vec5(move(vec3)); 
    // 6. 大括号
    vector<int> vec6 = {1, 4 , 6, 7};
    for (const auto &it : vec6) {
        cout << it << " ";
    }
    cout << endl;
}

void useDeque() {

}

void useList() {

}


void test0() {
    useVector();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

