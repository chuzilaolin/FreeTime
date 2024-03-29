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
        if (s.empty()) {
            return true;
        } 
        if (s.size() % 2 == 1) return false;
        stack<char> _stack;
        for (int i = 0; i < s.size(); ++i) {
            // 遇到左括号就入栈
            if (leftBrack.find(s[i]) != leftBrack.end()) {
                // 处理一下,存入右括号,弹栈时直接对比
                _stack.push(modifyToR(s[i]));   
            }
            // 遇到右括号就弹栈
            if (rightBrack.find(s[i]) != rightBrack.end()) {
                if (_stack.empty()) return false; // 判断一下如果没有左括号,直接错误 
                char c = _stack.top();
                _stack.pop();
                if (c != s[i]) return false; // 不匹配
            }
        }
        cout << "size:" << _stack.size() << endl;
        cout << "empty?:" << _stack.empty() << endl;
        return _stack.empty();
    }
private:
    unordered_set<char> leftBrack{'(', '[', '{'};
    unordered_set<char> rightBrack{')', ']', '}'};
    char modifyToR(char c) {
        if (c == '(') return ')';
        if (c == '[') return ']';
        if (c == '{') return '}';
        return c;
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

