/**
 * @file
 * @brief Implementation of [Binary Exponentiation]
 * (https://cp-algorithms.com/algebra/binary-exp.html)
 * @details
 * Given a base and an exponent, we want to return the resulting value.
 * Normal exponentiation calculates a^n in O(n), but using binary
 * exponentiation we are able to calculate a^n in O(logn).
 * @author [Mason Green](https://github.com/masongreen30)
 */

#include <cassert>
#include <iostream>

/**
 * @namespace divide_and_conquer
 * @brief Divide and Conquer algorithms
 */
namespace divide_and_conquer {
/**
 * @namespace karatsuba_algorithm
 * @brief Function for the [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html) algorithm implementation
 */
namespace binary_exponentiation {
/**
 * @brief Converts the exponent of a base to binary to
 * determine if the calculated number will be multiplied
 * to the result or not. Note that some extra variables 
 * were included for understanding, but are not required 
 * for the function to perform correctly.
 * @param base number being repeatedly multiplied
 * @param exponent number of times base multiplies itself
 * @returns result of base^exponent
 */
int binary_exponentiation(int base, int exponent) {
    bool remainder = 0;
    int result = 1;
    int calculated = base;
    while (exponent != 0) {
        remainder = exponent % 2;
        exponent /= 2;
        if (remainder) {
            result *= calculated;
        } 
        calculated *= calculated;
    }
    return result;
}
}  // namespace binary_exponentiation
}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test 1
    int b1 = 4;
    int exp1 = 3;
    std::cout << "Test 1 ";
    assert(divide_and_conquer::binary_exponentiation::binary_exponentiation(
               b1, exp1) == 64);  // 4^3 = 64
    std::cout << "successful" << std::endl;

    // Test 2
    int b2 = 2;
    int exp2 = 18;
    std::cout << "Test 2 ";
    assert(divide_and_conquer::binary_exponentiation::binary_exponentiation(
               b2, exp2) == 262144);  // 2^18 = 262144
    std::cout << "successful" << std::endl;

    // Test 3
    int b3 = 3;
    int exp3 = 13;
    std::cout << "Test 3 ";
    assert(divide_and_conquer::binary_exponentiation::binary_exponentiation(
               b3, exp3) == 1594323);  // 3^13 = 1594323
    std::cout << "successful" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test();  // run self-test implementations
    return 0;
}