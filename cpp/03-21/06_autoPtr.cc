#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>

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

void test0() {
    Point *p1 = new Point(3, 4);
    auto_ptr<Point> ap1(p1);  
    ap1->print();
    auto_ptr<Point> ap2(ap1);
    ap2->print();
    ap1->print(); // 段错误
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

