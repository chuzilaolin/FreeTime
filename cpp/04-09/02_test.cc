#include <iostream>
#include <memory>
#include <functional>

using namespace std;

class Test;
using testPtr = shared_ptr<Test>; 
using callback = function<void(const testPtr &test)>;

class Test 
: public enable_shared_from_this<Test>
{
public:
    Test()
    : _data(new char[1])
    {
        cout << "Test(int age)" << endl;
    };
    ~Test() {
        cout << "~Test()" << endl;
        delete[] _data;
    }
    void executeCallback() {
        /* _cb(this); // 编译不通过 */
        /* _cb(shared_ptr<Test>(this)); // 造成析构函数调用两次 */
        _cb(shared_from_this());
    }
    void setCallback(const callback &cb) {
        _cb = cb;
    }
private:
    callback _cb;
    char *_data;
};

int main() {
    shared_ptr<Test> t1(new Test());
    auto func = [](const testPtr &test){
        cout << "execute callback ...." << endl;
    };
    t1->setCallback(func);
    t1->executeCallback();
    return 0;
}

