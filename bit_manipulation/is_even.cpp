/**
 * @file
 * @brief [Find whether a given number is even or odd]
 * (https://www.geeksforgeeks.org/check-if-a-number-is-odd-or-even-using-bitwise-operators/)
 * implementation
 *
 * @details
 * We are given a positive integer number. We need to check whether the number
 * is even or odd.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms. test comment
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)
 * @author [Simona Isakova](https://github.com/Buringskul)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @brief The main function implements check if a number is even or odd
 * @param n is the number who will be checked
 * @returns either true or false
 */

bool is_even(std ::int64_t n) {  // int64_t is preferred over int so that
                                 // no Overflow can be there. x) {
    return n & 1 == 0; // If a number has a 0 at the end in binary it is even but if it's one then the number is odd.
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 4 return true
    assert(bit_manipulation::is_even(4) == true);
    // n = 6 return true
    assert(bit_manipulation::is_even(6) == true);
    // n = 13 return false
    assert(bit_manipulation::is_even(13) == false);
    // n = 68 return true
    assert(bit_manipulation::is_even(68) == true);
    // n = 15 return false
    assert(bit_manipulation::is_even(15) == false);
    // n = 34 return true
    assert(bit_manipulation::is_even(34) == true);
    // n = 99 return false
    assert(bit_manipulation::is_even(99) == false);
    // n = 1020 return true
    assert(bit_manipulation::is_even(1020) == true);
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
}  // namespace bit_manipulation
