/**
 * @file
 * @brief [Linear Search in a 2d array](https://www.geeksforgeeks.org/searching-algorithms-for-a-2d-arrays-matrix/)
 * in C++
 * @details
 *      Linear search is a simple and sequential searching algorithm. 
 *      It is used to find whether a particular element is present in the array or not by traversing every element in the array.
 *
 * ### Complexities
 *
 * //n, m is the number rows and columns in the array.
 *
 * Worst-case time complexity	O(n*m) => linear
 * Average time complexity	    O(n*m) => linear
 * Best-case time complexity	O(1)   => constant
 * Worst-case space complexity  0(1)   => constant
 */

#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <cassert>   /// for assert

template <typename T>
std::vector<int> linear_search_matrix(const std::vector<std::vector<T>>& matrix, const T& target){

    if(matrix.empty() || matrix[0].empty()){
        return {-1, -1};
    }
    
    int rows = matrix.size();
    int columns = matrix[0].size();

    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < columns; j++){
            if(matrix[i][j] == target){
                return {i, j};
            }
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
    std::vector<int> expected_ans = {0, 2};
    std::vector<int> derived_ans = linear_search_matrix(intMatrix, 3);
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
        {12.6, 8.8, 9.9}
    };
    std::vector<int> expected_ans = {1, 2};
    std::vector<int> derived_ans = linear_search_matrix(doubleMatrix, 6.6);
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
        {'f', 'e', 'd'},
        {'g', 'j', 'x'} 
    };
    std::vector<int> expected_ans = {2, 2};
    std::vector<int> derived_ans = linear_search_matrix(charMatrix, 'x');
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
