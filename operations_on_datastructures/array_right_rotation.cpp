/**
 * @file
 * @brief Implementation for the [Array right
 * Rotation](https://www.javatpoint.com/program-to-right-rotate-the-elements-of-an-array)
 * algorithm.
 * @details Shifting an array to the right involves moving each element of the
 * array so that it occupies a position of a certain shift value after its
 * current one. This implementation uses a result vector and does not mutate the
 * input.
 * @see array_left_rotation.cpp
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
 * @brief Shifts the given vector to the right by the shift amount and returns a
 * new vector with the result. The original vector is not mutated.
 * @details Shifts the values of the vector, by creating a new vector and adding
 * values from the shift index to the end, then appending the rest of the
 * elements to the start of the vector.
 * @param array A reference to the input std::vector
 * @param shift The amount to be shifted to the right
 * @returns A std::vector with the shifted values
 */
std::vector<int32_t> shift_right(const std::vector<int32_t> &array,
                                 size_t shift) {
    if (array.size() <= shift) {
        return {};  ///< We got an invalid shift, return empty array
    }
    std::vector<int32_t> res(array.size());  ///< Result array
    for (size_t i = shift; i < array.size(); i++) {
        res[i] = array[i - shift];  ///< Add values after the shift index
    }
    for (size_t i = 0; i < shift; i++) {
        res[i] =
            array[array.size() - shift + i];  ///< Add the values from the start
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
using operations_on_datastructures::shift_right;
/**
 * @brief A Test to check an simple case
 * @returns void
 */
void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {4, 5, 1, 2, 3}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 2);
    std::vector<int32_t> expected = {4, 5, 1, 2, 3};
    assert(res == expected);
    print(res);  ///< Should print 4 5 1 2 3
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check an empty vector
 * @returns void
 */
void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Initialized arr = {}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> arr = {};
    std::vector<int32_t> res = shift_right(arr, 2);
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);  ///< Should print empty newline
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check an invalid shift value
 * @returns void
 */
void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 7);  ///< 7 > 5
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);  ///< Should print empty newline
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check a very large input
 * @returns void
 */
void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Initialized arr = {2, 4, ..., 420}\n";
    std::cout << "Expected result: {420, 2, 4, ..., 418}\n";
    std::vector<int32_t> arr;
    for (int i = 1; i <= 210; i++) {
        arr.push_back(i * 2);
    }
    print(arr);
    std::vector<int32_t> res = shift_right(arr, 1);
    std::vector<int32_t> expected;
    expected.push_back(420);
    for (int i = 0; i < 209; i++) {
        expected.push_back(arr[i]);
    }
    assert(res == expected);
    print(res);  ///< Should print {420, 2, 4, ..., 418}
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check a shift of zero
 * @returns void
 */
void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {1, 2, 3, 4, 5}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 0);
    assert(res == arr);
    print(res);  ///< Should print 1 2 3 4 5
    std::cout << "TEST PASSED!\n\n";
}
}  // namespace tests

/**
 * @brief Function to test the correctness of shift_right() function
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
