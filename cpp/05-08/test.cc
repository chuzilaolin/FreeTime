#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> p1(new int(10));
    std::unique_ptr<int> p2 = std::move(p1);
    std::cout << "p2: " << *p2 << std::endl;
    // std::cout << "p1: " << *p1 << std::endl; // error
    return 0;
}
