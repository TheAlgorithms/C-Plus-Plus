/**
 * @file
 * @brief [N queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) all
 * optimized
 *
 * @author [Sombit Bose](https://github.com/deadshotsb)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <array>
#include <iostream>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace n_queens_optimized
 * @brief Functions for [Eight
 * Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) puzzle optimized.
 */
namespace n_queens_optimized {
/**
 * Utility function to print matrix
 * @tparam n number of matrix size
 * @param board matrix where numbers are saved
 */
template <size_t n>
void PrintSol(const std::array<std::array<int, n>, n> &board) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (n % 2 == 0 || (n % 2 == 1 && board[n / 2 + 1][0] != 1)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << board[j][i] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

/**
 * Check if a queen can be placed on matrix
 * @tparam n number of matrix size
 * @param board matrix where numbers are saved
 * @param row current index in rows
 * @param col current index in columns
 * @returns `true` if queen can be placed on matrix
 * @returns `false` if queen can't be placed on matrix
 */
template <size_t n>
bool CanIMove(const std::array<std::array<int, n>, n> &board, int row,
              int col) {
    /// check in the row
    for (int i = 0; i <= col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }
    /// check the first diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    /// check the second diagonal
    for (int i = row, j = col; i <= n - 1 && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    return true;
}

/**
 * Solve n queens problem
 * @tparam n number of matrix size
 * @param board matrix where numbers are saved
 * @param col current index in columns
 */
template <size_t n>
void NQueenSol(std::array<std::array<int, n>, n> board, int col) {
    if (col >= n) {
        PrintSol<n>(board);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (CanIMove<n>(board, i, col)) {
            board[i][col] = 1;
            NQueenSol<n>(board, col + 1);
            board[i][col] = 0;
        }
    }
}
}  // namespace n_queens_optimized
}  // namespace backtracking

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    const int n = 4;
    std::array<std::array<int, n>, n> board{};

    if (n % 2 == 0) {
        for (int i = 0; i <= n / 2 - 1; i++) {
            if (backtracking::n_queens_optimized::CanIMove(board, i, 0)) {
                board[i][0] = 1;
                backtracking::n_queens_optimized::NQueenSol(board, 1);
                board[i][0] = 0;
            }
        }
    } else {
        for (int i = 0; i <= n / 2; i++) {
            if (backtracking::n_queens_optimized::CanIMove(board, i, 0)) {
                board[i][0] = 1;
                backtracking::n_queens_optimized::NQueenSol(board, 1);
                board[i][0] = 0;
            }
        }
    }
    return 0;
}
