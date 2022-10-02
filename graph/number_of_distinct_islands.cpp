#include <iostream>
#include <vector>
#include <set>
#define int int64_t
using namespace std;

void dfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int i, int j, int base_i, int base_j, int m, int n, vector<pair<int, int>> &temp)
{
    visited[i][j] = 1;
    grid[i][j] = 0;
    temp.push_back(make_pair(i - base_i, j - base_j)); // i-base_i,j-base_j is used to track the shape of an island and therefore helps us in creating the number of distinct islands
    // moving down
    if (i < m - 1 && grid[i + 1][j] == 1 && visited[i + 1][j] != 1)
    {
        dfs(grid, visited, i + 1, j, base_i, base_j, m, n, temp);
    }
    // moving up
    if (i > 0 && grid[i - 1][j] == 1 && visited[i - 1][j] != 1)
    {
        dfs(grid, visited, i - 1, j, base_i, base_j, m, n, temp);
    }
    // moving left
    if (j > 0 && grid[i][j - 1] == 1 && visited[i][j - 1] != 1)
    {
        dfs(grid, visited, i, j - 1, base_i, base_j, m, n, temp);
    }
    // moving right
    if (j < n - 1 && grid[i][j + 1] == 1 && visited[i][j + 1] != 1)
    {
        dfs(grid, visited, i, j + 1, base_i, base_j, m, n, temp);
    }
}

int countDistinctIslands(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    set<vector<pair<int, int>>> st; // set data structure is used to remove the duplicated islands and only storing the number of distinct islands
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited[i][j] != 1 && grid[i][j] != 0)
            {
                int base_i = i, base_j = j;
                vector<pair<int, int>> temp;
                dfs(grid, visited, i, j, base_i, base_j, m, n, temp);
                st.insert(temp);
            }
        }
    }
    return st.size(); // returning the size of the set as it represents the number of distinct islands
}

int32_t main()
{
    // Sample Test Cases:-

    //Test Case#1

    // Input:
    // grid[][] = {{1, 1, 0, 0, 0},
    //             {1, 1, 0, 0, 0},
    //             {0, 0, 0, 1, 1},
    //             {0, 0, 0, 1, 1}}
    // Output:
    // 1
    // Explanation:
    // grid[][] = {{1, 1, 0, 0, 0}, 
    //             {1, 1, 0, 0, 0}, 
    //             {0, 0, 0, 1, 1}, 
    //             {0, 0, 0, 1, 1}}
    // Same colored islands are equal.
    // We have 2 equal islands, so we 
    // have only 1 distinct island.

    //Test Case#2

    // Input:
    // grid[][] = {{1, 1, 0, 1, 1},
    //             {1, 0, 0, 0, 0},
    //             {0, 0, 0, 0, 1},
    //             {1, 1, 0, 1, 1}}
    // Output:
    // 3
    // Explanation:
    // grid[][] = {{1, 1, 0, 1, 1}, 
    //             {1, 0, 0, 0, 0}, 
    //             {0, 0, 0, 0, 1}, 
    //             {1, 1, 0, 1, 1}}
    // Same colored islands are equal.
    // We have 4 islands, but 2 of them
    // are equal, So we have 3 distinct islands.

    // Code Starts From here:-
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // taking inputs of rows and columns
    int m, n;
    cin >> m >> n;

    // initializing the number of islands
    int ans = 0;

    // creating the 2D Matrix
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << countDistinctIslands(matrix);

    return 0;
}