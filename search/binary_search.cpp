/******************************************************************************
 * @file
 * @brief [Binary search
 * algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * @details
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
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @author Unknown author
 *******************************************************************************/

#include <algorithm>  /// for std::sort function
#include <cassert>    /// for std::assert
#include <cstdint>
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
/******************************************************************************
 * @namespace search
 * @brief Searching algorithms
 *******************************************************************************/
namespace search {

/******************************************************************************
 * @namespace binary_search
 * @brief Binary search searching algorihm
 *******************************************************************************/
namespace binary_search {

/******************************************************************************
 * @brief The main function which implements binary search
 * @param arr vector to be searched in
 * @param val value to be searched
 * @returns @param int index of val in vector arr
 *******************************************************************************/
int64_t binarySearch(const std::vector<int64_t> & arr, const int64_t val) {
    if (arr.empty()) {
        return -1;  // if the array is empty, return -1.
    }
     int64_t low = 0;  // set the lowest point of the vector.
     int64_t high = (int64_t)arr.size() - 1; // set the highest point of the vector.

    while (low <= high) {
        int64_t mid = low + (high - low) / 2;  // set the pivot point

        if (val == arr[mid]) {
            return mid;
        } /****************************************************
           * if pivot point is the val, return it,
           * else check if val is greater or smaller than pivot value
           * and set the next pivot point accordingly.
           ****************************************************/
        else if (val < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;  // if val is not in the array, return -1.
}

}  // namespace binary_search

}  // namespace search

/*******************************************************************************
 * @brief Self-test implementation #1
 * @returns void
 *******************************************************************************/
static void test1() {
    // testcase #1
    // array = [1,3,5,7,9,8,6,4,2] , Value = 4
    // should return 3

    std::vector<int64_t> arr = {{1, 3, 5, 7, 9, 8, 6, 4, 2}};
    std::sort(arr.begin(), arr.end());
    int64_t expected_ans = 3;
    int64_t derived_ans = search::binary_search::binarySearch(arr, 4);
    std::cout << "Test #1: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementation #2
 * @returns void
 *******************************************************************************/
void test2() {
    // testcase #2
    // array = [1,23,25,4,2] , Value = 25
    // should return 4
    std::vector<int64_t> arr = {{1, 23, 25, 4, 2}};
    std::sort(arr.begin(), arr.end());
    int64_t expected_ans = 4;
    int64_t derived_ans = search::binary_search::binarySearch(arr, 25);
    std::cout << "Test #2: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementation #3
 * @returns void
 *******************************************************************************/
void test3() {
    // testcase #3
    // array = [1,31,231,12,12,2,5,51,21,23,12,3] , Value = 31
    // should return 8
    std::vector<int64_t> arr = {{1, 31, 231, 12, 2, 5, 51, 21, 23, 12, 3}};
    std::sort(arr.begin(), arr.end());
    int64_t expected_ans = 8;
    int64_t derived_ans = search::binary_search::binarySearch(arr, 31);
    std::cout << "Test #3: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}
/*******************************************************************************
 * @brief Self-test implementation #4
 * @returns void
 *******************************************************************************/
void test4() {
    // testcase #4
    // array = [] , Value = 5
    // should return -1
    std::vector<int64_t> arr = {};
    std::sort(arr.begin(), arr.end());
    int64_t expected_ans = -1;
    int64_t derived_ans = search::binary_search::binarySearch(arr, 5);
    std::cout << "Test #4: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}
/*******************************************************************************
 * @brief Self-test implementation #5
 * @returns void
 *******************************************************************************/
void test5() {
    // testcase #5
    // array = [-20,20,50,-100,-5,20,-10] , Value = -10
    // should return 2
    std::vector<int64_t> arr = {{-20, 20, 50, -100, -5, 20, -10}};
    std::sort(arr.begin(), arr.end());
    int64_t expected_ans = 2;
    int64_t derived_ans = search::binary_search::binarySearch(arr, -10);
    std::cout << "Test #5: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test1();  // run self-test implementation #1
    test2();  // run self-test implementation #2
    test3();  // run self-test implementation #3
    test4();  // run self-test implementation #4
    test5();  // run self-test implementation #5

    return 0;
}
