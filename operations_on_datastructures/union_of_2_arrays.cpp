/**
 * @file
 * @brief Implementation for the [Union of two sorted
 * Arrays](https://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/)
 * algorithm.
 * @details A binary tree can be reversed by swapping the left and
 * right child of a node at each node, starting from the root, and
 * cascading below. This solution aims to provide an implementation of
 * a recursive reversal of a binary tree.
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// For assert
#include <iostream>  /// For IO operations
#include <vector>    /// For std::vector

using namespace std;

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

void print(vector<int32_t> array) {
    for (int64_t i : array) {
        std::cout << i << " ";  /// Print each value in the array
    }
    std::cout << "\n";  /// Print newline
}
vector<int32_t> get_union(vector<int32_t> first, vector<int32_t> second) {}
}  // namespace operations_on_datastructures

int main() {
    int m, n, i = 0, j = 0;
    cout << "Enter size of both arrays:";
    cin >> m >> n;
    int a[m];
    int b[n];
    cout << "Enter elements of array 1:";
    for (i = 0; i < m; i++) cin >> a[i];
    cout << "Enter elements of array 2:";
    for (i = 0; i < n; i++) cin >> b[i];
    i = 0;
    j = 0;
    while ((i < m) && (j < n)) {
        if (a[i] < b[j])
            cout << a[i++] << " ";
        else if (a[i] > b[j])
            cout << b[j++] << " ";
        else {
            cout << a[i++];
            j++;
        }
    }
    while (i < m) cout << a[i++] << " ";
    while (j < n) cout << b[j++] << " ";
    return 0;
}