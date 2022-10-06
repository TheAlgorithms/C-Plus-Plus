#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Mark Paths and return if it is possible
bool escapeMazeHelper(vector<vector<int>> &maze, int row, int col)
{
    bool ans; // true if any valid path exists from this point
    // BASE CASES
    if (row == maze.size() - 1 && col == maze.size() - 1 && maze[row][col] == 1)
    {
        maze[row][col] = 3;
        return true;
    }
    else if (row >= maze.size() || col >= maze.size() || maze[row][col] == 0 || maze[row][col] == 3)
    {
        return false;
    }
    else
    {
        // mark current point ===> CHOOSE
        maze[row][col] = 3;

        // explore choices ===> EXPLORE
        ans = escapeMazeHelper(maze, row + 1, col)     // down
              || escapeMazeHelper(maze, row, col - 1)  // left
              || escapeMazeHelper(maze, row, col + 1)  // right
              || escapeMazeHelper(maze, row - 1, col); // up

        // unchoose current point
        if (ans == false)
            maze[row][col] = 0;
    }
    return ans;
}

bool escapeMaze(vector<vector<int>> &maze)
{
    return escapeMazeHelper(maze, 0, 0);
}

void escapePathHelper(vector<vector<int>> &maze, int row, int col, vector<string> &ans, string op)
{
    if (row == maze.size() - 1 && col == maze.size() - 1 && maze[row][col] == 1)
    {
        ans.push_back(op); // maze solved!
        return;
    }
    else if (row >= maze.size() || col >= maze.size() || maze[row][col] == 0)
    {
        return; // invalid case, backtrack
    }
    else
    {
        // CHOOSE
        maze[row][col] = 0;

        // EXPLORE OTHER OPTIONS
        escapePathHelper(maze, row + 1, col, ans, op + "D"); // down
        escapePathHelper(maze, row, col - 1, ans, op + "L"); // left
        escapePathHelper(maze, row, col + 1, ans, op + "R"); // right
        escapePathHelper(maze, row - 1, col, ans, op + "U"); // up

        // UNCHOOSE
        maze[row][col] = 1;
    }
}

void escapePath(vector<vector<int>> &maze)
{
    vector<string> ans;
    escapePathHelper(maze, 0, 0, ans, "");

    // print paths
    for (string s : ans)
    {
        cout << s << "\n";
    }
}

int main()
{
    int N = 4;
    vector<vector<int>> m = {{1, 0, 0, 0},
                             {1, 1, 0, 1},
                             {1, 1, 0, 0},
                             {0, 1, 1, 1}};

    escapePath(m);
    // cout << "possible? -> " << escapeMaze(m) << "\n";

    // cout << "marked path if possible \n";
    // for (auto i : m)
    // {
    //     for (auto j : i)
    //     {
    //         cout << j << " ";
    //     }
    //     cout << "\n";
    // }

    return 0;
}