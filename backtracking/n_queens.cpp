/**
 * @file
 * @brief [Eight Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle)
 * puzzle
 *
 * @details
 * The **eight queens puzzle** is the problem of placing eight chess queens on
 * an 8×8 chessboard so that no two queens threaten each other; thus, a solution
 * requires that no two queens share the same row, column, or diagonal. The
 * eight queens puzzle is an example of the more general **n queens problem** of
 * placing n non-attacking queens on an n×n chessboard, for which solutions
 * exist for all natural numbers n with the exception of n = 2 and n = 3.
 *
 * @author Unknown author
 * @author [David Leal](https://github.com/Panquesito7)
 *
 */
#include <iostream>
#include <array>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
  /**
   * @namespace n_queens
   * @brief Functions for [Eight Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) puzzle.
   */
  namespace n_queens {
    /**
    * Utility function to print matrix
    * @tparam n number of matrix size
    * @param board matrix where numbers are saved
    */
    template <size_t n>
    void printSolution(const std::array<std::array<int, n>, n> &board) {
      std::cout << "\n";
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          std::cout << "" << board[i][j] << " ";
        }
        std::cout << "\n";
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
    bool isSafe(const std::array<std::array<int, n>, n> &board, const int &row,
                const int &col) {
      int i = 0, j = 0;

      // Check this row on left side
      for (i = 0; i < col; i++) {
        if (board[row][i]) {
          return false;
        }
      }

      // Check upper diagonal on left side
      for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
          return false;
        }
      }
      // Check lower diagonal on left side
      for (i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (board[i][j]) {
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
    void solveNQ(std::array<std::array<int, n>, n> board, const int &col) {
      if (col >= n) {
        printSolution<n>(board);
        return;
      }

      // Consider this column and try placing
      // this queen in all rows one by one
      for (int i = 0; i < n; i++) {
        // Check if queen can be placed
        // on board[i][col]
        if (isSafe<n>(board, i, col)) {
          // Place this queen in matrix
          board[i][col] = 1;

          // Recursive to place rest of the queens
          solveNQ<n>(board, col + 1);

          board[i][col] = 0; // backtrack
        }
      }
    }
  } // namespace n_queens
} // namespace backtracking

/**
 * Main function
 */
int main() {
  const int n = 4;
  std::array<std::array<int, n>, n> board = {
    std::array<int, n>({0, 0, 0, 0}),
    std::array<int, n>({0, 0, 0, 0}),
    std::array<int, n>({0, 0, 0, 0}),
    std::array<int, n>({0, 0, 0, 0})
    };

  backtracking::n_queens::solveNQ<n>(board, 0);
  return 0;
}
