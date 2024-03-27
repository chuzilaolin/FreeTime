#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


template<typename T, typename Compare = less<T>>
class HeapSort {
public:
    HeapSort(T *arr, size_t size) : _vec(arr, arr + size) ,_cmp(Compare()) {};
    // 排序
    void sort() {
        int heapLen = _vec.size();
        // 1. 建堆
        // 找到最后一个非叶子节点 2i+1 <= len -1 ==> i <= len-2 >> 1
        int nonLeafNodeIdx = (heapLen - 2) >> 1;
        // 循环堆化
        for (int i = nonLeafNodeIdx; i >= 0; --i) {
            heapify(heapLen, i);
        }
        // 2. 循环取根并堆化
        while (heapLen > 1) {
            swap(_vec[0], _vec[heapLen - 1]);
            heapify(--heapLen, 0);
        }   
    }
    void print() {
        for (const auto &it : _vec) {
            cout << it << " ";
        } 
    cout << endl;
    }
private:
    // 堆化
    void heapify(int heapLen, int idx) {
        while (true) {
            int maxIdx = idx; // 默认设要堆化的结点为最大的下标
            int leftIdx = idx * 2 + 1;
            int rightIdx = idx * 2 + 2;
            if (leftIdx < heapLen && _cmp(_vec[maxIdx], _vec[leftIdx])) {
                maxIdx = leftIdx;
            }
            if (rightIdx < heapLen && _cmp(_vec[maxIdx], _vec[rightIdx])) {
                maxIdx = rightIdx;
            }
            if (maxIdx == idx) {
                break; // 说明不需要堆化
            }else {
                swap(_vec[idx], _vec[maxIdx]);
                idx = maxIdx;
            }
        }
    }
    vector<T> _vec;
    Compare _cmp;
};


void test0() {
    int arr[] = {7, 2, 4, 1, 9, 5};
    /* HeapSort<int, greater<int>> hs(arr, 6); */
    HeapSort<int> hs(arr, 6);
    hs.print();
    hs.sort();
    hs.print();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

