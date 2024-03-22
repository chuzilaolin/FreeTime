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

void testUniquePtr1() {
    vector<unique_ptr<Point>> vec;
    vec.push_back(unique_ptr<Point>(new Point(1, 2)));
    vec.pop_back();
    cout << "----------------->\n";
    vec.push_back(unique_ptr<Point>(new Point(2, 3)));
    vec.push_back(unique_ptr<Point>(new Point(1, 7)));
}

void testUniquePtr2() {
    vector<Point*> vec; // 裸指针出现内存泄漏
    vec.push_back(new Point(1, 2));
    vec.push_back(new Point(2, 3));
    vec.push_back(new Point(5, 7));
}

void testUniquePtr3() {
    unique_ptr<Point> up(new Point(1, 7));
    up->print();
    Point *p = up.release();
    p->print();
    delete p;
    cout << "----------------->\n";
    up.reset(new Point(8, 4));
    // up->print();
    up.get()->print();
    unique_ptr<Point> up2(move(up));
    cout << "------xxx----------->\n";
    up2->print();
}

void testUniquePtr4() {
    vector<unique_ptr<Point>> vec;
    unique_ptr<Point> up(new Point(1, 7));
}

void test0() {
    // testUniquePtr1();
    // testUniquePtr2();
    // testUniquePtr3();
    testUniquePtr4();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

