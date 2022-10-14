/**
 * @file
 * @brief Implementation to [Find whether a given number is power of 2]
 * (https://www.geeksforgeeks.org/program-to-find-whether-a-given-number-is-power-of-2/).
 *
 * @details
 * We are given a positive integer number. We need to check whether the number is power of
 * 2 or not.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)
 * @author [Prafful Gupta](https://github.com/EcstaticPG-25811)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace count_of_set_bits
 * @brief Functions for the [check power of
 * 2](https://www.geeksforgeeks.org/program-to-find-whether-a-given-number-is-power-of-2/)
 * implementation
 */
namespace count_of_set_bits {
/**
 * @brief The main function implements check for power of 2
 * @param n is the number who will be checked
 * @returns either true or false
 */
bool isPowerOfTwo(
    std ::int64_t n) {  // int64_t is preferred over int so that
                        // no Overflow can be there.

    return n > 0 && not (n & n - 1); // If we subtract a power of 2 numbers by 1 
    // then all unset bits after the only set bit become set; and the set bit becomes unset.

    // If a number n is a power of 2 then bitwise and of n-1 and n will be zero.
    // The expression n&(n-1) will not work when n is 0. 
    // To handle this case also, our expression will become n& (!n&(n-1)) 
}
}  // namespace count_of_set_bits
}  // namespace bit_manipulation

static void test() {
    // n = 4 return true
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(4) == true);
    // n = 6 return false
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(6) == false);
    // n = 13 return false
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(13) == false);
    // n = 64 return true
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(64) == true);
    // n = 15 return false
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(15) == false);
    // n = 32 return true
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(32) == true);
    // n = 97 return false
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(97) == false);
    // n = 1024 return true
    assert(bit_manipulation::count_of_set_bits::isPowerOfTwo(1024) == true);
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