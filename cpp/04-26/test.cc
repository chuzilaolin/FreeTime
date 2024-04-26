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

using std::cout;
using std::endl;

class Test{
public:
    Test():age(5){
        name = "hello";
    };
    int getAge() const {
        cout << name << endl;
        /* setName(); */
        return age;
    }
    void setName() {
        cout << name << endl;
    }
private:
    std::string name;
    const int age = 10;
};

void test0() {
    Test test;
    cout << test.getAge() << endl;
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

