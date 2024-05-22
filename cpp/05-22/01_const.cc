#include <func.h>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <workflow/WFFacilities.h>

using namespace std;

class Man {
public:
    Man() {}
    Man(int age, string &name) :_age(age), _name(move(name)){}
    friend ostream& operator<<(ostream &out, const Man &man);
    ~Man() {}
private:
    int _age;
    const string _name;
};

ostream& operator<<(ostream &out, const Man &man) {
    out << man._name << ":" << man._age;
    return out;
}

void test0() {
    string str("lg");
    Man man(10, str);
    cout << man << endl;
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

