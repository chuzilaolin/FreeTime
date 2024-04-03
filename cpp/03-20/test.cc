#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <pthread.h>

using namespace std;

class Solution {  
private:  
    vector<int> ans;  
    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up  
    vector<vector<bool>> visited;  
    int m, n;  
    void dfs(vector<vector<int>>& matrix, int x, int y,int index) {  
        if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y]) return;  
        visited[x][y] = true;  
        ans.push_back(matrix[x][y]);  
        int cnt=0;
        for(int k=index;cnt<4;k++)
        {   
            cnt++;
            int nx = x + dirs[k%4][0], ny = y + dirs[k%4][1];  
            dfs(matrix,nx,ny,k);  
        }
    }  
  
public:  
    vector<int> spiralOrder(vector<vector<int>>& matrix) {    
        m = matrix.size();  
        n = matrix[0].size();  
        visited.resize(m, vector<bool>(n, false));  
        dfs(matrix, 0, 0, 0); 
        return ans;  
    }  
};

void test1() {
    pthread_create();
    pthread_join();
    sleep();
        
}

void test0() {
    int m = 4, n = 4;
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

    for (int i = 0; i < m; ++i) {
        for (auto it : matrix[i]) {
            cout << it << " ";
        }
        cout << endl;
    }
    Solution s;
    vector<int> v = s.spiralOrder(matrix);

    for (int num : v) {
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

