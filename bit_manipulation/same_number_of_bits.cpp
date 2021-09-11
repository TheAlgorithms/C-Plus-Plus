/**
 * @file
 *
 * @brief Implementation to [Next higher number with same number of set
 * bits](https://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/)
 * @details
 * we have given a number let's say n, find next number with same number of
 * 1 bits in it's binary representation.
 *
 * @author [Kunal Kumar](https://github.com/kunalkumar37)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace same_number_of_bits
 * @brief Functions for the [Next higher number with the same number of set
 * bits](https://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/)
 * implementation
 */
namespace same_number_of_bits {
/**
 * @brief The main function implements same number of bits
 * @returns this function returns next higher with same number of set bits as n
 */
std::uint64_t samenumberofbits(uint64_t n) {
    uint64_t right = 0;
    uint64_t nexthigher = 0;
    uint64_t rightone = 0;
    uint64_t next1 = 0;
    if (n) {
        right = n & -static_cast<signed>(n);  // right most set bit

        nexthigher = n + right;  // reset the pattern and set next higher bit

        rightone = n ^ nexthigher;
        rightone = (rightone) / right;  // right adjust pattern
        rightone = rightone >> 2;       // correction factor
        next1 = nexthigher | rightone;
    }
    return next1;
}
}  // namespace same_number_of_bits
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n=1 return 2
    assert(bit_manipulation::same_number_of_bits::samenumberofbits(1) == 2);

    // n=3 return 5
    assert(bit_manipulation::same_number_of_bits::samenumberofbits(3) == 5);
    // n=15 return 23
    assert(bit_manipulation::same_number_of_bits::samenumberofbits(15) == 23);
    std::cout << "all the test cases are successfully passed!!" << std::endl;
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();  // run self-test implementation
    return 0;
}
