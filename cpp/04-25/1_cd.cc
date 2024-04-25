#include <func.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <utility>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <workflow/WFFacilities.h>
#include <stack>

using namespace std;

class CD {
public:
    CD() {
        _stack.push_back("/");
    }
    // 进入下一次目录
    int nextDir(string nextDirName) {
        _stack.push_back(nextDirName);

        return 0;
    }
    // 返回上一层目录
    int preDir() {
        if (_stack.size() == 1) {
            cout << "当前已经在根目录！";
            return -1;
        }
        _stack.pop_back();
        return 0;
    }
    // 获取当前目录
    string pwd() {
        string pwdStr = "/";
        for (vector<string>::iterator it = _stack.begin() + 1; it != _stack.end(); ++it) {
            pwdStr.append(*it).append("/");
        }
        /* return move(pwdStr.substr(0, pwdStr.size()-1)); */
        return move(pwdStr);
    }

private:
    vector<string> _stack;
};

string &getName() {
    string name = "nuitom";
    return ref(name);
}
string getName1() {
    string name = "nuitom";
    /* return name; */
    return move(name);
}

void test() {
    string name = "lg";
    string &ref1 = name;
    string &ref2 = ref(name);
    cout << "ref1:" << ref1 << endl;
    cout << "ref2:" << ref2 << endl;
    cout << "getName():" << getName() << endl;
    cout << "getName1():" << getName1() << endl;
}

void test0() {
    CD cd;
    cout << cd.nextDir("dir1") << endl;
    cout << cd.nextDir("dir2") << endl;
    cout << "当前路径为：" << cd.pwd() << endl;
    cout << cd.preDir() << endl;
    cout << cd.preDir() << endl;
    cout << cd.preDir() << endl;
    cout << cd.preDir() << endl;
    test();
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

