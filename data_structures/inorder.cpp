/*
    N queens problem
    ----------------
    Find a way to place N non-attacking queens on an N×N chessboard.
    Time complexity
    ---------------
    O(N!), where N is the number of queens.
    Space complexity
    ----------------
    O(N^2), where N is the number of queens.
*/

#ifndef RAT_in_A_MAZE_HPP
#define RAT_in_A_MAZE_HPP

#include <iostream>
#include <vector>

// C++ program to solve Rat in a Maze problem using
// backtracking

using namespace std;
// Maze size
#define N 4

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);

// A utility function to print solution matrix sol[N][N]
void printSolution(int sol[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << " " << sol[i][j] << " ";
        cout << endl;
    }
}

// A utility function to check if x, y is valid index for
// N*N maze
bool isSafe(int maze[N][N], int x, int y)
{
    // if (x, y outside maze) return false
    if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
        return true;
    return false;
}

// This function solves the Maze problem using Backtracking.
// It mainly uses solveMazeUtil() to solve the problem. It
// returns false if no path is possible, otherwise return
// true and prints the path in the form of 1s. Please note
// that there may be more than one solutions, this function
// prints one of the feasible solutions.
bool solveMaze(int maze[N][N])
{
    int sol[N][N] = {{0, 0, 0, 0},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0}};
    if (solveMazeUtil(maze, 0, 0, sol) == false)
    {
        cout << "Solution doesn't exist";
        return false;
    }
    printSolution(sol);
    return true;
}

// A recursive utility function to solve Maze problem
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
    // if (x, y is goal) return true
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1)
    {
        sol[x][y] = 1;
        return true;
    }
    // Check if maze[x][y] is valid
    if (isSafe(maze, x, y) == true)
    {
        // Check if the current block is already part of
        // solution path.
        if (sol[x][y] == 1)
            return false;
        // mark x, y as part of solution path
        sol[x][y] = 1;
        /* Move forward in x direction */
        if (solveMazeUtil(maze, x + 1, y, sol) == true)
            return true;
        // If moving in x direction doesn't give solution
        // then Move down in y direction
        if (solveMazeUtil(maze, x, y + 1, sol) == true)
            return true;
        // If none of the above movements work then
        // BACKTRACK: unmark x, y as part of solution path
        sol[x][y] = 0;
        return false;
    }
    return false;
}

// driver program to test above function
int main()
{
    int maze[N][N] = {{1, 0, 0, 0},
                      {1, 1, 0, 1},
                      {0, 1, 0, 0},
                      {1, 1, 1, 1}};
    solveMaze(maze);
    return 0;
}

#endif // RAT_in_A_MAZE_HPP