#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return _res;
        }
        // 上下左右边界
        int up = 0;
        int down = matrix.size() - 1;
        int left = 0;
        int right = matrix[1].size() -1;
        // 沿着右、下、左、上的方向循环移动
        while(true) {
            for (int i = left; i <= right; ++i) { // 向右移动到边界处
                _res.push_back(matrix[up][i]);
            }
            if (++up > down) break; // 更新上边界并判断是否越界
            for (int i = up; i <= down; ++i) { // 向下移动到边界处
                _res.push_back(matrix[i][right]);
            }
            if (--right < left) break; // 更新右边界并判断是否越界
            for (int i = right; i >= left; --i) { // 向左移动到边界处
                _res.push_back(matrix[down][i]);
            }
            if (--down < up) break; // 更新下边界并判断是否越界
            for (int i = down; i >= up; --i) { // 向上移动到边界处
                _res.push_back(matrix[i][left]);
            }
            if (++left > right) break; // 更新左边界并判断是否越界 
        }
        return _res;
    }
private:
    vector<int> _res;
};

void test0() {
    int m = 3, n = 3;
    vector<vector<int>> matrix;
    int num = 1;
    for (int i = 0; i < m; ++i) {
        vector<int> rows;
        for (int j = 0; j < n; ++j) {
            rows.push_back(num); 
            ++num;
        }
        matrix.push_back(rows);
    }

    for (const auto &it: matrix) {
        for (int num : it) {
            printf("%3d", num);
        }
        cout << endl;
    }
    cout << endl;

    Solution s;
    vector<int> ans = s.spiralOrder(matrix);

    cout << endl;
    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

