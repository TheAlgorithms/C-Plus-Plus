/**
 * @file
 * @brief Program to check if a number is an [Armstrong/Narcissistic
 * number](https://en.wikipedia.org/wiki/Narcissistic_number) in decimal system.
 *
 * @details
 * An Armstrong number (also known as a pluperfect digital invariant (PPDI) or
 * narcissistic number) is a number that is the sum of its own digits each
 * raised to the power of the number of digits.
 *
 * For example:
 * - \f$153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153\f$
 * - \f$1634 = 1^4 + 6^4 + 3^4 + 4^4 = 1 + 1296 + 81 + 256 = 1634\f$
 *
 * @author [Neeraj Cherkara](https://github.com/iamnambiar)
 * @author [Akhila Pynam](https://github.com/akhila-pynam)
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for std::uint64_t
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Computes base raised to the power of exponent using integer
 * arithmetic.
 * @param base The base number.
 * @param exp The exponent.
 * @return base raised to the power of exp.
 */
uint64_t power(uint64_t base, uint64_t exp) {
    uint64_t res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return res;
}

/**
 * @brief Function to calculate the total number of digits in a number.
 * @param num The number to count digits for.
 * @return Total number of digits in the given number.
 */
uint64_t number_of_digits(uint64_t num) {
    if (num == 0) {
        return 1;
    }
    uint64_t total_digits = 0;
    while (num > 0) {
        num /= 10;
        ++total_digits;
    }
    return total_digits;
}

/**
 * @brief Function to check whether a number is an Armstrong number or not.
 * @param number The number to be checked.
 * @return `true` if the number is an Armstrong number.
 * @return `false` if the number is not an Armstrong number.
 */
bool is_armstrong(uint64_t number) {
    uint64_t total_digits = number_of_digits(number);
    uint64_t sum = 0;
    uint64_t temp = number;

    while (temp > 0) {
        uint64_t rem = temp % 10;
        sum += power(rem, total_digits);
        temp /= 10;
    }

    return number == sum;
}

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 0 is an Armstrong number: 0^1 = 0
    assert(math::is_armstrong(0) == true);

    // Single-digit numbers are all Armstrong numbers: d^1 = d
    assert(math::is_armstrong(1) == true);
    assert(math::is_armstrong(5) == true);
    assert(math::is_armstrong(9) == true);

    // 2-digit numbers are never Armstrong numbers in base 10
    assert(math::is_armstrong(10) == false);
    assert(math::is_armstrong(12) == false);

    // 3-digit Armstrong numbers: 153, 370, 371, 407
    assert(math::is_armstrong(153) == true);
    assert(math::is_armstrong(370) == true);
    assert(math::is_armstrong(371) == true);
    assert(math::is_armstrong(407) == true);
    assert(math::is_armstrong(225) == false);
    assert(math::is_armstrong(500) == false);

    // 4-digit Armstrong numbers: 1634, 8208, 9474
    assert(math::is_armstrong(1634) == true);
    assert(math::is_armstrong(8208) == true);
    assert(math::is_armstrong(9474) == true);
    assert(math::is_armstrong(9475) == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
