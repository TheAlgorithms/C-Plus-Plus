/**
 * @file
 * @brief [Sudoku Solver](https://en.wikipedia.org/wiki/Sudoku) algorithm.
 *
 * @author [DarthCoder3200](https://github.com/DarthCoder3200)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <iostream>
#include <array>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
    template <size_t V>
    bool isPossible(const std::array <std::array <int, V>, V> &mat, int i, int j, int no, int n) {
        /// Row or col nahin hona chahiye
        for (int x = 0; x < n; x++) {
            if (mat[x][j] == no || mat[i][x] == no) {
                return false;
            }
        }

        /// Subgrid mein nahi hona chahiye
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
     * Print array of array
     * @param mat array of arrays
     * @param n number of times loop will be run
     * @return void
     */
    template <size_t V>
    void printMat(const std::array <std::array <int, V>, V> &mat, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << mat[i][j] << " ";
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
     * Sudoku algorithm
     * @param mat array of arrays
     * @param i current index in rows
     * @param j current index in columns
     * @returns `true` if ....
     * @returns `false` if ....
     */
    template <size_t V>
    bool solveSudoku(std::array <std::array <int, V>, V> &mat, int i, int j) {
        /// Base Case
        if (i == 9) {
            /// Solve kr chuke hain for 9 rows already
            backtracking::printMat<V>(mat, 9);
            return true;
        }

        /// Crossed the last  Cell in the row
        if (j == 9) {
            return backtracking::solveSudoku<V>(mat, i + 1, 0);
        }

        /// Blue Cell - Skip
        if (mat[i][j] != 0) {
            return backtracking::solveSudoku<V>(mat, i, j + 1);
        }
        /// White Cell
        /// Try to place every possible no
        for (int no = 1; no <= 9; no++) {
            if (backtracking::isPossible<V>(mat, i, j, no, 9)) {
                /// Place the no - assuming solution aa jayega
                mat[i][j] = no;
                bool aageKiSolveHui = backtracking::solveSudoku<V>(mat, i, j + 1);
                if (aageKiSolveHui) {
                    return true;
                }
                /// Nahin solve hui
                /// loop will place the next no.
            }
        }
        /// Sare no try kr liey, kisi se bhi solve nahi hui
        mat[i][j] = 0;
        return false;
    }
} // namespace backtracking

/**
 * Main function
 */
int main() {
    const int V = 9;
    std::array <std::array <int, V>, V> mat = { 5, 3, 0, 0, 7, 0, 0, 0, 0, 6, 0, 0, 1, 9, 5, 0, 0, 0,
                     0, 9, 8, 0, 0, 0, 0, 6, 0, 8, 0, 0, 0, 6, 0, 0, 0, 3,
                     4, 0, 0, 8, 0, 3, 0, 0, 1, 7, 0, 0, 0, 2, 0, 0, 0, 6,
                     0, 6, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 4, 1, 9, 0, 0, 5,
                     0, 0, 0, 0, 8, 0, 0, 7, 9 };

    backtracking::printMat<V>(mat, 9);
    std::cout << "Solution " << std::endl;
    backtracking::solveSudoku<V>(mat, 0, 0);

    return 0;
}
