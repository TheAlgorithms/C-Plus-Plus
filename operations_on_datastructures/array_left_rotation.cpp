/**
 * @file
 * @brief Implementation for the [Union of two sorted
 * Arrays](https://en.wikipedia.org/wiki/Union_(set_theory))
 * algorithm.
 * @details The Union of two arrays is the collection of all the unique elements
 * in the first array, combined with all of the unique elements of a second
 * array. This implementation uses ordered arrays, and an algorithm to correctly
 * order them and return the result as a new array (vector).
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

/**
 * @brief Prints the values of a vector sequentially, ending with a newline
 * character.
 * @param array Reference to the array to be printed
 * @returns void
 */
void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";  /// Print each value in the array
    }
    std::cout << "\n";  /// Print newline
}

/**
 * @brief Shifts the given vector to the left by the shift amount and returns a
 * new vector with the result. The original vector is not mutated.
 * @details Shifts the values of the vector, by creating a new vector and adding
 * values from the shift index to the end, then appending the rest of the
 * elements from the start of the vector.
 * @param array A reference to the input std::vector
 * @param shift The amount to be shifted to the left
 * @returns A std::vector with the shiftedd values
 */
std::vector<int32_t> shift_left(const std::vector<int32_t> &array,
                                size_t shift) {
    if (shift >= array.size()) {
        return {};  ///< We got an invalid shift, return empty array
    }
    std::vector<int32_t> res(array.size());  ///< Result array
    for (int i = shift; i < array.size(); i++) {
        res.push_back(array[i]);  ///< Add values after the shift index
    }
    for (int i = 0; i < shift; i++) {
        res.push_back(array[i]);  ///< Add the values from the start
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief Testcases to check Union of Two Arrays.
 */
namespace tests {
using operations_on_datastructures::print;
using operations_on_datastructures::shift_left;
/**
 * @brief A Test to check an edge case (two empty arrays)
 * @returns void
 */
void test1() {
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    print(shift_left(arr, 2));
}
}  // namespace tests

/**
 * @brief Function to test the correctness of get_union() function
 * @returns void
 */
static void test() { tests::test1(); }

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}