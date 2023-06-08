/**
 * @file
 * @brief C++ Program to find Binary Exponent Iteratively and Recursively.
 *
 * @details
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
 *
 * @author [Mann Mehta](https://github.com/mann2108)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Recursive function to calculate exponent in \f$O(\log(n))\f$ using
 * binary exponent.
 * @param a base number
 * @param b exponent number
 * @return 1 if the exponent number is 0 the return value will always be 1
 * @return (res * res * a) if modulo 2 of exponential is 0
 * @return (res * res) if modulo 2 of exponential is 1
 */
int64_t binExpo_recursive(int64_t a, uint64_t b) {
    /*!
     * Provided that b != 0, this function recursively calls itself, until an
     * instance of it returns 1 (which eventually occurs due to b/2 for each
     * call to binExpo). This triggers a chain reaction eventually leading
     * back to the original call to binExpo returning. This works like a
     * building a russian doll, first figure out however dolls you want to use (
     * say, until a call to binExpo returns 1 ) and then assemble the dolls (
     * with each return, res gets exponentially bigger )
     */
    if (b == 0 || a == 1) {
        return 1;
    } else if(b == 1 || a == 0){
        return a;
    }

    int64_t res = binExpo_recursive(a, b / 2);
    if (b % 2) {
        return res * res * a;
    } else {
        return res * res;
    }
}

/**
 * @brief Iterative function to calculate exponent in \f$O(\log(n))\f$ using
 * binary
 + exponent.
 * @param a base number
 * @param b exponential number
 * @return res if the exponential number is >= 0
 */
int64_t binExpo_iterative(int64_t a, uint64_t b) {
    /*!
     * Provided b > 0, this function iteratively multiples the value res. Each
     * iteration of the while loop, checks if the exponential number is binary,
     * if so res is multiplied by the current value of a, for that iteration.
     * Additionally, a is multiplied by itself and b is halved by itself.
     */
    if (b == 0 || a == 1) {
        return 1;
    } else if(b == 1 || a == 0){
        return a;
    }
    
    int64_t res = 1;
    while (b > 0) {  // if b is not a valid exponent
        if (b % 2) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
}  // namespace math

/**
 * @brief Self-test implementation
 * @returns void
 */
static void tests() {
    assert(math::binExpo_recursive(0, 1) == 0);
    assert(math::binExpo_recursive(1, 0) == 1);
    assert(math::binExpo_recursive(746584, 0) == 1);
    assert(math::binExpo_recursive(1, 1) == 1);
    assert(math::binExpo_recursive(2938374, 1) == 2938374);
    assert(math::binExpo_recursive(3, 7) == 2187);
    assert(math::binExpo_recursive(-31, 5) == -28629151);
    assert(math::binExpo_recursive(0, 0) == 1);
    assert(math::binExpo_recursive(1, 20) == 0);

    assert(math::binExpo_iterative(0, 1) == 0);
    assert(math::binExpo_iterative(1, 0) == 1);
    assert(math::binExpo_iterative(746584, 0) == 1);
    assert(math::binExpo_iterative(1, 1) == 1);
    assert(math::binExpo_iterative(2938374, 1) == 2938374);
    assert(math::binExpo_iterative(3, 7) == 2187);
    assert(math::binExpo_iterative(-31, 5) == -28629151);
    assert(math::binExpo_iterative(0, 0) == 1);
    assert(math::binExpo_iterative(1, 20) == 0);
    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
