#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <stack>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> _stack;
        if (s.size() % 2 == 1) return false;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == '(')
                _stack.push(')');
            else if (s[i] == '[') 
                _stack.push(']');
            else if (s[i] == '{')
                _stack.push('}');
            else if (!_stack.empty() && _stack.top() == s[i])
                _stack.pop();
            else 
                return false;
        }
        return _stack.empty();
    }
};

void test0() {
    cout << "true:" << true << endl;
    cout << "false:" << false << endl;
    Solution s;
    string word;
    while (cin >> word) {
        bool flag = s.isValid(word);
        cout << word <<  " is " << flag << endl;
    }

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

