#include <iostream>
#include <memory>
#include <functional>

using namespace std;

class Test;
/**
 * 一个参数为shared_ptr<Test>的普通函数
*/
void func(const shared_ptr<Test> &test){
    cout << "execute callback ...." << endl;
};

class Test 
: public enable_shared_from_this<Test>
{
public:
    Test()
    : _data(new char[1])
    {
        cout << "Test()" << endl;
    };
    ~Test() {
        cout << "~Test()" << endl;
        delete[] _data;
    }
    /**
    * 一个把类对象作为参数传递的成员函数
    */
    void test() {
        /* func(this); // 编译不通过 */
        /* func(shared_ptr<Test>(this)); // 造成析构函数调用两次 */
        func(shared_from_this());
    }
private:
    char *_data;
};

void test1() {
    shared_ptr<Test> t1(new Test());
    /* t1->test(); */
    cout << "此时的引用计数为:" << t1.use_count() << endl;
    shared_ptr<Test> t2 = t1;
    cout << "此时的引用计数为:" << t1.use_count() << endl;
    shared_ptr<Test> t3(t1);
    cout << "此时的引用计数为:" << t1.use_count() << endl;
    shared_ptr<Test> t4(t1.get());
    cout << "此时的引用计数为:" << t1.use_count() << endl;
}

void test2() {
    Test *pt = new Test();
    shared_ptr<Test> sp(pt);
}

void test3() {
    Test pt;
    shared_ptr<Test> sp(&pt);
}

int main() {
    /* test1(); */
    test3();
    cout << "end...." << endl;
    return 0;
}











