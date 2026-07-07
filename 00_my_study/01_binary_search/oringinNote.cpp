/******************************************************************************
 * Binary search is a search algorithm that finds the position of a target value
 * within a sorted array.Just like looking for a word in a dictionary, in binary
 * search we compare the target value to the middle element of the array. If
 * they are not equal, then the half in which the target cannot lie is
 * eliminated and the search continues on the remaining half, again taking the
 * middle element to compare to the target value, and repeating this until the
 * target value is found. If the search ends with the remaining half being
 * empty, the target is not in the array.
 *
 * ### Implementation
 *
 * Binary search works on sorted arrays. It begins by comparing an
 * element in the middle of the array with the target value. If the target value
 * matches the element, its position in the array is returned. If the target
 * value is less than the element, the search continues in the lower half of
 * the array. If the target value is greater than the element, the search
 * continues in the upper half of the array. By doing this, the algorithm
 * eliminates the half in which the target value cannot lie in each iteration.
 *
 * ### Complexities
 *
 * //n is the number of element in the array.
 *
 * Worst-case time complexity	O(log n)
 * Best-case time complexity	O(1)
 * Average time complexity	    O(log n)
 * space complexity  0(1)
 * Worst-case space complexity  0(1)
 *******************************************************************************/
#include <algorithm>  /// for std::sort function
#include <cassert>    /// for std::assert
#include <cstdint>     ///處理unit64_t
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

namespace search {

namespace binary_search {

uint64_t binarySearch(std::vector<uint64_t> arr, uint64_t val) {
    uint64_t low = 0;                // set the lowest point of the vector.
    uint64_t high = arr.size() - 1;  // set the highest point of the vector.

    while (low <= high) {
        uint64_t m = low + (high - low) / 2;  // set the pivot point

        if (val == arr[m]) {
            return m;
        } else if (val < arr[m]) {
            high = m - 1;
        } else {
            low = m + 1;
        }
    }
    return -1;
}

}  // namespace binary_search

}  // namespace search

static void test1() {
    // testcase #1
    // array = [1,3,5,7,9,8,6,4,2] , Value = 4
    // should return 3

    std::vector<uint64_t> arr = {{1, 3, 5, 7, 9, 8, 6, 4, 2}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans = 3;
    uint64_t derived_ans = search::binary_search::binarySearch(arr, 4);
    std::cout << "Test #1: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

void test2() {
    // testcase #2
    // array = [1,23,25,4,2] , Value = 25
    // should return 4
    std::vector<uint64_t> arr = {{1, 23, 25, 4, 2}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans = 4;
    uint64_t derived_ans = search::binary_search::binarySearch(arr, 25);
    std::cout << "Test #2: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

void test3() {
    // testcase #3
    // array = [1,31,231,12,12,2,5,51,21,23,12,3] , Value = 5
    // should return 8
    std::vector<uint64_t> arr = {{1, 31, 231, 12, 2, 5, 51, 21, 23, 12, 3}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans = 8;
    uint64_t derived_ans = search::binary_search::binarySearch(arr, 31);
    std::cout << "Test #3: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

int main() {
    test1();  // run self-test implementation #1
    test2();  // run self-test implementation #2
    test3();  // run self-test implementation #3

    return 0;
}
