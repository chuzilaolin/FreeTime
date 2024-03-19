#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

bool stringMatch(double k, const string &a, const string &b) {
    if (a.length() == 0 || b.length() == 0) {
        return false;
    }
    int count = 0; 
    for (int i = 0; i < a.length(); i++) { // a和b长度相等，所以只判断a
        if (a[i] == b[i]) {
            ++count;
        }
    }
    return k <= (count * 1.0 / a.length());
}

void test0() {
    double k;
    string a, b;
    cin >> k;
    cin >> a;
    cin >> b;
    cout << (stringMatch(k, a, b) ? "yes" : "no") << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

