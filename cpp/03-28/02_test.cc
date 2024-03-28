#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


void test0() {
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 

    // sort using the default operator<
    std::sort(s.begin(), s.end());
    for (auto a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';

    // sort using a standard library compare function object
    std::sort(s.begin(), s.end(), std::greater<int>());
    for (auto a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';

    // sort using a custom function object
    struct customLess {
        bool operator()(int a, int b) const
        {   
            return a < b;
        }   
    };
    std::sort(s.begin(), s.end(), customLess());
    for (auto a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

