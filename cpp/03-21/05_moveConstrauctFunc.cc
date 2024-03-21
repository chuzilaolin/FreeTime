#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class Point {
public:
    Point(double x, double y) : _x(x), _y(y) {
        cout << "Point(double x, double y)" << endl;
    } 
    Point(const Point &other) : _x(other._x), _y(other._y) {
        cout << "Point(const Point &other)" << endl;
    }
    Point(Point &&other) : _x(other._x), _y(other._y) {
        cout << "Point(Point &&other)" << endl;
    }
    void print() {
        cout << "_x=" << _x << ", _y=" << _y << endl;
    }
    ~Point() {
        cout << "~Point()" << endl;
    }
private:
    double _x;
    double _y;
};

template<typename T1, int _num>
T1 print(T1 a) {
    return a + 10 + _num; 
}


Point func1() {
    Point p(7, 2);
    cout << "&p:" << &p << endl;;
    return p;
}

void test0() {
    // cout << print<int, 5>(10) << endl;
    Point p1(3, 4);
    cout << "&p1:" << &p1 << endl;;
    Point p2 = p1;
    cout << "&p2:" << &p2 << endl;;
    Point p3(p1);
    cout << "&p3:" << &p3 << endl;;
    Point p4 = move(p1);
    cout << "&p4:" << &p4 << endl;;
    cout << "---------->" << endl;
    Point &&p5 = func1();
    cout << "---------->" << endl;
    cout << "&p5:" << &p5 << endl;;
    cout << endl << endl << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

