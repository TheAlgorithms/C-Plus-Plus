/**
 * @file
 * @brief Implementation of generating
 * [Permutations](https://leetcode.com/problems/permutations/description/)
 * using Backtracking.
 * 
 * @details
 * Generates all possible ordered arrangements of a given set of elements
 * using recursive swap-based backtracking algorithm.
 *
 * @author [Mehran Hashemi](https://github.com/mhrn83)
 */

#include <algorithm> /// for std::swap
#include <cassert>   /// for assert
#include <iostream>  /// for std::cout
#include <vector>    /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {

/**
 * @namespace permutations
 * @brief Functions for recursive permutation generation
 */
namespace permutations {

/**
 * @brief Recursive function to generate permutations of a vector using backtracking.
 * @tparam T Type of elements in the vector
 * @param arr Target vector being permuted
 * @param k Current index being processed
 * @param n Total size of the vector
 * @param result Reference to vector where generated permutations are stored
 */
template <typename T>
void permute(std::vector<T>& arr, size_t k, size_t n, std::vector<std::vector<T>>& result) {
    if (k == n) {
        result.push_back(arr);
        return;
    }

    for (size_t i = k; i < n; ++i) {
        std::swap(arr[k], arr[i]);
        permute(arr, k + 1, n, result);
        std::swap(arr[k], arr[i]);
    }
}

/**
 * @brief Helper function to return all permutations of an input vector.
 * @tparam T Type of elements in the vector
 * @param arr Input vector
 * @returns `std::vector<std::vector<T>>` Collection of all permutations
 */
template <typename T>
std::vector<std::vector<T>> get_permutations(std::vector<T> arr) {
    std::vector<std::vector<T>> result;
    permute(arr, 0, arr.size(), result);
    return result;
}

}  // namespace permutations
}  // namespace backtracking

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<int> input1 = {1, 2, 3};
    auto res1 = backtracking::permutations::get_permutations(input1);
    assert(res1.size() == 6);
    assert((res1[0] == std::vector<int>{1, 2, 3}));
    assert((res1[1] == std::vector<int>{1, 3, 2}));
    assert((res1[2] == std::vector<int>{2, 1, 3}));
    assert((res1[3] == std::vector<int>{2, 3, 1}));
    assert((res1[4] == std::vector<int>{3, 2, 1}));
    assert((res1[5] == std::vector<int>{3, 1, 2}));

    std::vector<char> input2 = {'a', 'b'};
    auto res2 = backtracking::permutations::get_permutations(input2);
    assert(res2.size() == 2);
    assert((res2[0] == std::vector<char>{'a', 'b'}));
    assert((res2[1] == std::vector<char>{'b', 'a'}));

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
