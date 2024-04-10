#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>
#include <functional>

using namespace std;

class Test;
using testPtr = shared_ptr<Test>; 
using callback = function<void(const testPtr &test)>;

class Test 
: public enable_shared_from_this<Test>
{
public:
    Test(int age) 
    :_age(age) 
    {

    };
    void print() {
        /* cout << "age = " << age << endl; */
        /* _tt(shared_ptr<Test>(this)); */
        _tt(shared_from_this());
    }
    int getAge() {
        return _age;
    }
    void setCallback(const callback &cb) {
        _tt = cb;
    }
private:
    int _age;
    callback _tt;
};

void test5() {
    Test t1(5);
    auto fuc = [](const testPtr &test){
        cout << "age = " << test->getAge() << endl;
    };
    t1.setCallback(fuc);
    t1.print();
}

void test0() {
    vector<int> vec;
    int a = 10;
    int &b = a;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(20);
    for(const auto & it:vec) {
        cout << it << endl;
    }
}

void test2() {
    vector<Test> vec;
    Test t1(5);
    Test &t2 = t1;
    vec.push_back(t1);
    vec.push_back(t2);
    for(auto & it:vec) {
        cout << it.getAge() << endl;
        /* it.print(); */
    }
}

void test3() {
    /* vector<int &> vec; // 出错 */
}

/* void test4() { */
/*     Test *t1 = new Test(5); */
/*     shared_ptr<Test> sp1 = make_shared<Test>(&t1); */
/*     shared_ptr<Test> sp2 = make_shared<Test>(&t1); */
/*     sp1->print(); */
/*     cout << "------------------" << endl; */
/*     sp2->print(); */
/*     cout << sp2.use_count() << endl; */
/* } */

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    /* test0(); */
    /* test2(); */
    /* test4(); */
    test5();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

