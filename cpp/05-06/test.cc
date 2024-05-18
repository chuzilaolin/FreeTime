#include <iostream>
#include <set>
#include <string>

using namespace std;

class Person {
public:
    Person(int age, const std::string& name) : age_(age), name_(name) {}
    
    // 如果两个值相差3,就认为相等
    bool isEqual(int left, int right) const {
        bool flag = true;
        flag = (left == (right + 3) || left == (right - 3));
        cout << "-----------> left=" << left << ", right=" << right << ", flag=" << flag << endl;
        return flag;
    }
    // 重载小于运算符
    bool operator<(const Person& other) const {
        bool flag = (age_ == other.age_);
        cout << name_ << ":" << age_ << " --- " << other.name_ << ":" << other.age_ << ", flag = " << flag << endl;
        if (flag) { // 如果年龄相同，再比较名称
            return name_ < other.name_;
        }
        return age_ < other.age_;
    }

    int getAge() const { return age_; }
    const std::string& getName() const { return name_; }
private:
    int age_;
    std::string name_;
};

int main() {
    std::set<Person> personSet;

    // 向集合中插入元素，自动去重
    personSet.insert(Person(25, "A"));
    personSet.insert(Person(28, "A")); // 相差3,能插入
    personSet.insert(Person(27, "A")); // 插入不了

    // 输出集合中的元素
    /* std::cout << "Set contains:\n"; */
    for (const auto& person : personSet) {
        std::cout << "Age: " << person.getAge() << ", Name: " << person.getName() << std::endl;
    }

    return 0;
}

