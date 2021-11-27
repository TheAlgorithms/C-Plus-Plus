/**
 * @file
 * @brief Binary exponentiation for calculating power
 * @details
 * reference link :https://cp-algorithms.com/algebra/binary-exp.html
 * Time complexity : O(log(n))
 * Space complexity : O(1)
 * @author [Jaladi Saai Sishir](https://github.com/sishir2001)
 **/

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace binary_exponentiation
 * @brief Functions for the [binary
 * exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)
 * implementation
 */
namespace binary_exponentiation {
/**
 * @brief The main function implements power through binary exponentiation
 * @param x is the base of the power
 * @param n is the exponent for the power
 * @returns power(x,n) i.e x^n of type long (64 bits)
 */
int64_t binaryExponentiation(int x, int n) {
    int64_t res = 1;  // variable for storing the final result
    while (n != 0) {
        if (n % 2 == 1) {
            // last bit is 1
            res *= x;
        }
        x *= x;  // exponentiation
        n /= 2;  // right shifting
    }
    return res;
}
}  // namespace binary_exponentiation
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(bit_manipulation::binary_exponentiation::binaryExponentiation(
               2, 2) == 4);  // x = 2 n = 2 return 4
    assert(bit_manipulation::binary_exponentiation::binaryExponentiation(
               3, 2) == 9);  // x = 3 n = 2 return 9
    assert(bit_manipulation::binary_exponentiation::binaryExponentiation(
               4, 2) == 16);  // x = 4 n = 2 return 16
    assert(bit_manipulation::binary_exponentiation::binaryExponentiation(
               5, 2) == 25);  // x = 5 n = 2 return 25
    assert(bit_manipulation::binary_exponentiation::binaryExponentiation(
               6, 2) == 36);  // x = 6 n = 2 return 36
    std::cout << "All tests passed"
              << "\n";
}
/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
