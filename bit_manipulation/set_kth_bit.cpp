/**
 * @file
 * @brief Implementation to [From the right, set the Kth bit in the binary
 * representation of N]
 * (https://practice.geeksforgeeks.org/problems/set-kth-bit3724/1/) in an
 * integer.
 *
 * @details
 * Given a number N and a value K. From the right, set the Kth bit in the binary
 * representation of N. The position of Least Significant Bit(or last bit) is 0,
 * the second last bit is 1 and so on. in it.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)

 * @author [Aman Raj](https://github.com/aman2000raj)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace setKthBit
 * @brief Functions for the [From the right, set the Kth bit in the binary
 * representation of N]
 * (https://practice.geeksforgeeks.org/problems/set-kth-bit3724/1/)
 * implementation
 */
namespace set_kth_bit {
/**
 * @brief The main function implements set kth bit
 * @param N is the number whose kth bit will be set
 * @returns returns an integer after setting the K'th bit in N
 */
std::uint64_t setKthBit(std ::int64_t N,
                        std ::int64_t k) {  // int64_t is preferred over int so
                                            // that no Overflow can be there.

    int pos =
        1 << k;  // "pos" variable is used to store 1 at kth postion and
                 // rest bits are 0. in binary representation of number 'n'

    return N | pos;  // by taking or with the pos and the N we set the bit of N
                     // at kth position.
}
}  // namespace set_kth_bit
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 10,2 return 14
    assert(bit_manipulation::set_kth_bit::setKthBit(10, 2) == 14);
    // n = 25,1 return 27
    assert(bit_manipulation::set_kth_bit::setKthBit(25, 1) == 27);
    // n = 400001,5 return 400033
    assert(bit_manipulation::set_kth_bit::setKthBit(400001, 5) == 400033);
    // n = 123 return 123
    assert(bit_manipulation::set_kth_bit::setKthBit(123, 3) == 123);

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
