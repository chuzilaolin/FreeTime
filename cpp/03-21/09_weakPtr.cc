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
    shared_ptr<Point> sp(new Point(1, 3));
    weak_ptr<Point> wp(sp);
    wp.use_count();
    shared_ptr<Point> sp1 = wp.lock();
    if (sp1) {  
        sp1->print();
    } else {
        cout << "wp空间已被销毁" << endl;
    }
    wp.reset();

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

