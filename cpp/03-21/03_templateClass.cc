#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

template <typename T>
class Point {
public:
    Point(double x, double y) : _x(x), _y(y) {}
    T convertX();
    T convertY();
    void print(); 
private:
    double _x;
    double _y;
};

template <typename T>
T Point<T>::convertX() {
    return _x;
}

template <typename T>
T Point<T>::convertY() {
    return _y;
}

template<typename T>
void Point<T>::print() {
    cout << "_x=" << _x << ", _y=" << _y << endl;
}


void test0() {
    Point<int> p(3.14, 2.76);
    p.print();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

