/**
 * @file
 * @brief Program to find maximum and minimum element in an array
 *
 * @details
 * This program demonstrates how to find the maximum and minimum values
 * in an array of elements. It is implemented as a template function so
 * it works with any comparable data type.
 *
 * The algorithm simply iterates through the array once, updating the
 * maximum and minimum values as needed. This results in \f$O(n)\f$ time
 * complexity and \f$O(1)\f$ space complexity.
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout, std::endl
#include <vector>    /// for std::vector
#include <utility>   /// for std::pair

/**
 * @namespace arrays
 * @brief Array-based algorithms
 */
namespace arrays {
/**
 * @namespace find_max_min
 * @brief Functions for finding maximum and minimum values
 */
namespace find_max_min {
/**
 * @brief Find maximum and minimum in an array
 * @tparam T data type of elements (must support comparisons)
 * @param arr input array
 * @return std::pair<T, T> containing {max, min}
 */
template <typename T>
std::pair<T, T> findMaxMin(const std::vector<T>& arr) {
    assert(!arr.empty());  // array must not be empty
    T maxVal = arr[0];
    T minVal = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return {maxVal, minVal};
}
}  // namespace find_max_min
}  // namespace arrays

/**
 * @brief Self-test implementation
 */
static void test() {
    using arrays::find_max_min::findMaxMin;

    std::vector<int> vec1 = {3, 1, 7, -5, 9};
    auto result1 = findMaxMin(vec1);
    assert(result1.first == 9 && result1.second == -5);

    std::vector<float> vec2 = {1.5, 2.5, 0.5};
    auto result2 = findMaxMin(vec2);
    assert(result2.first == 2.5f && result2.second == 0.5f);

    std::vector<char> vec3 = {'a', 'z', 'm'};
    auto result3 = findMaxMin(vec3);
    assert(result3.first == 'z' && result3.second == 'a');

    std::vector<int> vec4 = {42};
    auto result4 = findMaxMin(vec4);
    assert(result4.first == 42 && result4.second == 42);
}

/**
 * @brief Main function
 */
int main() {
    test();
    std::cout << "All tests passed!\n";
    return 0;
}
