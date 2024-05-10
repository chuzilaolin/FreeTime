#include <iostream>
#include <unordered_set>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& name, int age) : name(name), age(age) {}

    bool operator==(const Person& other) const {
        /* return (name == other.name) && (age == other.age); */
        std::cout << "-----> Name " << name << " ,age:" << age << " other.age:" << other.age << "\n";
        std::cout << "flag" << (age == (other.age+3) || age == (other.age-3)) << std::endl;
        return (name == other.name) && (age == (other.age+3) || age == (other.age-3));
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age;
        return os;
    }

    friend struct std::hash<Person>;
};

namespace std {
    template<>
    struct hash<Person> {
        size_t operator()(const Person& person) const {
            hash<std::string> hash_fn;
            size_t name_hash = hash_fn(person.name);
            size_t age_hash = hash<int>()(person.age);
            /* return name_hash; */
            return 0;
        }
    };
}

int main() {
    std::unordered_set<Person> uniquePeople;

    uniquePeople.insert(Person("Alice", 25));
    uniquePeople.insert(Person("Bob", 30));
    uniquePeople.insert(Person("Alice", 25));
    uniquePeople.insert(Person("Alice", 28));
    uniquePeople.insert(Person("Alice", 22));
    uniquePeople.insert(Person("Alice", 27));

    for (const auto& person : uniquePeople) {
        std::cout << person << std::endl;
    }

    return 0;
}
