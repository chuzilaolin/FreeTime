#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class Test {
public:
    Test(int age) :age(age) {};
    void print() {
        cout << "age =" << age << endl;
    }
    int age;
};


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
    for(const auto & it:vec) {
        cout << it.age << endl;
    }
}

void test3() {
    /* vector<int &> vec; // 出错 */
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    /* test0(); */
    test2();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

