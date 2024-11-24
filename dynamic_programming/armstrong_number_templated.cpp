/**
 * @file
 * @brief Checks whether a number is an [Armstrong
 * Number](https://en.wikipedia.org/wiki/Narcissistic_number) or not.
 *
 * @details
 * An Armstrong number is a number that is the sum of its own digits each raised
 * to the power of the number of digits. For example: 153 is an Armstrong number
 * since 153 = 1^3 + 5^3 + 3^3.
 *
 * A few examples of valid armstrong numbers:
 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634, 8208, 9474, 54748,
 * 92727, 93084.
 *
 * Armstrong numbers are also known as Narcissistic Numbers, as stated in
 * Wikipedia.
 *
 * @author [Shivam Singhal](https://github.com/shivhek25)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for std::pow
#include <iostream>  /// for IO operations

/**
 * @namespace
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @brief Checks if the given number is armstrong or not.
 * @param number the number to check
 * @returns false if the given number is NOT armstrong
 * @returns true if the given number IS armstrong
 */
template <typename T>
bool is_armstrong(const T &number) {
    int count = 0, temp = number, result = 0, rem = 0;

    // Count the number of digits of the given number.
    // For example: 153 would be 3 digits.
    while (temp != 0) {
        temp /= 10;
        count++;
    }

    // Calculation for checking of armstrongs number i.e.
    // in an n-digit number sum of the digits is raised to a power of `n` is
    // equal to the original number.
    temp = number;
    while (temp != 0) {
        rem = temp % 10;
        result += static_cast<T>(std::pow(rem, count));
        temp /= 10;
    }

    if (result == number) {
        return true;
    } else {
        return false;
    }
}
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(dynamic_programming::is_armstrong(153) == true);
    assert(dynamic_programming::is_armstrong(1) == true);
    assert(dynamic_programming::is_armstrong(0) == true);
    assert(dynamic_programming::is_armstrong(370) == true);
    assert(dynamic_programming::is_armstrong(1634) == true);
    assert(dynamic_programming::is_armstrong(580) == false);
    assert(dynamic_programming::is_armstrong(15) == false);
    assert(dynamic_programming::is_armstrong(1024) == false);
    assert(dynamic_programming::is_armstrong(989) == false);
    assert(dynamic_programming::is_armstrong(103) == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
