#include <iostream>
#include <set>
#include <string>

using namespace std;

class Person {
public:
    Person(int age, const std::string& name) : age_(age), name_(name) {}

    // 定义比较运算符来使对象可比较
    /* bool operator<(const Person& other) const { */
    /*     // 首先按照年龄比较 */
    /*     if (age_ < other.age_) */
    /*         return true; */
    /*     else if (age_ > other.age_) */
    /*         return false; */
    /*     // 如果年龄相同，则按照姓名比较 */
    /*     return name_ < other.name_; */
    /* } */
    bool operator<(const Person& other) const {
        bool flag = (age_ == other.age_);
        cout << name_ << ":" << age_ << " --- " << other.name_ << ":" << other.age_ << ", flag = " << flag << endl;
        if (flag) { // 如果年龄相同，再比较名称
            return name_ < other.name_;
        }
        return age_ < other.age_;
    }

    int getAge() const {
        return age_;
    }

    const std::string& getName() const {
        return name_;
    }

private:
    int age_;
    std::string name_;
};

int main() {
    std::set<Person> personSet;

    // 向集合中插入元素，自动去重
    personSet.insert(Person(25, "Alice"));
    personSet.insert(Person(25, "Alice1"));
    personSet.insert(Person(25, "lg"));
    personSet.insert(Person(30, "Bob"));
    personSet.insert(Person(25, "Alice")); // 这个元素会被忽略，因为已经存在一个年龄为25、姓名为"Alice"的元素

    // 输出集合中的元素
    std::cout << "Set contains:\n";
    for (const auto& person : personSet) {
        std::cout << "Age: " << person.getAge() << ", Name: " << person.getName() << std::endl;
    }

    return 0;
}

