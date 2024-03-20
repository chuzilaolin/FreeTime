#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int res[100][10];

void test1(int m, int n)
{
//     int n, m;
//     cin >> n >> m;
    //定义0为(0,1) 向右走
    //定义1为(1,0) 向下走
    //定义2为(0,-1)向左走
    //定义3为(-1, 0)向上走
    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

    for (int x = 0, y = 0, d = 0, k = 1; k <= n * m; k ++ )
    {
        res[x][y] = k;
        int a = x + dx[d], b = y + dy[d]; //下个方向的下标
        if (a < 0 || a >= n || b < 0 || b >= m || res[a][b])//判断撞墙
        {
            d = (d + 1) % 4; //转向，每次转向的变化是d=0>1>2>3>0>1>2>3
            a = x + dx[d], b = y + dy[d]; //转向之后再确定方向
        }
        x = a, y = b; //走
    }

    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < m; j ++ ) cout << res[i][j] << ' ';
        cout << endl;
    }
}

void test2(int m, int n) {
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

    vector<int> ans;
    int u = 0;      // 赋值上下左右边界
    int d = matrix.size() - 1;
    int l = 0;
    int r = matrix[0].size() - 1;
    while (true)
    {
        for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
        if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
        for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
        if(-- r < l) break; //重新设定有边界
        for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
        if(-- d < u) break; //重新设定下边界
        for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
        if(++ l > r) break; //重新设定左边界
    }
    cout << "------->" << endl;

    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
}

void test3(int row, int col) {
    vector<vector<int>> matrix(row, vector<int>(col, 0)); // 初始化为0
    // 定义方向
    // (0, 1)   向右
    // (1, 0)   向下
    // (0, -1)  向左
    // (-1, 0)  向上
    vector<int> xDrection = {0, 1, 0, -1}; // x轴方向
    vector<int> yDrection = {1, 0, -1, 0}; // y轴方向
    int x = 0, y = 0; // 初始坐标
    int d = 0; // 初始方位
    for(int count = 1; count <= row * col; ++count) {
        matrix[x][y] = count;
        int nx = x + xDrection[d], ny = y + yDrection[d]; // 获取下一个位置 
        if (nx < 0 || nx >= row || ny < 0 || ny >= col || matrix[nx][ny]) { // 撞墙或已遍历过
            d = (d + 1) % 4; // 转向
            nx = x + xDrection[d], ny = y + yDrection[d]; // 重新获取下一个位置 
        }
        x = nx, y = ny; // 移动
    } 

    for (const auto &it: matrix) {
        for (int num : it) {
            printf("%5d", num);
        }
        cout << endl;
    }
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    
    // test1(100, 10);
    // test2(5, 6);
    test3(100, 10);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}