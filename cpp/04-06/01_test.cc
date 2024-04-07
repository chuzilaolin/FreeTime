#include <iostream>
#include <functional>

using namespace std;

class Demo {
public:
    Demo(){
        cout << "Demo()" << endl;       
    }
    ~Demo() {
        cout << "~Demo()" << endl;
    }
    Demo(Demo &&rhs) {
        cout << "Demo(Demo &&rhs)" << endl;
    }

private:
    int age;
};

void print(int& x) {
    std::cout << "Value: " << x << std::endl;
}

void test1() {
    int num = 10;

    // 使用 std::ref 将 num 的引用传递给函数
    std::reference_wrapper<int> ref_num = std::ref(num);

    // 使用函数对象
    print(ref_num);

    // 修改原始对象的值
    num = 20;

    // 再次调用函数，将看到修改后的值
    print(ref_num);

    int a = 9;
    print(a);
}

void print1(Demo &demo) {
    cout << "print1() is running" << endl;
}

void test2() {
    Demo d1;
    reference_wrapper<Demo> ref_demo = ref(d1);
    print1(ref_demo);
}

void test3() {
    Demo d1;
    print1(d1);
}

void test4() {
    Demo d1;
    print1(ref(d1));
}

int main() {
    /* test1(); */
    /* test2(); */
    // test3();
    test4();
    return 0;
}

