#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

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

int main() {
    // taking inputs of rows and columns
    int n = 0, m = 0;
    cin >> n >> m;

    // initializing the number of islands
    int ans = 0;

    // creating the 2D Matrix
    vector<vector<char>> matrix(n, vector<char>(m, 0));
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