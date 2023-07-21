/**
 * @file
 * @brief Iterative implementation of
 * [Factorial](https://en.wikipedia.org/wiki/Factorial)
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 *
 * @details Calculates factorial iteratively.
 * \f[n! = n\times(n-1)\times(n-2)\times(n-3)\times\ldots\times3\times2\times1
 *       = n\times(n-1)!\f]
 * for example:
 * \f$4! = 4\times3! = 4\times3\times2\times1 = 24\f$
 *
 * @example
 *
 * 5! = 5 * 4 * 3 * 2 * 1
 *
 * Recursive implementation of factorial pseudocode:
 *
 * function factorial(n):
 *     if n == 1:
 *         return 1
 *     else:
 *         return factorial(n-1)
 *
 */

#include <cassert>    /// for assert
#include <cstdint>    /// for integral types
#include <exception>  /// for std::invalid_argument
#include <iostream>   /// for std::cout

/**
 * @namespace
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Calculates the factorial iteratively.
 * @param n Nth factorial.
 * @return Factorial.
 * @note 0! = 1.
 * @warning Maximum=20 because there are no 128-bit integers in C++. 21!
 * returns 1.419e+19, which is not 21! but (21! % UINT64_MAX).
 */
uint64_t iterativeFactorial(uint8_t n) {
    if (n > 20) {
        throw new std::invalid_argument("Maximum n value is 20");
    }

    // 1 because it is the identity number of multiplication.
    uint64_t accumulator = 1;

    while (n > 1) {
        accumulator *= n;
        --n;
    }

    return accumulator;
}

}  // namespace math

/**
 * @brief Self-test implementations to test iterativeFactorial function.
 * @note There is 1 special case: 0! = 1.
 */
static void test() {
    // Special case test
    std::cout << "Exception case test \n"
                 "Input: 0 \n"
                 "Expected output: 1 \n\n";
    assert(math::iterativeFactorial(0) == 1);

    // Base case
    std::cout << "Base case test \n"
                 "Input: 1 \n"
                 "Expected output: 1 \n\n";
    assert(math::iterativeFactorial(1) == 1);

    // Small case
    std::cout << "Small number case test \n"
                 "Input: 5 \n"
                 "Expected output: 120 \n\n";
    assert(math::iterativeFactorial(5) == 120);

    // Medium case
    std::cout << "Medium number case test \n"
                 "Input: 10 \n"
                 "Expected output: 3628800 \n\n";
    assert(math::iterativeFactorial(10) == 3628800);

    // Maximum case
    std::cout << "Maximum case test \n"
                 "Input: 20 \n"
                 "Expected output: 2432902008176640000\n\n";
    assert(math::iterativeFactorial(20) == 2432902008176640000);

    // Exception test
    std::cout << "Exception test \n"
                 "Input: 21 \n"
                 "Expected output: Exception thrown \n";
    try {
        math::iterativeFactorial(21);
    } catch (std::invalid_argument* e) {
        std::cout << "Exception thrown successfully \nContent: " << e->what()
                  << "\n";
    }

    std::cout << "All tests have passed successfully.\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-test implementation
    return 0;
}
