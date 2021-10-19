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

/**
 * @brief Prints the values of a vector sequentially, ending with a newline
 * character.
 * @returns void
 */
void print(std::vector<int32_t> array) {
    for (int64_t i : array) {
        std::cout << i << " ";  /// Print each value in the array
    }
    std::cout << "\n";  /// Print newline
}

/**
 * @brief Gets the union of two sorted arrays, and returns them in a
 * vector.
 * @details An algorithm is used that compares the elements of the two vectors,
 * appending the one that has a lower value, and incrementing the index for that
 * array. If one of the arrays reaches its end, all the elements of the other
 * are appended to the resultant vector.
 * @param first A std::vector of sorted integer values
 * @param second A std::vector of sorted integer values
 * @returns A std::vector of the union of the two arrays, in ascending order
 */
std::vector<int32_t> get_union(std::vector<int32_t> first,
                               std::vector<int32_t> second) {
    std::vector<int32_t> res;         ///< Vector to hold the union
    size_t f_index;                   ///< Index for the first array
    size_t s_index;                   ///< Index for the second array
    size_t f_length = first.size();   ///< Length of first array
    size_t s_length = second.size();  ///< Length of second array
    while (f_index < f_length && s_index < s_length) {
        int32_t next;  ///< Integer to store value of the next element
        if (first[f_index] < second[s_index]) {
            next = first[f_index];  ///< Append from first array
            f_index++;              ///< Increment index of second array
        } else if (first[f_index] > second[s_index]) {
            next = second[s_index];  ///< Append from second array
            s_index++;               ///< Increment index of second array
        } else {
            next = first[f_index];  ///< Element is the same in both
            f_index++;              ///< Increment index of first array
            s_index++;              ///< Increment index of second array too
        }
        if (next != res.back()) {
            res.push_back(next);  ///< Add the element if it is unique
        }
    }
    while (f_index < f_length) {
        res.push_back(first[f_index]);  ///< Append remaining elements
        f_index++;
    }
    while (s_index < s_length) {
        res.push_back(second[s_index]);  ///< Append remaining elements
        s_index++;
    }
    return res;
}

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