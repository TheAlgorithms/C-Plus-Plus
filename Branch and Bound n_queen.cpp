/*
Details--
the  N queens puzzle is the problem of placing N chess queens on a N*N chessboard
so that no two queens threaten each other. Thus, a slution requires that no two 
queens share the same row, column, or diagonal


By using backtracking for N -queen we backtrack when we hit a dead end.
In branch and bound after building a partial solution we figure out that there is no point going any deeper as we 
are going to hi a dead end

*/


/*
Idea--
the idea is to place queens one by one in different columns starting from the 
leftmost column.
when we place a queen in a column we check for clashes with already placed queens.
if we find a row for which there is no clash, we mark this row and column as part
of the solution.


*/

#include <iostream>
#include <string.h>
using namespace std;
#define N 8

/* A utility function to print solution */
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << " " << board[i][j];
        cout << "\n";
    }
}

/* A Optimized function to check if a queen can
be placed on board[row][col] */
bool isSafe(int row, int col, int slashCode[N][N],
            int backslashCode[N][N], bool rowLookup[],
            bool slashCodeLookup[], bool backslashCodeLookup[])
{
    if (slashCodeLookup[slashCode[row][col]] ||
        backslashCodeLookup[backslashCode[row][col]] ||
        rowLookup[row])
        return false;

    return true;
}

/* A recursive utility function
to solve N Queen problem */
bool solveNQueensUtil(int board[N][N], int col,
                      int slashCode[N][N], int backslashCode[N][N],
                      bool rowLookup[N],
                      bool slashCodeLookup[],
                      bool backslashCodeLookup[])
{
    /* base case: If all queens are placed
    then return true */
    if (col >= N)
        return true;

    /* Consider this column and try placing
       this queen in all rows one by one */
    for (int i = 0; i < N; i++)
    {
        /* Check if queen can be placed on
           board[i][col] */
        if (isSafe(i, col, slashCode,
                   backslashCode, rowLookup,
                   slashCodeLookup, backslashCodeLookup))
        {
            /* Place this queen in board[i][col] */
            board[i][col] = 1;
            rowLookup[i] = true;
            slashCodeLookup[slashCode[i][col]] = true;
            backslashCodeLookup[backslashCode[i][col]] = true;

            /* recur to place rest of the queens */
            if (solveNQueensUtil(board, col + 1,
                                 slashCode, backslashCode,
                                 rowLookup, slashCodeLookup, backslashCodeLookup))
                return true;

            /* If placing queen in board[i][col]
            doesn't lead to a solution, then backtrack */

            /* Remove queen from board[i][col] */
            board[i][col] = 0;
            rowLookup[i] = false;
            slashCodeLookup[slashCode[i][col]] = false;
            backslashCodeLookup[backslashCode[i][col]] = false;
        }
    }

    /* If queen can not be place in any row in
        this column col then return false */
    return false;
}

/* This function solves the N Queen problem using
Branch and Bound. It mainly uses solveNQueensUtil() to
solve the problem. It returns false if queens
cannot be placed, otherwise return true and
prints placement of queens in the form of 1s.
Please note that there may be more than one
solutions, this function prints one of the
feasible solutions.*/
bool solveNQueens()
{
    int board[N][N];
    memset(board, 0, sizeof board);

    // helper matrices
    int slashCode[N][N];
    int backslashCode[N][N];

    // arrays to tell us which rows are occupied
    bool rowLookup[N] = {false};

    //keep two arrays to tell us
    // which diagonals are occupied
    bool slashCodeLookup[2 * N - 1] = {false};
    bool backslashCodeLookup[2 * N - 1] = {false};

    // initialize helper matrices
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
        {
            slashCode[r][c] = r + c,
            backslashCode[r][c] = r - c + 7;
        }

    if (solveNQueensUtil(board, 0,
                         slashCode, backslashCode,
                         rowLookup, slashCodeLookup, backslashCodeLookup) ==
        false)
    {
        cout << "Solution does not exist";
        return false;
    }

    // solution found
    printSolution(board);
    return true;
}

// Driver program to test above function
int main()
{
    solveNQueens();

    return 0;
}
