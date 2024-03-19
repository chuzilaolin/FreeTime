#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
using namespace std;


class Person {
public:
    Person(const char *name, int age) 
    : _name(new char[strlen(name) + 1]())
    , _age(age) {
        strcpy(_name, name);
        cout << "Person->带参构造函数" << endl;
    }
    Person(const Person &other)
    : _name(new char[strlen(other._name) + 1]())
    , _age(other._age){
        strcpy(_name, other._name);
        cout << "Person->拷贝构造函数" << endl;
    }
    Person &operator=(const Person &other) {
        cout << "Person->赋值运算符函数" << endl;
        if (this != &other) { // 跳过自赋值
            delete [] this->_name;
            this->_name = new char[strlen(other._name) + 1]();
            strcpy(this->_name, other._name);
            _age = other._age;
        }
        return *this; 
    } 
    virtual ~Person() {
        delete [] _name;
        cout << "~Person()" << endl;
    }
    virtual void display() {
        cout << "name: " << _name << ", age: " << _age;
    }
private:
    char *_name;
    int _age; 
};

class Employee : public Person {
public:
    Employee(const char *name, int age, const char *department, double salary) 
    : Person(name, age)
    , _department(new char[strlen(department) + 1]()) 
    , _salary(salary) {
        cout << "Employee->带参构造函数" << endl;
        strcpy(_department, department);
    }
    Employee(const Employee &other)
    : Person(other)
    , _department(new char[strlen(other._department) + 1])
    , _salary(other._salary) {
        cout << "Employee->拷贝构造函数" << endl;
        delete[] _department;
        _department = new char[strlen(other._department) + 1]();
        strcpy(_department, other._department);
    }
    Employee &operator=(const Employee &other) {
        cout << "Employee->赋值运算符函数" << endl;
        if (this != &other) {
            delete [] this->_department;
            this->_department = new char[strlen(other._department) + 1]();
            strcpy(this->_department, other._department);
            this->_salary = other._salary;
            // 赋值基类元素
            Person::operator=(other); 
        }
        return *this;
    }
    double getSalary() {
        return _salary;
    }
    void display() override {
        this->Person::display();
        cout << fixed << setprecision(2) << ", department: " << _department << ", salary: " << _salary << endl;
    }
    ~Employee() {
        delete [] _department;
        cout << "~Employee()" << endl;
    }
private:
    char *_department;
    double _salary;
};

double getAverageSalary(vector<double> salarys) {
    double total = 0;
    for (const auto &it : salarys) {
        total += it;
    }
    return total / salarys.size();
}


void test0() {
    vector<double> salarys;
    Employee *e1 = new Employee("zs", 18, "tech", 18230.48);
    e1->display();
    salarys.push_back(e1->getSalary());

    // Employee e2(*e1);
    // Employee e2 = *e1;
    Employee e2("ls", 19, "tech", 19181.24);
    e2 = *e1;
    delete e1;
    e2.display();
    salarys.push_back(e2.getSalary());

    Employee e3("ww", 23, "moyu", 38178.9);
    e3.display();
    salarys.push_back(e3.getSalary());
    cout << "average salary: " << fixed << setprecision(2) << getAverageSalary(salarys) << endl;
}

int main(void) {
    test0();
    return 0;
}

