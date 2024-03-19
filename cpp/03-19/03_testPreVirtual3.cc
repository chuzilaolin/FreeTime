#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

class Base {
public:
    Base(const char *name) : _name(new char[strlen(name) + 1]()) {
        cout << "Base(const char *name)" << endl;
        strcpy(_name, name);
    }
    virtual void print1() {
        cout << "Base -> print1()" << endl;
    }
    virtual void print2() = 0;
    virtual ~Base() {
        delete [] _name;
        cout << "~Base()" << endl;
    }
private:
    char *_name;
};

void Base::print2() {
    cout << "Base -> print2()" << endl;
}

class Derive : public Base {
public:
    Derive(const char *name, const char *sex) 
    : Base(name) 
    , _sex(new char[strlen(sex) + 1])
    {
        cout << "Derive(const char *name)" << endl;
        strcpy(_sex, sex);
    }
    void print1() override {
        cout << "Derive -> print1()" << endl;
    }
    void print2() override {
        cout << "Derive -> print2()" << endl;
    }
    ~Derive() {
        delete [] _sex;
        cout << "~Derive()" << endl; 
    }
private:
    char *_sex;
};

void test0() {
    // Derive d1("tom", "man");
    // d1.print1();
    // d1.print2();
    // d1.Base::print2();

    Base *p2 = new Derive("jeck", "manxxxxxkkk");
    p2->print1();
    p2->print2();
    delete p2;
}

int main(void) {
    test0();
    return 0;
}

