/**
 * @file bubble_sort.cpp
 * @brief Generic implementation of the Bubble Sort algorithm with self-tests.
 *
 * This file contains a template-based implementation of the bubble sort algorithm
 * inside the `sorting` namespace. It supports sorting of any container
 * holding elements that can be compared using the `>` operator.
 *
 * Additionally, it contains a set of self-tests to verify correctness
 * using the C++ standard library's `assert` mechanism.
 *
 * Example:
 * @code
 * std::vector<int> nums = {5, 4, 3, 2, 1};
 * sorting::bubble_sort(nums);
 * // nums becomes {1, 2, 3, 4, 5}
 *
 * std::vector<std::string> words = {"apple", "banana", "cherry"};
 * sorting::bubble_sort(words);
 * // words becomes {"apple", "banana", "cherry"}
 * @endcode
 *
 * @author Rohith A K
 * @date 2025-09-30
 */

#include <cassert>   ///< for assert
#include <iostream>  ///< for IO operations
#include <utility>   ///< for std::swap
#include <vector>    ///< for std::vector
#include <string>    ///< for std::string

namespace sorting {

/**
 * @brief Sorts the given container using the bubble sort algorithm.
 *
 * This optimized bubble sort reduces the number of passes in average cases
 * by checking if the container is already sorted during each pass.
 *
 * @tparam Container Type of the container (e.g., std::vector<T>)
 * @param cont The container to be sorted
 * @return Reference to the sorted container
 */
template <typename Container>
Container& bubble_sort(Container& cont) {
    if (cont.size() < 2) return cont;  // handle empty or single-element case

    for (std::size_t i = 0; i < cont.size() - 1; ++i) {
        bool swapped = false;
        for (std::size_t j = 0; j < cont.size() - 1 - i; ++j) {
            if (cont[j] > cont[j + 1]) {
                std::swap(cont[j], cont[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return cont;
}

}  // namespace sorting

/**
 * @brief Self-test implementations of the generic bubble_sort function.
 */
static void tests() {
    // Integer test cases
    std::vector<int> v1 = {2, 8, 1, 6, 2, 0, 3, 6};
    const std::vector<int> expected1 = {0, 1, 2, 2, 3, 6, 6, 8};
    assert(sorting::bubble_sort(v1) == expected1);

    std::vector<int> v2 = {5, 4, 3, 2, 1};
    const std::vector<int> expected2 = {1, 2, 3, 4, 5};
    assert(sorting::bubble_sort(v2) == expected2);

    std::vector<int> v3 = {1, 2, 3, 4, 5};
    const std::vector<int> expected3 = {1, 2, 3, 4, 5};
    assert(sorting::bubble_sort(v3) == expected3);

    // Negative numbers
    std::vector<int> v4 = {-5, -1, -3, -2, -4};
    const std::vector<int> expected4 = {-5, -4, -3, -2, -1};
    assert(sorting::bubble_sort(v4) == expected4);

    // Mixed negative and positive
    std::vector<int> v5 = {-1, 0, 1, -2, 2};
    const std::vector<int> expected5 = {-2, -1, 0, 1, 2};
    assert(sorting::bubble_sort(v5) == expected5);

    // Empty vector
    std::vector<int> v6 = {};
    const std::vector<int> expected6 = {};
    assert(sorting::bubble_sort(v6) == expected6);

    // Double test case
    std::vector<double> vd = {3.5, 2.1, 4.8, 1.2};
    const std::vector<double> expectedd = {1.2, 2.1, 3.5, 4.8};
    assert(sorting::bubble_sort(vd) == expectedd);

    // String test case
    std::vector<std::string> vs = {"apple", "banana", "cherry", "apricot"};
    const std::vector<std::string> expecteds = {"apple", "apricot", "banana", "cherry"};
    assert(sorting::bubble_sort(vs) == expecteds);

    // Char test case
    std::vector<char> vc = {'z', 'b', 'a', 'd', 'c'};
    const std::vector<char> expectedc = {'a', 'b', 'c', 'd', 'z'};
    assert(sorting::bubble_sort(vc) == expectedc);

    std::cout << "All generic tests have successfully passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    tests();
    return 0;
}
