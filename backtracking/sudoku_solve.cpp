/**
 * @file
 * @brief [Sudoku Solver](https://en.wikipedia.org/wiki/Sudoku) algorithm.
 *
 * @details
 * Sudoku (数独, sūdoku, digit-single) (/suːˈdoʊkuː/, /-ˈdɒk-/, /sə-/,
 * originally called Number Place) is a logic-based, combinatorial
 * number-placement puzzle. In classic sudoku, the objective is to fill a 9×9
 * grid with digits so that each column, each row, and each of the nine 3×3
 * subgrids that compose the grid (also called "boxes", "blocks", or "regions")
 * contain all of the digits from 1 to 9. The puzzle setter provides a
 * partially completed grid, which for a well-posed puzzle has a single
 * solution.
 *
 * @author [DarthCoder3200](https://github.com/DarthCoder3200)
 * @author [David Leal](https://github.com/Panquesito7)
 */
#include <array>     /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace sudoku_solver
 * @brief Functions for the [Sudoku
 * Solver](https://en.wikipedia.org/wiki/Sudoku) implementation
 */
namespace sudoku_solver {
/**
 * @brief Check if it's possible to place a number (`no` parameter)
 * @tparam V number of vertices in the array
 * @param mat matrix where numbers are saved
 * @param i current index in rows
 * @param j current index in columns
 * @param no number to be added in matrix
 * @param n number of times loop will run
 * @returns `true` if 'mat' is different from 'no'
 * @returns `false` if 'mat' equals to 'no'
 */
template <size_t V>
bool isPossible(const std::array<std::array<int, V>, V> &mat, int i, int j,
                int no, int n) {
    /// `no` shouldn't be present in either row i or column j
    for (int x = 0; x < n; x++) {
        if (mat[x][j] == no || mat[i][x] == no) {
            return false;
        }
    }

    /// `no` shouldn't be present in the 3*3 subgrid
    int sx = (i / 3) * 3;
    int sy = (j / 3) * 3;

    for (int x = sx; x < sx + 3; x++) {
        for (int y = sy; y < sy + 3; y++) {
            if (mat[x][y] == no) {
                return false;
            }
        }
    }

    return true;
}
/**
 * @brief Utility function to print the matrix
 * @tparam V number of vertices in array
 * @param mat matrix where numbers are saved
 * @param starting_mat copy of mat, required by printMat for highlighting the
 * differences
 * @param n number of times loop will run
 * @return void
 */
template <size_t V>
void printMat(const std::array<std::array<int, V>, V> &mat,
              const std::array<std::array<int, V>, V> &starting_mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (starting_mat[i][j] != mat[i][j]) {
                std::cout << "\033[93m" << mat[i][j] << "\033[0m"
                          << " ";
            } else {
                std::cout << mat[i][j] << " ";
            }
            if ((j + 1) % 3 == 0) {
                std::cout << '\t';
            }
        }
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Main function to implement the Sudoku algorithm
 * @tparam V number of vertices in array
 * @param mat matrix where numbers are saved
 * @param starting_mat copy of mat, required by printMat for highlighting the
 * differences
 * @param i current index in rows
 * @param j current index in columns
 * @returns `true` if 'no' was placed
 * @returns `false` if 'no' was not placed
 */
template <size_t V>
bool solveSudoku(std::array<std::array<int, V>, V> &mat,
                 const std::array<std::array<int, V>, V> &starting_mat, int i,
                 int j) {
    /// Base Case
    if (i == 9) {
        /// Solved for 9 rows already
        printMat<V>(mat, starting_mat, 9);
        return true;
    }

    /// Crossed the last  Cell in the row
    if (j == 9) {
        return solveSudoku<V>(mat, starting_mat, i + 1, 0);
    }

    /// Blue Cell - Skip
    if (mat[i][j] != 0) {
        return solveSudoku<V>(mat, starting_mat, i, j + 1);
    }
    /// White Cell
    /// Try to place every possible no
    for (int no = 1; no <= 9; no++) {
        if (isPossible<V>(mat, i, j, no, 9)) {
            /// Place the 'no' - assuming a solution will exist
            mat[i][j] = no;
            bool solution_found = solveSudoku<V>(mat, starting_mat, i, j + 1);
            if (solution_found) {
                return true;
            }
            /// Couldn't find a solution
            /// loop will place the next `no`.
        }
    }
    /// Solution couldn't be found for any of the numbers provided
    mat[i][j] = 0;
    return false;
}
}  // namespace sudoku_solver
}  // namespace backtracking

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    const int V = 9;
    std::array<std::array<int, V>, V> mat = {
        std::array<int, V>{5, 3, 0, 0, 7, 0, 0, 0, 0},
        std::array<int, V>{6, 0, 0, 1, 9, 5, 0, 0, 0},
        std::array<int, V>{0, 9, 8, 0, 0, 0, 0, 6, 0},
        std::array<int, V>{8, 0, 0, 0, 6, 0, 0, 0, 3},
        std::array<int, V>{4, 0, 0, 8, 0, 3, 0, 0, 1},
        std::array<int, V>{7, 0, 0, 0, 2, 0, 0, 0, 6},
        std::array<int, V>{0, 6, 0, 0, 0, 0, 2, 8, 0},
        std::array<int, V>{0, 0, 0, 4, 1, 9, 0, 0, 5},
        std::array<int, V>{0, 0, 0, 0, 8, 0, 0, 7, 9}};

    backtracking::sudoku_solver::printMat<V>(mat, mat, 9);
    std::cout << "Solution " << std::endl;
    std::array<std::array<int, V>, V> starting_mat = mat;
    backtracking::sudoku_solver::solveSudoku<V>(mat, starting_mat, 0, 0);

    return 0;
}
