/**
 * @file
 * @brief Program to return the [Aliquot
 * Sum](https://en.wikipedia.org/wiki/Aliquot_sum) of a number
 *
 * \details
 * The Aliquot sum s(n) of a non-negative integer n is the sum of all
 * proper divisors of n, that is, all the divisors of n, other than itself.
 * For example, the Aliquot sum of 18 = 1 + 2 + 3 + 6 + 9 = 21
 *
 * @author [SpiderMath](https://github.com/SpiderMath)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace math
 */
namespace math {
/**
 * Function to return the aliquot sum of a number
 * @param num The input number
 */
uint64_t aliquot_sum(const uint64_t num) {
    if (num == 0 || num == 1) {
        return 0;  // The aliquot sum for 0 and 1 is 0
    }

    uint64_t sum = 0;

    for (uint64_t i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    return sum;
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Aliquot sum of 10 is 1 + 2 + 5 = 8
    assert(math::aliquot_sum(10) == 8);
    // Aliquot sum of 15 is 1 + 3 + 5 = 9
    assert(math::aliquot_sum(15) == 9);
    // Aliquot sum of 1 is 0
    assert(math::aliquot_sum(1) == 0);
    // Aliquot sum of 97 is 1 (the aliquot sum of a prime number is 1)
    assert(math::aliquot_sum(97) == 1);

    std::cout << "All the tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run the self-test implementations

    return 0;
}
