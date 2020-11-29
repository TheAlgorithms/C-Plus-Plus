/**
 * @file saddleback_search.cpp
 * @brief Implementation of saddleback algorithm for 2D arrays.
 *
 * @details
 * Saddleback Algorithm is an algorithm that searches 2D array in linear time,
 * i.e, O(m + n), where m is row and n is column of 2D array. Also, each row and
 * column of the matrix should be sorted beforehand for this algorithm to work.
 *
 * @author [Hashir Niazi](https://github.com/HashirGJ8842)
 */
#include <cassert>
#include <iostream>
#include <vector>

/** \namespace search
 * \brief Algorithms for searching
 */
namespace search {
/** \namespace saddleback
 * \brief Function for implementing Saddleback Algorithm.
 */
namespace saddleback {
/**
 * This function implements saddleback
 * @param matrix , a 2D matrix which is sorted on the basis of rows and columns
 * @param element , the element which is needed to be searched
 * @return An std::pair of with row and column populated within it, if the
 * element is present.
 * @return An std::pair with (-1, -1), if the element is not present.
 */
std::pair<int, int> saddleback(std::vector<std::vector<int>> matrix,
                               int element) {
    int left_index = 0;
    int right_index = matrix[0].size() - 1;  // Start from top right corner
    while (left_index < matrix.size() &&
           right_index >=
               0) {  // Exit once the value of indexes get out of range.
        if (element ==
            matrix[left_index]
                  [right_index]) {  // If value on this position of matrix is
                                    // equal to element, return (row, column).
            return std::pair<int, int>(left_index, right_index);
        } else if (element >
                   matrix[left_index]
                         [right_index]) {  // Else if value on this position of
                                           // matrix is less than the element,
                                           // move left.
            ++left_index;
        } else if (element <
                   matrix[left_index]
                         [right_index]) {  // Else if value on this position of
                                           // matrix is greater than the
                                           // element, move down.
            --right_index;
        }
    }
    return std::pair<int, int>(
        -1, -1);  // If the program reaches here, that means one of the index
                  // went out of index, hence no element present.
}
}  // namespace saddleback
}  // namespace search

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    std::vector<std::vector<int>> matrix = {{1, 10, 100, 1000, 10000},
                                            {2, 20, 200, 2000, 20000},
                                            {3, 30, 300, 3000, 30000},
                                            {4, 40, 400, 4000, 40000},
                                            {5, 50, 500, 5000, 50000}};

    std::pair<int, int> not_found = std::pair<int, int>(-1, -1);
    std::pair<int, int> test_answer;
    // Test 1
    std::pair<int, int> answer1 = search::saddleback::saddleback(matrix, 123);
    assert(not_found == answer1);
    // Test 2
    answer1 = search::saddleback::saddleback(matrix, 0);
    assert(not_found == answer1);
    // Test 3
    answer1 = search::saddleback::saddleback(matrix, 1);
    test_answer = std::pair<int, int>(0, 0);
    assert(test_answer == answer1);
    // Test 4
    answer1 = search::saddleback::saddleback(matrix, 50000);
    test_answer = std::pair<int, int>(4, 4);
    assert(test_answer == answer1);
    // Test 5
    answer1 = search::saddleback::saddleback(matrix, 300);
    test_answer = std::pair<int, int>(2, 2);
    assert(test_answer == answer1);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing
    test();
    return 0;
}