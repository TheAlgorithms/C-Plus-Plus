/**
 * @file
 * @brief Implementation to [Toggle Bits in a given Range]
 * (https://www.geeksforgeeks.org/toggle-bits-given-range/).
 *
 * @details
 * We are given a non-negative number n and two values l and r. The problem is
 * to toggle the bits in the range l to r in the binary representation of n,
i.e,
 * to toggle bits from the rightmost lth bit to the rightmost rth bit. A toggle
 * operation flips a bit 0 to 1 and a bit 1 to 0.
 * Example:- Input : n = 17, l = 2, r = 3
 *            Output : 23
 *            (17)10 = (10001)2
 *            (23)10 = (10111)2
 *           The bits in the range 2 to 3 in the binary
representation of 17 are toggled.
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)
 * @author [Anish Kumar De](https://github.com/anishclw)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace toggle_bits
 * @brief Functions for the [Toggle
 * Bits](https://www.geeksforgeeks.org/toggle-bits-given-range/) implementation
 */
namespace toggle_bits {
/**
 * @brief The main function implements set bit count
 * @param n is the number whose  bits will be toggled in a given range l to r
 * inclusive.
 * @param l is the left range
 * @param r is the right range
 * @returns the new number 'n' after toggling the bits in the range.
 */
std::uint64_t toggleBits(std::int64_t n, std::int64_t l,
                         std::int64_t r) {  // int64_t is preferred over int so
                                            // that no Overflow can be there.

    int i = 1;
    i = i << l - 1;
    while (l <= r) {
        n = n ^ i;
        i = i << 1;
        l++;
    }
    return n;
    // Why this algorithm is better than the standard one?
    // Because this algorithm runs with O(1) time complexity and with no space
    // complexity. From l-1 to r the the bits of number N is traversed and then
    // the bits are toggled.
}
}  // namespace toggle_bits
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 17, l=2,r=3 return 23
    assert(bit_manipulation::toggle_bits::toggleBits(17, 2, 3) == 23);
    // n = 50, l=2,r=5 return 44
    assert(bit_manipulation::toggle_bits::toggleBits(50, 2, 5) == 44);
    // n = 10, l=3,r=4 return 6
    assert(bit_manipulation::toggle_bits::toggleBits(10, 3, 4) == 6);
    //  n = 12, l=4,r=6 return 52
    assert(bit_manipulation::toggle_bits::toggleBits(12, 4, 6) == 52);
    // n = 19, l=2,r=6 return 45
    assert(bit_manipulation::toggle_bits::toggleBits(19, 2, 6) == 45);
    // n = 5, l=1,r=3 return 2
    assert(bit_manipulation::toggle_bits::toggleBits(5, 1, 3) == 2);
    std::cout << "All test cases successfully passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
