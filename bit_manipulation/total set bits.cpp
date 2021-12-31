
// @file
// * @brief Implementation to [count total set bits]
// * (https://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/)
// *
// *
// * @details
// *  We are Given a positive integer n, we need to count the total number of set bits in binary representation of all numbers from 1 to n.
// *
// * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as set bit and 0 is non set bit
      // Input: n = 3
      // Output:  4
      //
      // Input: n = 6
      // Output: 9
      //
      // Input: n = 7
      // Output: 12
      //
      // Input: n = 8
      // Output: 13
// * Worst Case Time Complexity: O(log n)
// * Space complexity: O(1)
// * @author [Anish Kumar De](https://github.com/anishclw)
//
// */
#include <cassert>   /// for assert
#include <iostream>
#include <cmath>
 /// for IO operations
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace count_of_set_bits
 * @brief Functions for the [count sets
 * bits](https://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/)
 * implementation
 */
namespace count_of_set_bits {
/**
 * @brief The main function implements total set bit count
 * @param n is the range  whose set bit will be counted
 * @returns total number of set-bits in the range of  `n`
 */
std::uint64_t countSetBits(
    std ::int64_t n) {  // int64_t is preferred over int so that
                        // no Overflow can be there.

    if(n==0)
    {
      return 0;
    }

    int x = log2(n);
    int yo = x *(1<<(x-1));
    int yo2 = n - (1<<x)+1;
    int rest = n -(1<<x);
    int ans = yo + yo2 + countSetBits(rest);
    return ans;
    // Why this algorithm is better than the standard one?
    // Because this algorithm runs the same number of times as the number of
    // set-bits in it. Means if my number is having "3" set bits, then this
    // while loop will run only "3" times!!
}
}  // namespace count_of_set_bits
}  // namespace bit_manipulation

static void test() {
    // n = 3 return 4
    assert(bit_manipulation::count_of_set_bits::countSetBits(3) == 4);
    // n = 6 return 9
    assert(bit_manipulation::count_of_set_bits::countSetBits(6) == 9);
    // n = 7 return 12
    assert(bit_manipulation::count_of_set_bits::countSetBits(7) == 12);
    // n = 8 return 13
    assert(bit_manipulation::count_of_set_bits::countSetBits(8) == 13);
    // n = 4 return 5
    assert(bit_manipulation::count_of_set_bits::countSetBits(4) == 5);
    // n = 17 return 35
    assert(bit_manipulation::count_of_set_bits::countSetBits(17) == 35);
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
