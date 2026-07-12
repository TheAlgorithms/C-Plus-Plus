/**
 * @file
 * @brief An algorithm to calculate the sum of [Fibonacci
 * Sequence](https://en.wikipedia.org/wiki/Fibonacci_number): \f$\mathrm{F}(n) +
 * \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 * @details An algorithm to calculate the sum of Fibonacci Sequence:
 * \f$\mathrm{F}(n) + \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$ where
 * \f$\mathrm{F}(i)\f$ denotes the i-th Fibonacci Number . Note that F(0) = 0
 * and F(1) = 1. The value of the sum is calculated using matrix exponentiation.
 * Reference source:
 * https://stackoverflow.com/questions/4357223/finding-the-sum-of-fibonacci-numbers
 * @author [Sarthak Sahu](https://github.com/SarthakSahu1009)
 */

#include <cassert>   /// for assert
#include <cstdint>
#include <iostream>  /// for std::cin and std::cout
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace fibonacci_sum
 * @brief Functions for the sum of the Fibonacci Sequence: \f$\mathrm{F}(n) +
 * \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 */
namespace fibonacci_sum {
using matrix = std::vector<std::vector<uint64_t> >;

/**
 * Function to multiply two matrices
 * @param matrix_a First matrix 
 * @param matrix_b Second martix 
 * @returns resultant matrix
 * @complexity Time Complexity : $O(1)$ because the matrix size is a fixed 2x2. Space Complexity: $O(1)$.
 */
math::fibonacci_sum::matrix multiply(const math::fibonacci_sum::matrix &matrix_a,
                                     const math::fibonacci_sum::matrix &matrix_b) {
    math::fibonacci_sum::matrix result(2, std::vector<uint64_t>(2, 0));

    // multiplying matrices
    result[0][0] = matrix_a[0][0] * matrix_b[0][0] + matrix_a[0][1] * matrix_b[1][0];
    result[0][1] = matrix_a[0][0] * matrix_b[0][1] + matrix_a[0][1] * matrix_b[1][1];
    result[1][0] = matrix_a[1][0] * matrix_b[0][0] + matrix_a[1][1] * matrix_b[1][0];
    result[1][1] = matrix_a[1][0] * matrix_b[0][1] + matrix_a[1][1] * matrix_b[1][1];

    return result;
}

/**
 * Function to compute base_matrix^exponent where base_matrix is a matrix.
 * @param base_matrix The matrix to be exponentiated
 * @param exponent The power to raise the matrix to
 * @returns resultant matrix
 * @complexity Time Complexity: $O(\log(\text{exponent}))$ due to divide and conquer approach. Space Complexity: $O(\log(\text{exponent}))$ due to the recursion stack.
 */
math::fibonacci_sum::matrix power(math::fibonacci_sum::matrix base_matrix, uint64_t exponent) {
    const math::fibonacci_sum::matrix transformation_matrix{{1, 1}, {1, 0}};
    if (exponent == 0 || exponent == 1) {
        return base_matrix;
    }

    base_matrix = power(base_matrix, exponent / 2);
    base_matrix = multiply(base_matrix, base_matrix);
    if (exponent & 1) {
        base_matrix = multiply(base_matrix, transformation_matrix);
    }
    return base_matrix;
}

/**
 * Function to compute sum of fibonacci sequence from 0 to limit.
 * @param limit The upper bound of the sequence
 * @returns uint64_t ans, the sum of sequence
 * @complexity Time Complexity: $O(\log(\text{limit}))$. Space Complexity: $O(\log(\text{limit}))$.
 */
uint64_t result(uint64_t limit) {
    const math::fibonacci_sum::matrix initial_matrix{{1, 1}, {1, 0}};
    math::fibonacci_sum::matrix base_matrix = initial_matrix;
    
    base_matrix = power(base_matrix, limit);
    uint64_t ans = base_matrix[0][1];
    ans = (ans - 1);
    return ans;
}

/**
 * Function to compute sum of fibonacci sequence from start_index to end_index.
 * @param start_index start of sequence
 * @param end_index end of sequence
 * @returns uint64_t the sum of sequence
 * @complexity Time Complexity: $O(\log(\text{end\_index}))$. Space Complexity: $O(\log(\text{end\_index}))$.
 */
uint64_t fiboSum(uint64_t start_index, uint64_t end_index) {
    return (result(end_index + 2) - result(start_index + 1));
}
}  // namespace fibonacci_sum
}  // namespace math

/**
 * Function for testing fiboSum function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    uint64_t start_index = 0, end_index = 3;
    uint64_t test_1 = math::fibonacci_sum::fiboSum(start_index, end_index);
    assert(test_1 == 4);
    std::cout << "Passed Test 1!" << std::endl;

    start_index = 3;
    end_index = 5;
    uint64_t test_2 = math::fibonacci_sum::fiboSum(start_index, end_index);
    assert(test_2 == 10);
    std::cout << "Passed Test 2!" << std::endl;

    start_index = 5;
    end_index = 7;
    uint64_t test_3 = math::fibonacci_sum::fiboSum(start_index, end_index);
    assert(test_3 == 26);
    std::cout << "Passed Test 3!" << std::endl;

    start_index = 7;
    end_index = 10;
    uint64_t test_4 = math::fibonacci_sum::fiboSum(start_index, end_index);
    assert(test_4 == 123);
    std::cout << "Passed Test 4!" << std::endl;

    start_index = 9;
    end_index = 12;
    uint64_t test_5 = math::fibonacci_sum::fiboSum(start_index, end_index);
    assert(test_5 == 322);
    std::cout << "Passed Test 5!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the tests
    return 0;
}
