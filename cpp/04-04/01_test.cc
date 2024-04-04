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

class Product {
public:
    virtual void show() = 0;
    virtual ~Product(){
        cout << "Product::~Product()" << endl; 
    }
};

class ProductA 
: public Product 
{
public: 
    void show() {
        cout << "ProductA::show()" << endl;
    }
    ~ProductA() {
        cout << "ProductA::~ProductA()" << endl;
    }
};

class ProductB 
: public Product 
{
public: 
    void show() {
        cout << "ProductB::show()" << endl;
    }
    ~ProductB() {
        cout << "ProductB::~ProductB()" << endl;
    }
};

class Factory {
public:
    virtual unique_ptr<Product> createProduct() = 0;
    virtual ~Factory() {
        cout << "Factory::~Factory()" << endl;
    }
};

class FactoryA 
: public Factory 
{
public:
    unique_ptr<Product> createProduct() {
        return unique_ptr<Product>(new ProductA);
    }
    ~FactoryA() {
        cout << "FactoryA::~FactoryA()" << endl;
    }
};


class FactoryB 
: public Factory 
{
public:
    unique_ptr<Product> createProduct() {
        return unique_ptr<Product>(new ProductB);
    }
    ~FactoryB() {
        cout << "FactoryB::~FactoryB()" << endl;
    }
};

void test0() {
    unique_ptr<Factory> factoryA(new FactoryA()); 
    unique_ptr<Product> productA = factoryA->createProduct();
    productA->show();
    cout << "--------------------" << endl;
    unique_ptr<Factory> factoryB(new FactoryB()); 
    unique_ptr<Product> productB = factoryB->createProduct();
    productB->show();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

