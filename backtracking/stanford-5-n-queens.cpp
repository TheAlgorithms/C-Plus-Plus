#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*

What solution strikes first?
=> Place Queen
=> Try to place the rest of the queens
=> unplace the queen

THIS METHOD WILL TAKE TOOOO MUCH TIME AND SO MANY REDUNDANT CALLS

We know, there must be exactly 1 queen in each col (or row)
so we should utilize that!

=> Redefine queen to be a valid placement of queen in a particular column
=> Solution space shortened!!

*/

bool isSafe(vector<string> &board, int row, int col, vector<int> &flag)
{
    // check row
    if (flag[row] == 0)
        return false;

    // check left diagonals
    if (flag[2 * board.size() - col + row - 1] == 0 || flag[3 * board.size() + col + row - 1] == 0)
        return false;

    return true;
}

void solveNQueensHelper(vector<string> &board, vector<vector<string>> &ans, int col, vector<int> &flag)
{
    if (col >= board.size())
    {
        ans.push_back(board); // BASE CASE
        return;
    }
    else
    {
        // RECURSIVE CASE
        for (int row = 0; row < board.size(); ++row)
        {
            if (isSafe(board, row, col, flag))
            {
                // CHOOSE
                board[row][col] = 'Q';
                flag[row] = flag[2 * board.size() - col + row - 1] = flag[3 * board.size() + row + col - 1] = 0;
                // mark row -> 4 rows -> 0,1,2,3
                // mark top left diag  -> 7 points -> 4, 5, 6, 7, 8, 9, 10
                // mark bottom left diag -> 7 points -> 11, 12, 13, 14, 15, 16, 17

                // EXPLORE OTHER OPTIONS
                solveNQueensHelper(board, ans, col + 1, flag);

                // UNCHOOSE
                board[row][col] = '.';
                flag[row] = flag[2 * board.size() - col + row - 1] = flag[3 * board.size() + row + col - 1] = 1;
            }
        }
    }
}

void solveNQueens(int n)
{
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    vector<int> flag(5 * board.size() - 2, 1);

    // solve
    solveNQueensHelper(board, ans, 0, flag);

    for (auto board : ans)
    {
        for (auto row : board)
            cout << row << "\n";
        cout << "\n";
    }
}

int main()
{
    int n = 5;
    solveNQueens(n);
    return 0;
}