#include <cstring>
#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <workflow/WFFacilities.h>

using namespace std;

void test0() {
    ofstream ofs("1.txt");
    string str = "hello";
    cout << "str.length() = " << str.length() << endl;
    cout << "str.size() = " << str.size() << endl;
    const char *c_str = str.c_str();
    cout << "str.c_str() = " << strlen(c_str) << endl;
    ofs << str;
    ofs.close();
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

