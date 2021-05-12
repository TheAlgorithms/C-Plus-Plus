/**
 * @file
 * @author [Aditya Prakash](https://adityaprakash.tech)
 * @brief This is an implementation of a recursive version of the [Bubble sort algorithm](https://www.geeksforgeeks.org/recursive-bubble-sort/)
 *
 * @details
 * The working principle of the Bubble sort algorithm.

 * Bubble sort is a simple sorting algorithm used to rearrange a set of ascending or descending order elements.
 * Bubble sort gets its name from the fact that data "bubbles" to the top of the dataset.
 
 * ### Algorithm

 * What is Swap?

 * To swap two numbers mean that we interchange their values.
 * An additional variable is required for this operation. x = 5, y = 10.
 * We want x = 10, y = 5. Here we create the most variable to do it.

 * int z;
 * z = x;
 * x = y;
 * y = z;

 * The above process is a typical displacement process.
 * When x assigns the value to x, the old value of x is lost.
 * That's why we created a variable z to create the first value of the value of x,
 * and finally, we have assigned to y.

 * Recursion

 * While the recursive method does not necessarily have advantages over iterative
 * versions, but it is useful to enhance the understanding of the algorithm and
 * recursion itself. In Recursive Bubble sort algorithm, we firstly call the
 * function on the entire array, and for every subsequent function call, we exclude
 * the last element. This fixes the last element for that sub-array.Formally, for
 * `ith` iteration, we consider elements up to n-i, where n is the number of
 * elements in the array. Exit condition: n==1; i.e. the sub-array contains only
 * one element.

 * Complexity
 * Time complexity: O(n) best case; O(n²) average case; O(n²) worst case
 * Space complexity: O(n)

 * We need to traverse the array `n * (n-1)` times. However, if the entire array is
 * already sorted, then we need to traverse it only once. Hence, O(n) is the best case
 * complexity
*/

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <array>     /// for std::array
#include <algorithm> /// for std::is_sorted

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {

/**
 * @brief This is an implementation of the recursive_bubble_sort. A vector is passed
 * to the function which is then dereferenced, so that the changes are
 * reflected in the original vector. It also accepts a second parameter of
 * type `int` and name `n`, which is the size of the array.
 * 
 * @tparam T type of data variables in the array
 * @param nums our array of elements.
 * @param n size of the array
 */
template <typename T>
void recursive_bubble_sort(std::vector<T> *nums, int n) {
    if (n == 1) {  //!< base case; when size of the array is 1
        return;
    }

    for (int i = 0; i < n - 1; i++) {  //!< iterating over the entire array
        //!< if a larger number appears before the smaller one, swap them.
        if ((*nums)[i] > (*nums)[i + 1]) {
            std::swap((*nums)[i], (*nums)[i + 1]);
        }
    }

    //!< calling the function after we have fixed the last element
    recursive_bubble_sort(nums, n - 1);
}
}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st example. Creating an array of type `int`.
    std::cout << "1st test using `int`\n";
    const int size = 6;
    std::vector<int> arr;
    //populating the array
    arr.push_back(22);
    arr.push_back(46);
    arr.push_back(94);
    arr.push_back(12);
    arr.push_back(37);
    arr.push_back(63);
    // array populating ends

    sorting::recursive_bubble_sort(&arr, size);
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
    std::cout << " 1st test passed!\n";
    // printing the array
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;

    // 2nd example. Creating an array of type `double`.
    std::cout << "2nd test using doubles\n";
    std::vector<double> double_arr;

    //populating the array
    double_arr.push_back(20.4);
    double_arr.push_back(62.7);
    double_arr.push_back(12.2);
    double_arr.push_back(43.6);
    double_arr.push_back(74.1);
    double_arr.push_back(57.9);
    //array populating ends

    sorting::recursive_bubble_sort(&double_arr, size);
    assert(std::is_sorted(std::begin(double_arr), std::end(double_arr)));
    std::cout << " 2nd test passed!\n";
    // printing the array
    for (int i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;

}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() { 
    test();  // run self-test implementations
    return 0;
}
