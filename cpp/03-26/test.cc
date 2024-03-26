#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void printCapacity(const vector<int> &con)
{
    cout << "size() = " << con.size() << endl;
    cout << "capacity() = " << con.capacity() << endl;
}

class Point {
public:
    Point(int x=0, int y=0) : _x(x), _y(y){
        cout << "Point(int x=0, int y=0)" << endl;
    } 
    Point(const Point &ref) :_x(ref._x) , _y(ref._y) {
        cout << "Point(const Point &ref)" << endl; 
    }
    void print() {
        cout << "x:" << _x << ", y:" << _y << endl;
    }
private:
    int _x;
    int _y;
};

void test1(vector<Point> &vec) {
    // Point p = 3;
    // Point p(2, 2);
    
    // vec.emplace_back(p);
    vec.emplace_back(Point());

    // vec.emplace_back(p1);
    // vec.push_back(p1);
    // vec.push_back((3, 5));
    // p.print();
}

void test()
{
    vector<Point> vec;
    test1(vec);
    cout << "------------------->" << endl;
    vec[0].print();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
