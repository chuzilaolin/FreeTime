#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class Base
{
public:
    virtual void print()
    {
        cout << "Base::print()" << endl;
    }
    virtual void display()
    {
        cout << "Base::display()" << endl;
    }
    virtual void show()
    {
        cout << "Base::show()" << endl;
    }

private:
    long _base = 10;
};

class Derived
    : public Base
{
public:
    virtual void print()
    {
        cout << "Derived::print()" << endl;
    }
    virtual void display()
    {
        cout << "Derived::display()" << endl;
    }
    virtual void show()
    {
        cout << "Derived::show()" << endl;
    }
    void test() {
        cout << "Derived::test()" << endl;
    }

private:
    long _derived = 100;
};


void test0() {
    Derived d;
    long *pDerived = reinterpret_cast<long*>(&d);
    cout << pDerived[0] << endl;
    cout << pDerived[1] << endl;
    cout << pDerived[2] << endl;
    // cout << pDerived[3] << endl;
    // typedef void (Derived::*Func)();
    // Func f = &Derived::test;
    // (d.*f)(); 
    long *pVtable = reinterpret_cast<long*>(pDerived[0]);
    
    typedef void (*Func)();
    Func f = reinterpret_cast<Func>(pVtable[0]);
    f();
    f = reinterpret_cast<Func>(pVtable[1]);
    f();
    f = (Func)pVtable[2];
    f();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

