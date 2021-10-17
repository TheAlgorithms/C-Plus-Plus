/**
 * @file
 * @brief [Knight's tour](https://en.wikipedia.org/wiki/Knight%27s_tour) algorithm
 *
 * @details
 * A knight's tour is a sequence of moves of a knight on a chessboard
 * such that the knight visits every square only once. If the knight
 * ends on a square that is one knight's move from the beginning
 * square (so that it could tour the board again immediately, following
 * the same path, the tour is closed; otherwise, it is open.
 *
 * @author [Nikhil Arora](https://github.com/nikhilarora068)
 * @author [David Leal](https://github.com/Panquesito7)
 */
#include <iostream>
#include <array>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
    /**
     * A utility function to check if i,j are valid indexes for N*N chessboard
     * @tparam V number of vertices in array
     * @param x current index in rows
     * @param y current index in columns
     * @param sol matrix where numbers are saved
     * @returns `true` if ....
     * @returns `false` if ....
     */
    template <size_t V>
    bool issafe(int x, int y, const std::array <std::array <int, V>, V>& sol) {
        return (x < V && x >= 0 && y < V && y >= 0 && sol[x][y] == -1);
    }

    /**
     * Knight's tour algorithm
     * @tparam V number of vertices in array
     * @param x current index in rows
     * @param y current index in columns
     * @param mov movement to be done
     * @param sol matrix where numbers are saved
     * @param xmov next move of knight (x coordinate)
     * @param ymov next move of knight (y coordinate)
     * @returns `true` if solution exists
     * @returns `false` if solution does not exist
     */
    template <size_t V>
    bool solve(int x, int y, int mov, std::array <std::array <int, V>, V> &sol,
        const std::array <int, V> &xmov, std::array <int, V> &ymov) {
        int k, xnext, ynext;

        if (mov == V * V) {
            return true;
        }

        for (k = 0; k < V; k++) {
            xnext = x + xmov[k];
            ynext = y + ymov[k];

            if (backtracking::issafe<V>(xnext, ynext, sol)) {
                sol[xnext][ynext] = mov;

                if (backtracking::solve<V>(xnext, ynext, mov + 1, sol, xmov, ymov) == true) {
                    return true;
                }
                else {
                    sol[xnext][ynext] = -1;
                }
            }
        }
        return false;
    }
} // namespace backtracking

/**
 * Main function
 */
int main() {
    const int n = 8;
    std::array <std::array <int, n>, n> sol = { 0 };

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) { sol[i][j] = -1; }
    }

    std::array <int, n> xmov = { 2, 1, -1, -2, -2, -1, 1, 2 };
    std::array <int, n> ymov = { 1, 2, 2, 1, -1, -2, -2, -1 };

    sol[0][0] = 0;

    bool flag = backtracking::solve<n>(0, 0, 1, sol, xmov, ymov);
    if (flag == false) {
        std::cout << "Error: Solution does not exist\n";
    }
    else {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) { std::cout << sol[i][j] << "  "; }
            std::cout << "\n";
        }
    }
    return 0;
}
