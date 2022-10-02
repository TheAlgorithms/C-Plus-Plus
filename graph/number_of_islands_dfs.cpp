/**
 * @file
 *
 * @brief Algorithm to count the number of islands
 *
 * @details
 * Depth First Traversal (or Search) for a graph is similar to Depth First
 * Traversal of a tree. The only catch here is, that, unlike trees, graphs may
 * contain cycles (a node may be visited twice). To avoid processing a node more
 * than once, use a boolean visited array. A graph can have more than one DFS
 * traversal.
 *
 * The algorithm implemented in this file determines the number of islands in a
 * 2D array of 1s(land) and 0s(water).
 *
 * @author [Harsh Agrawal](https://github.com/harshagrawal523)
 *
 */
#include <iostream>  // for IO operations
#include <string>    // for strings
#include <vector>    // for vectors

/**
 * @namespace graph
 * @brief Graphical algorithms
 */
namespace graph {
/**
 * @namespace number_of_islands
 * @brief Functions for counting the number of islands
 */
namespace number_of_islands {
/**
 * @brief Class for representing the matrix of 0s(water) and 1s(land).
 */
class matrix {
 private:
    int n, m;  ///< dimensions of the graph
    std::vector<std::vector<char> >
        mat;  ///< matrix that stores the ocean(0s and 1s)

 public:
    /**
     * @brief Constructor that initializes the matrix of oceans on creation
     */
    explicit matrix(std::vector<std::vector<char> > mat, int rows, int cols) {
        n = rows;
        m = cols;
        mat.resize(n, std::vector<char>(m));
    }
    void dfs(
        std::vector<std::vector<char> > *mat, int row,
        int col);  ///< DFS function that helps us find the number of islands
};
/**
 * @brief this is a dfs funtion which checks all the connected 1s
 * the function returns if it goes out of bound of matrix
 */
void matrix::dfs(std::vector<std::vector<char> > *mat, int row, int col) {
    if (row < 0 || row >= (*mat).size() || col < 0 || col >= (*mat)[0].size()) {
        return;
    }
    if ((*mat)[row][col] == '0') {
        return;
    }
    (*mat)[row][col] = '0';
    dfs(mat, row - 1, col);
    dfs(mat, row + 1, col);
    dfs(mat, row, col + 1);
    dfs(mat, row, col - 1);
}

}  // namespace number_of_islands
}  // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test() {
    std::vector<std::vector<char> > mat;
    graph::number_of_islands::matrix ocean(
        mat, 4, 5);  // creating a ocean with 1s(land) and 0s(water)
    // initializing the matrix
    mat = {{'1', '1', '1', '1', '0'},
           {'1', '1', '0', '1', '0'},
           {'1', '1', '0', '0', '0'},
           {'0', '0', '0', '0', '0'}};
    // number of islands = ans
    int ans = 0;

    // operating on the matrix
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] == '1') {
                ocean.dfs(&mat, i, j);
                ans++;
            }
        }
    }
    std::cout << ans << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Testing

    return 0;
}
