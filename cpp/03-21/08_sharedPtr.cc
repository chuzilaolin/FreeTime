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
    sp->print();
    shared_ptr<Point> sp1 = sp;
    sp1->print();
    sp->print();
    shared_ptr<Point> sp2(sp);
    sp2->print();
}


class Child;
class Parent {
public:
    Parent() {
        cout << "Parent()" << endl;
    }
    ~Parent() {
        cout << "~Parent()" << endl;
    }
    weak_ptr<Child> childSp; 
};

class Child {
public:
    Child() {
        cout << "Child()" << endl;
    }
    ~Child() {
        cout << "~Child()" << endl;
    }
    void print() {
        cout << "I'm Child" << endl;
    }
    weak_ptr<Parent> parentSp;
};
void test1() {
    // shared_ptr<Parent> parentPtr(new Parent());
    // shared_ptr<Child> childPtr(new Child());
    // cout << "parentPtr.use_count(): " << parentPtr.use_count() << endl;
    // cout << "childPtr.use_count(): " << childPtr.use_count() << endl;
    // parentPtr->childSp = childPtr;
    // childPtr->parentSp = parentPtr;
    // cout << "parentPtr.use_count(): " << parentPtr.use_count() << endl;
    // cout << "childPtr.use_count(): " << childPtr.use_count() << endl;

    shared_ptr<Child> childPtr(new Child());
    shared_ptr<Child> childPtr1(childPtr);
    childPtr.get()->print();
    childPtr1.get()->print();

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    // test0();
    test1();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

