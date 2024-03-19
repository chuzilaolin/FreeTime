#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class Base {
protected:
    Base(){};
public:
    virtual void print1() {
        cout << "Base -> print1()" << endl;
    }
    virtual void print2();
private:


};

void Base::print2() {
    cout << "Base -> print2()" << endl;
}

class Derive : public Base {
public:
    void print1() override {
        cout << "Derive -> print1()" << endl;
    }
    void print2() override {
        cout << "Derive -> print2()" << endl;
    }
private:

};

void test0() {
     
    Derive d1;
    d1.print1();
    d1.print2();
    d1.Base::print2();
}

int main(void) {
    test0();
    return 0;
}

