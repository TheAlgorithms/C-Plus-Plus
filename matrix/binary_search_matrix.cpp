/**
 * @file
 * @brief [Binary Search in a 2d array](https://www.geeksforgeeks.org/searching-algorithms-for-a-2d-arrays-matrix/)
 * in C++
 * @details
 *      Binary search is an efficient divide-and-conquer searching algorithm . 
 *      It works by repeatedly dividing the search space in half, eliminating half of the elements each time, until the target element is found or it is determined that the element is not present in the array. 
 *      It can only be applied to sorted matrixes(row-wise or column-wise).
 *
 * ### Complexities
 *
 * //n, m is the number rows and columns in the array.
 *
 * Worst-case time complexity	O(log (n*m)
 * Average time complexity	    O(log (n*m) 
 * Best-case time complexity	O(1)
 * Worst-case space complexity  0(1)
 */

#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <algorithm> /// fro std::is_sorted
#include <cassert>   /// for assert

template <typename T>
std::vector<int> binary_search_matrix(const std::vector<std::vector<T>>& matrix, const T& target){

    if(matrix.empty() || matrix[0].empty()){
        return {-1, -1};
    }

    for (const auto& row : matrix) {

        if (!std::is_sorted(row.begin(), row.end())) {
            return {-1, -1};
        }
    }
    
    int m = matrix.size();
    int n = matrix[0].size();
    int i = 0, j = m*n-1;

    while(i <= j){

        int mid = i + (j-i) / 2;
        T midValue = matrix[mid/n][mid%n];

        if(midValue == target){
            return {mid/n, mid%n};
        }
        else if(midValue < target){
            i = mid + 1;
        } 
        else{
            j = mid - 1;
        }
    }

    return {-1, -1};
}

/*******************************************************************************
 * @brief Self-test implementation #1
 * @returns void
 *******************************************************************************/
static void test1() {
    // testcase #1
    // array = [[1, 2, 3],
    //          [4, 5, 6],
    //          [7, 8, 9]] 
    // Value = 3
    // should return {0, 2}

    std::vector<std::vector<int>> intMatrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<int> expected_ans = {2, 1};
    std::vector<int> derived_ans = binary_search_matrix(intMatrix, 8);
    std::cout << "Test #1: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementation #2
 * @returns void
 *******************************************************************************/
static void test2() {
    // testcase #2
    // array = [[1.1, 2.2, 3.3],
    //          [4.4, 5.5, 6.6],
    //          [7.7, 8.8, 9.9] 
    // Value = 6.6
    // should return {1, 2}

    std::vector<std::vector<double>> doubleMatrix = {
        {1.1, 2.2, 3.3},
        {4.4, 5.5, 6.6},
        {7.7, 8.8, 9.9}
    };
    std::vector<int> expected_ans = {0, 0};
    std::vector<int> derived_ans = binary_search_matrix(doubleMatrix, 1.1);
    std::cout << "Test #2: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementation #3
 * @returns void
 *******************************************************************************/
static void test3() {
    // testcase #3
    // array = [['a', 'b', 'c'],
    //          ['f', 'e', 'd'],
    //          ['g', 'j', 'x'] 
    // Value = 'x'
    // should return {2, 2}

    std::vector<std::vector<char>> charMatrix = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'} 
    };
    std::vector<int> expected_ans = {2, 1};
    std::vector<int> derived_ans = binary_search_matrix(charMatrix, 'h');
    std::cout << "Test #3: ";
    assert(derived_ans == expected_ans);
    std::cout << "Passed!" << std::endl;
}

int main() {
    
    test1(); // run self-test implementation #1
    test2(); // run self-test implementation #2
    test3(); // run self-test implementation #3

    return 0;
}
