#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

void test() {
    string str("hello world\n");
    FILE *p = fopen("test.txt", "a+");
    fwrite(str.c_str(), 1, str.size(), p);
    fclose(p);
}

void test0() {
    char str[] = "hello world\n";
    FILE *p = fopen("test.txt", "ab+");
    fwrite(str, 1, sizeof(str), p);
    fclose(p);
}

void test1() {
    char str[] = "hello world\n";
    FILE *p = fopen("test.txt", "a+");
    fwrite(str, 1, sizeof(str), p);
    fclose(p);
}


int main(void) {
    auto begin = chrono::high_resolution_clock::now();

    test();
    // test0();
    // test1();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

