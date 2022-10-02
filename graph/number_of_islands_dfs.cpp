#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
//#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int int64_t

void dfs(vector<vector<char>> &matrix, int row, int col) {
    if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
        return;
    }
    if (matrix[row][col] == '0') {
        return;
    }
    matrix[row][col] = '0';
    dfs(matrix, row - 1, col);
    dfs(matrix, row + 1, col);
    dfs(matrix, row, col + 1);
    dfs(matrix, row, col - 1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // taking inputs of rows and columns
    int n, m;
    cin >> n >> m;

    // initializing the number of islands
    int ans = 0;

    // creating the 2D Matrix
    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '1') {
                dfs(matrix, i, j);
                ans++;
            }
        }
    }

    cout << endl;
    cout << ans << endl;

    return 0;
}