#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>

using namespace std;

void test() {
    string str("hello world\n");
    FILE *p = fopen("test.txt", "a+");
    fwrite(str.c_str(), 1, str.size(), p);
    fclose(p);
}

void test0() {
    string str("hello world\n");
    FILE *p = fopen("test.txt", "a+");
    fwrite(str.c_str(), 1, str.size(), p);
    fclose(p);
}

void test1() {
    string str("hello world\n");
    unique_ptr<FILE> up(fopen("test.txt", "a+"));
    fwrite(str.c_str(), 1, str.size(), up.get());
    // fclose(up.get());
}

struct FILECloser {
    void operator()(FILE *p) {
        if (p) {
            fclose(p);
            cout << "fclose(p)" << endl;
        }
    }
};
void test2() {
    string str("hello world\n");
    unique_ptr<FILE, FILECloser> up(fopen("test.txt", "a+"));
    fwrite(str.c_str(), 1, str.size(), up.get());
}



int main(void) {
    auto begin = chrono::high_resolution_clock::now();

    // test();
    // test0();
    // test1();
    test2();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

