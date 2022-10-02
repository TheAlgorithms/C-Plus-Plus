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
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @namespace islands
 * @brief DFS algorithms
 */
namespace islands {
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
    int n, m;                   // dimensions of graph
    int ans;                    // number of islands in the ocean
    vector<vector<char> > mat;  // matrix that stores the ocean(0s and 1s)

 public:
    /**
     * @brief Constructor that initializes the matrix of oceans on creation
     */
    explicit matrix(vector<vector<char> > mat, int rows, int cols) {
        n = rows;
        m = cols;
        mat.resize(n, vector<char>(m));
    }
    void dfs(vector<vector<char> > &matrix, int row,
             int col);  // dfs function that helps us find the number of islands
};
/**
 * @brief this is a dfs funtion which checks all the connected 1s
 * the function returns if it goes out of bound of matrix
 */
void matrix::dfs(vector<vector<char> > &matrix, int row, int col) {
    if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
        return;
    }
    if (matrix[row][col] == '0') {
        return;
    }
    matrix[row][col] = '0';
    dfs(matrix, row - 1, col);
    dfs(matrix, row + 1, col);
    dfs(matrix, row, col + 1);
    dfs(matrix, row, col - 1);
}

}  // namespace number_of_islands
}  // namespace islands

static void test() {
    vector<vector<char> > mat;
    islands::number_of_islands::matrix ocean(
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
                ocean.dfs(mat, i, j);
                ans++;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    test();  // Testing

    return 0;
}