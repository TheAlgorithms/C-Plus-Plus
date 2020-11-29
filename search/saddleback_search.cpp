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