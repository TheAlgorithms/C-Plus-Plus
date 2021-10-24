/**
 * @file
 * @brief Implementation for the [Intersection of two sorted
 * Arrays](https://en.wikipedia.org/wiki/Intersection_(set_theory))
 * algorithm.
 * @details The intersection of two arrays is the collection of all the elements
 * that are common in both the first and second arrays. This implementation uses
 * ordered arrays, and an algorithm to correctly order them and return the
 * result as a new array (vector).
 * @see union_of_two_arrays.cpp
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <algorithm>  /// for std::sort
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

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
 * @brief Gets the intersection of two sorted arrays, and returns them in a
 * vector.
 * @details An algorithm is used that compares the elements of the two vectors,
 * incrementing the index of the smaller of the two. If the elements are the
 * same, the element is appended to the result array to be returned.
 * @param first A std::vector of sorted integer values
 * @param second A std::vector of sorted integer values
 * @returns A std::vector of the intersection of the two arrays, in ascending
 * order
 */
std::vector<int32_t> get_intersection(const std::vector<int32_t> &first,
                                      const std::vector<int32_t> &second) {
    std::vector<int32_t> res;         ///< Vector to hold the intersection
    size_t f_index = 0;               ///< Index for the first array
    size_t s_index = 0;               ///< Index for the second array
    size_t f_length = first.size();   ///< Length of first array
    size_t s_length = second.size();  ///< Length of second array

    while (f_index < f_length && s_index < s_length) {
        if (first[f_index] < second[s_index]) {
            f_index++;  ///< Increment index of second array
        } else if (first[f_index] > second[s_index]) {
            s_index++;  ///< Increment index of second array
        } else {
            if ((res.size() == 0) || (first[f_index] != res.back())) {
                res.push_back(
                    first[f_index]);  ///< Add the element if it is unique
            }
            f_index++;  ///< Increment index of first array
            s_index++;  ///< Increment index of second array too
        }
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief Testcases to check intersection of Two Arrays.
 */
namespace tests {
using operations_on_datastructures::get_intersection;
using operations_on_datastructures::print;
/**
 * @brief A Test to check an edge case (two empty arrays)
 * @returns void
 */
void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Intialized a = {} b = {}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);  ///< Check if result is empty
    print(result);        ///< Should only print newline
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check an edge case (one empty array)
 * @returns void
 */
void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Intialized a = {} b = {2, 3}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);  ///< Check if result is equal to a
    print(result);        ///< Should only print newline
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check correct functionality with a simple test case
 * @returns void
 */
void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Intialized a = {4, 6} b = {3, 6}\n";
    std::cout << "Expected result: {6}\n";
    std::vector<int32_t> a = {4, 6};
    std::vector<int32_t> b = {3, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {6};
    assert(result == expected);  ///< Check if result is correct
    print(result);               ///< Should print 6
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check correct functionality with duplicate values
 * @returns void
 */
void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Intialized a = {4, 6, 6, 6} b = {2, 4, 4, 6}\n";
    std::cout << "Expected result: {4, 6}\n";
    std::vector<int32_t> a = {4, 6, 6, 6};
    std::vector<int32_t> b = {2, 4, 4, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {4, 6};
    assert(result == expected);  ///< Check if result is correct
    print(result);               ///< Should print 4 6
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check correct functionality with a harder test case
 * @returns void
 */
void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Intialized a = {1, 2, 3, 4, 6, 7, 9} b = {2, 3, 4, 5}\n";
    std::cout << "Expected result: {2, 3, 4}\n";
    std::vector<int32_t> a = {1, 2, 3, 4, 6, 7, 9};
    std::vector<int32_t> b = {2, 3, 4, 5};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {2, 3, 4};
    assert(result == expected);  ///< Check if result is correct
    print(result);               ///< Should print 2 3 4
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check correct functionality with an array sorted using
 * std::sort
 * @returns void
 */
void test6() {
    std::cout << "TEST CASE 6\n";
    std::cout << "Intialized a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2} ";
    std::cout << "b = {11, 3, 7, 8, 6}\n";
    std::cout << "Expected result: {3, 7}\n";
    std::vector<int32_t> a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2};
    std::vector<int32_t> b = {11, 3, 7, 8, 6};
    std::sort(a.begin(), a.end());  ///< Sort vector a
    std::sort(b.begin(), b.end());  ///< Sort vector b
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {3, 7};
    assert(result == expected);  ///< Check if result is correct
    print(result);               ///< Should print 3 7
    std::cout << "TEST PASSED!\n\n";
}
}  // namespace tests

/**
 * @brief Function to test the correctness of get_intersection() function
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
    tests::test6();
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
