/**
 * @file
 * @brief Implements [Rat in a
 * Maze](https://www.codesdope.com/blog/article/backtracking-to-
 * solve-a-rat-in-a-maze-c-java-pytho/) algorithm
 *
 * @details
 * A Maze is given as N*N binary matrix of blocks where source block is the
 * upper left most block i.e., maze[0][0] and destination block is lower
 * rightmost block i.e., maze[N-1][N-1]. A rat starts from source and has to
 * reach destination. The rat can move only in two directions: forward and down.
 * In the maze matrix, 0 means the block is dead end and 1 means the block can
 * be used in the path from source to destination.
 *
 * @author [Vaibhav Thakkar](https://github.com/vaithak)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace rat_maze
 * @brief Functions for [Rat in a
 * Maze](https://www.codesdope.com/blog/article/backtracking-to-
 * solve-a-rat-in-a-maze-c-java-pytho/) algorithm
 */
namespace rat_maze {
/**
 * @brief Solve rat maze problem
 * @tparam size number of matrix size
 * @param currposrow current position in rows
 * @param currposcol current position in columns
 * @param maze matrix where numbers are saved
 * @param soln matrix to problem solution
 * @returns `true` if there exists a solution to move one step ahead in a column
 * or in a row
 * @returns `false` for the backtracking part
 */
template <size_t size>
bool solveMaze(int currposrow, int currposcol,
               const std::array<std::array<int, size>, size> &maze,
               std::array<std::array<int, size>, size> soln) {
    if ((currposrow == size - 1) && (currposcol == size - 1)) {
        soln[currposrow][currposcol] = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << soln[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return true;
    } else {
        soln[currposrow][currposcol] = 1;

        // if there exist a solution by moving one step ahead in a column
        if ((currposcol < size - 1) && maze[currposrow][currposcol + 1] == 1 &&
            solveMaze(currposrow, currposcol + 1, maze, soln)) {
            return true;
        }

        // if there exists a solution by moving one step ahead in a row
        if ((currposrow < size - 1) && maze[currposrow + 1][currposcol] == 1 &&
            solveMaze(currposrow + 1, currposcol, maze, soln)) {
            return true;
        }

        // the backtracking part
        soln[currposrow][currposcol] = 0;
        return false;
    }
}
}  // namespace rat_maze
}  // namespace backtracking

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    const int size = 4;
    std::array<std::array<int, size>, size> maze = {
        std::array<int, size>{1, 0, 1, 0}, std::array<int, size>{1, 0, 1, 1},
        std::array<int, size>{1, 0, 0, 1}, std::array<int, size>{1, 1, 1, 1}};

    std::array<std::array<int, size>, size> soln{};

    // Backtracking: setup matrix solution to zero
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            soln[i][j] = 0;
        }
    }

    int currposrow = 0;  // Current position in the rows
    int currposcol = 0;  // Current position in the columns

    assert(backtracking::rat_maze::solveMaze<size>(currposrow, currposcol, maze,
                                                   soln) == 1);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
