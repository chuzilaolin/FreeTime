#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;


void test0() {
    int a = 0x1234;
    char *b = (char *)&a;
    printf("*b = %x\n", *b); 
}

void test() {
    int a = 0x1234;
    char *b = (char *)&a;
    printf("%x\n",*b);
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    /* test0(); */
    test();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

