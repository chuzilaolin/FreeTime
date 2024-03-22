#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstring>

using namespace std;

class String {
public:
    String(const char *str) : _str(new char[strlen(str) + 1]) {
        strcpy(_str, str);
        cout << "String(const char *str)" << endl;
    }
    String &operator=(const char *str) {
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
        cout << "String &operator=(const char *str)" << endl;
        return *this;
    }
    String(String &&other) :_str(other._str) {
        cout << "String(String &&other) " << endl;
        other._str = nullptr;
    }
    String &operator=(String &&other) {
        cout << "String &operator=(String &&other)" << endl;
        if (this != &other) {
            delete [] _str;
            _str = other._str;
            other._str = nullptr;
        }
        return *this;
    }
private:
    char *_str;
};

void test0() {
    String str1("tom");
    String str2 = "jeck";
    str2 = "niqiu";
    String str3 = move(str2);
    str3 = move(str1);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

