/******************************************************************************
 * @file
 * @brief [Binary search
 * algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * [2D Matrix](https://en.wikipedia.org/wiki/Array_(data_structure)#Multidimensional_arrays)
 * @details
 *  The problem statement states that the values of the last col of the ith row is greater than the first col of (i+1)th row. Also, each row is sorted.
 *  This means that, if we linearly arrange the elements of each row, we will have a sorted array. So we can now perform a binary search over it.
 *  How will the matrix behave like an array without actually creating an auxiliary array?
 *  It could be achieved by the following formula :
 *  A n * m matrix converted into an array: matrix[x][y] : a[x * m + y]
 *  An array can be converted into n * m matrix: a[x] : matrix[x / m][x % m]
 *
 * ### Implementation
 *
 * Operate the matrix as an array using the above formula
 * Perform a binary search for the target element over the matrix
 *
 * ### Complexities
 *
 * //n is the number of element in the array.
 *
 * Worst-case time complexity	O(log (n*m)) = O(log(n) + log(m))
 * Best-case time complexity	O(1)
 * Average time complexity	    O(log (n*m)) = O(log(n) + log(m))
 * Worst-case space complexity  0(1)
 *
 * @author [Shantanu](https://github.com/shy0980)
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
uint64_t binarySearch2DMatrix(std::vector<std::vector<uint64_t>> matrix, uint64_t target) {
    uint64_t n = matrix.size();      // the number of rows
    uint64_t m = matrix[0].size();    // the number of colums

    if(n == 0 || m == 0)     // if matrix have 0 rows or 0 colums
        return -1;

    uint64_t low = 0;                // set the lowest point of the vector.
    uint64_t high = m*n-1 ;  // set the highest point of the vector.

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;  // set the pivot point
        uint64_t current = matrix[mid/m][mid%m];  // as per formule 

        if( target == current) {
            return mid;
        }
        else if (target < current)  {
            high = mid - 1 ; // for left half
        }
        else{
            low = mid + 1 ; // for right half 
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
    // Matrix = {{1, 3, 5, 7}, 
    //           {10, 11, 16, 20},
    //           {23, 30 , 34 , 210}} , rows = 3, columes = 4
    // should return 6 (the net index)
    int n = 3, m = 4;
    std::vector<std::vector<uint64_t>> arr = {{1, 3, 5, 7}, {10, 11, 16, 20},{23, 30 , 34 , 210}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans_row = 1, expected_ans_col = 2;
    uint64_t derived_ans = search::binary_search::binarySearch2DMatrix(arr, 16);
    int row = derived_ans/m;
    int column = derived_ans%m;
    std::cout << "Test #1: ";
    if( row == expected_ans_row && column == expected_ans_col ) {
        std::cout << "Test Passed \n";
    }
    else{
        std::cout << "Test failed \n";
    }
}

static void test2() {
    // testcase #2
    // Matrix = {{3, 5, 6, 7}, 
    //           {10, 13, 16, 19},
    //           {20, 30 , 37 , 42}} , rows = 3, columes = 4
    // should return 6 (the net index)
    int n = 3, m = 4;
    std::vector<std::vector<uint64_t>> arr = {{3, 5, 6, 7},{10, 13, 16, 19},{20, 30 , 37 , 42}};
    std::sort(arr.begin(), arr.end());
    uint64_t expected_ans_row = 1, expected_ans_col = 2;
    uint64_t derived_ans = search::binary_search::binarySearch2DMatrix(arr, 25);
    int row = derived_ans/m;
    int column = derived_ans%m;
    std::cout << "Test #1: ";
    if( row == expected_ans_row && column == expected_ans_col ) {
        std::cout << "Test Passed \n";
    }
    else{
        std::cout << "Test failed \n";
    }
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test1();  // run self-test implementation #1
    test2();  // run self-test implementation #2
    return 0;
}
