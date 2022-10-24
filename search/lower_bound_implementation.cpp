/******************************************************************************
 * @file
 * @brief [Lower Bound Binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * @details
 * Binary search is a search algorithm that finds the position of a target value
 * within a sorted array. Binary search compares the target value to the middle
 * element of the array. If they are not equal, the half in which the target
 * cannot lie is eliminated and the search continues on the remaining half,
 * again taking the middle element to compare to the target value, and repeating
 * this until the target value is found. If the search ends with the remaining
 * half being empty, the target is not in the array.
 *
 * ### Implementation
 *
 * Binary search works on sorted arrays. Binary search begins by comparing an
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
 * Worst-case space complexity  0(1)
 *
 * @author [Priyanshu Vaishnav](https://github.com/PranshVaishnav)
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
 * @namespace binary_search_modified
 * @brief Binary search modified searching algorihm
 *******************************************************************************/
namespace binary_search_modified {

/******************************************************************************
 * @brief The main function which implements binary search
 * @param arr vector to be searched in
 * @param val value to be searched
 * @returns @param int index of val in vector arr
 *******************************************************************************/
uint64_t binarySearch(std::vector<uint64_t> arr, uint64_t val) {
    uint64_t mid;
    uint64_t N = arr.size();
    uint64_t low = 0;   // set the lowest point of the vector.
    uint64_t high = N;  // set the highest point of the vector.

    // Till low is less than high
    while (low < high) {
        mid = low + (high - low) / 2;  // set the pivot point

        if (val <= arr[mid]) {
            /****************************************************
             * if pivot point is less than or equal to the val, then find in the
             *left subarray
             ****************************************************/
            high = mid;
        }
            /****************************************************
            * if pivot point is greater than val, then find in the right subarray
            ****************************************************/
        else {
            low = mid + 1;
        }
    }

    // if VAL is greater than arr[n-1]
    if (low < N && arr[low] < val) {
        low++;
    }
    //return the lower bound index
    return low;
}

}  // namespace binary_search_modified

}  // namespace search

 /*******************************************************************************
 * @brief Self-test implementation #1
 * @returns void
 *******************************************************************************/
static void test1() {
    // testcase #1
    // array = [5,7,7,8,8,10] , Value = 8
    // should return 3

    std::vector<uint64_t> arr = {{5,7,7,8,8,10}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans = 3;
    uint64_t derived_ans = search::binary_search_modified::binarySearch(arr, 8);
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
    // array = [5,7,7,8,8,10] , Value = 6
    // should return 1
    std::vector<uint64_t> arr = {{5,7,7,8,8,10}};
    uint64_t expected_ans = 1;
    uint64_t derived_ans = search::binary_search_modified::binarySearch(arr, 6);
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
    // array = [5,7,7,8,8,10] , Value = 11
    // should return 6
    std::vector<uint64_t> arr = {{5,7,7,8,8,10}};
    uint64_t expected_ans = 6;
    uint64_t derived_ans = search::binary_search_modified::binarySearch(arr, 11);
    std::cout << "Test #3: ";
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

    return 0;
}