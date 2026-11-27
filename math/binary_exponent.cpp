/**
 * @file
 * @brief C++ Program to find Binary Exponent Iteratively and Recursively.
 *
 * Calculate \f$a^b\f$ in \f$O(\log(b))\f$ by converting \f$b\f$ to a
 * binary number. Binary exponentiation is also known as exponentiation by
 * squaring.
 * @note This is a far better approach compared to naive method which
 * provide \f$O(b)\f$ operations.
 *
 * Example:
 * </br>10 in base 2 is 1010.
 * \f{eqnarray*}{
 * 2^{10_d} &=& 2^{1010_b} = 2^8 * 2^2\\
 * 2^1 &=& 2\\
 * 2^2 &=& (2^1)^2 = 2^2 = 4\\
 * 2^4 &=& (2^2)^2 = 4^2 = 16\\
 * 2^8 &=& (2^4)^2 = 16^2 = 256\\
 * \f}
 * Hence to calculate 2^10 we only need to multiply \f$2^8\f$ and \f$2^2\f$
 * skipping \f$2^1\f$ and \f$2^4\f$.
 */

#include <cassert>   /// For assert
#include <iostream>  /// For IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Recursive function to calculate exponent in \f$O(\log(n))\f$ using
 * binary exponent.
 * @param a base
 * @param b exponent
 * @returns \f$a^b\f$
 */
int binExpo(int a, int b) {
    if (b == 0) {
        return 1;
    }
    int res = binExpo(a, b / 2);
    if (b % 2) {
        return res * res * a;
    } else {
        return res * res;
    }
}

/**
 * @brief Iterative function to calculate exponent in \f$O(\log(n))\f$ using
 * binary exponent.
 * @param a base
 * @param b exponent
 * @returns \f$a^b\f$
 */
int binExpo_alt(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b % 2) {
            res = res * a;
        }
        a = a * a;
        b /= 2;
    }
    return res;
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(math::binExpo(2, 3) == 8);
    assert(math::binExpo_alt(2, 3) == 8);
    assert(math::binExpo(2, 0) == 1);
    assert(math::binExpo_alt(2, 0) == 1);
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // run self test implementation.
    return 0;
}
