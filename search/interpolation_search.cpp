
/******************************************************************************
 * @file
 * @brief [Interpolation search
 * algorithm](https://en.wikipedia.org/wiki/interpolation_search)
 *
 * @details
 * interpolation search resembles the method by which people search a telephone
 * directory for a name (the key value by which the book's entries are ordered):
 * in each step the algorithm calculates where in the remaining search space
 * the sought item might be, based on the key values at the bounds of the search
 * space and the value of the sought key, usually via a linear interpolation.
 * The key value actually found at this estimated position is then compared to
 * the key value being sought. If it is not equal, then depending on the
 * comparison, the remaining search space is reduced to the part before or
 * after the estimated position. This method will only work if calculations
 * on the size of differences between key values are sensible.

 * ### Complexities
 *
 * //n is the number of element in the array.
 *
 * Worst-case time complexity	O(n)                (when items are distributed
 exponentially)
 * Average time complexity	    O(log2(log2 n))
 * space complexity  0(1)
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @author Unknown author
 *******************************************************************************/

#include <algorithm>  /// for std::sort function
#include <cassert>    /// for std::assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/******************************************************************************
 * @namespace search
 * @brief Searching algorithms
 *******************************************************************************/
namespace search {

/******************************************************************************
 * @namespace interpolation_search
 * @brief Functions for the [Interpolation
 *Search](https://en.wikipedia.org/wiki/interpolation_search) algorithm
 *implementation
 *******************************************************************************/
namespace interpolation_search {

/******************************************************************************
 * @brief The main function which implements interpolation search
 * @param arr vector to be searched in
 * @param number value to be searched
 * @returns integer index of `number` in vector `arr`
 *******************************************************************************/
uint64_t interpolationSearch(const std::vector<uint64_t> &arr,
                             uint64_t number) {
    uint64_t size = arr.size();
    uint64_t low = 0, high = (size - 1);

    // Since vector is sorted, an element present in array must be in range
    // defined by corner
    while (low <= high && number >= arr[low] && number <= arr[high]) {
        if (low == high) {
            if (arr[low] == number) {
                return low;
            }
            return -1;
        }
        // Probing the position with keeping uniform distribution in mind.
        uint64_t pos =
            low +
            ((static_cast<uint64_t>(high - low) / (arr[high] - arr[low])) *
             (number - arr[low]));

        if (arr[pos] == number) {
            return pos;  // Condition of target found
        }

        if (arr[pos] < number) {
            low = pos + 1;  // If x is larger, x is in upper part
        }

        else {
            high = pos - 1;  // If x is smaller, x is in the lower part
        }
    }
    return -1;
}

}  // namespace interpolation_search

}  // namespace search

/*******************************************************************************
 * @brief Self-test implementation
 * @returns void
 *******************************************************************************/
static void tests() {
    // testcase
    // array = [10, 12, 13, 16, 18, 19, 20, 21, 1, 2, 3, 4, 22, 23, 24, 33, 35,
    // 42, 47] , Value = 33 should return 15
    std::vector<uint64_t> arr = {{10, 12, 13, 16, 18, 19, 20, 21, 1, 2, 3, 4,
                                  22, 23, 24, 33, 35, 42, 47}};
    sort(arr.begin(), arr.end());
    uint64_t number = 33;  // Element to be searched
    uint64_t expected_answer = 15;
    uint64_t derived_answer =
        search::interpolation_search::interpolationSearch(arr, number);
    std::cout << "Testcase: ";
    assert(derived_answer == expected_answer);
    std::cout << "Passed!\n";
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    tests();  // run self-test implementations
    return 0;
}
