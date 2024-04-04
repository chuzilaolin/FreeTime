/**
 * 工厂方法模式
 */
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>

using namespace std;

class ProductA {
public:
    virtual void show() = 0;
    virtual ~ProductA(){}
};

class ProductA1
: public ProductA
{
public: 
    void show() {
        cout << "ProductA1::show()" << endl;
    }
};

class ProductA2
: public ProductA 
{
public: 
    void show() {
        cout << "ProductA2::show()" << endl;
    }
};

class ProductB {
public:
    virtual void show() = 0;
    virtual ~ProductB(){}
};

class ProductB1
: public ProductB
{
public: 
    void show() {
        cout << "ProductB1::show()" << endl;
    }
};

class ProductB2
: public ProductB 
{
public: 
    void show() {
        cout << "ProductB2::show()" << endl;
    }
};

class Factory {
public:
    virtual unique_ptr<ProductA> createProductA() = 0;
    virtual unique_ptr<ProductB> createProductB() = 0;
    virtual ~Factory() {
        cout << "Factory::~Factory()" << endl;
    }
};

class Factory1
: public Factory 
{
public:
    unique_ptr<ProductA> createProductA() {
        return unique_ptr<ProductA>(new ProductA1);
    }
    unique_ptr<ProductB> createProductB() {
        return unique_ptr<ProductB>(new ProductB1);
    }
    ~Factory1() {
        cout << "Factory1::~Factory1()" << endl;
    }
};

class Factory2
: public Factory 
{
public:
    unique_ptr<ProductA> createProductA() {
        return unique_ptr<ProductA>(new ProductA2);
    }
    unique_ptr<ProductB> createProductB() {
        return unique_ptr<ProductB>(new ProductB2);
    }
    ~Factory2() {
        cout << "Factory2::~Factory2()" << endl;
    }
};


void test0() {
    unique_ptr<Factory> factory1(new Factory1()); 
    unique_ptr<ProductA> productA = factory1->createProductA();
    unique_ptr<ProductB> productB = factory1->createProductB();
    productA->show();
    productB->show();
    cout << "--------------------" << endl;
    unique_ptr<Factory> factory2(new Factory2()); 
    unique_ptr<ProductA> productA2 = factory2->createProductA();
    unique_ptr<ProductB> productB2 = factory2->createProductB();
    productA2->show();
    productB2->show();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

