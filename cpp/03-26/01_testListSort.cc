#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <list>

using namespace std;

class Point {
    friend bool operator<(const Point &lhs, const Point &rhs);
public:
    Point(int x=0, int y=0) : _x(x), _y(y){
    } 
    Point(const Point &ref) :_x(ref._x) , _y(ref._y) {
    }
    void print() const {
        cout << "x:" << _x << ", y:" << _y << endl;
    }

private:
    int _x;
    int _y;
};

bool operator<(const Point &lhs, const Point &rhs) {
    return (lhs._x + lhs._y) < (rhs._x + rhs._y);    
}

void test0() {
    list<Point> points;
    Point p1(1, 3);
    Point p2(2, 5);
    Point p3(1, 1);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    for (const auto &it : points) {
        it.print();
    }
    cout << "---------------->" << endl;
   /* points.sort(); */
   /*  for (const auto &it : points) { */
   /*      it.print(); */
   /*  } */
    list<Point> points2;
    Point p4(1, 3);
    Point p5(2, 5);
    Point p6(7, 1);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    
    cout << (points > points2) << endl;
}
    
int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}










