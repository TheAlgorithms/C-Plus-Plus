/**
 * Check whether a number is divisible by 2^k or not
 *
 *
 * We are given a positive integer `n` and an integer `k`.
 * We need to check whether `n` is divisible by `2^k`.
 *
 * - Bitwise AND operation is used to efficiently check
 *   if the last k bits of n are zero.
 * - If (n & (2^k - 1)) equals 0, then the number is divisible by 2^k.
 *
 * 
 * 
 * Worst Case Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @author [Tirth Patel](https://github.com/Tirth9978)
 */


/*

Explanation  : 
--> LL << k shifts 1 left by k positions, giving us 2 ^ k
--> Subtracting 1 from it gives a binary number with the last k bits set.
--> Bitwise AND with n checks if the last k bits of n are zero.

*/



#include <cassert>  /// for assert
#include <cstdint>  /// for int64_t
#include <iostream> /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation
{

    /**
     * @brief Check if a number `n` is divisible by 2^k
     * @param n The input number
     * @param k The power of 2
     * @returns `true` if divisible, otherwise `false`
     */
    bool isDivisibleBy2PowerK(std::int64_t n, int k)
    {
        // Check if the last k bits of n are zero
        return (n & ((1LL << k) - 1)) == 0;
    }
}

static void test()
{
    // Test cases to check divisibility by 2^k

    // 8 is divisible by 2^3
    assert(bit_manipulation::isDivisibleBy2PowerK(8, 3) == true);
    // 10 is not divisible by 2^2
    assert(bit_manipulation::isDivisibleBy2PowerK(10, 2) == false);
    // 64 is divisible by 2^6
    assert(bit_manipulation::isDivisibleBy2PowerK(64, 6) == true);
    // 15 is not divisible by 2^3
    assert(bit_manipulation::isDivisibleBy2PowerK(15, 3) == false);
    // 32 is divisible by 2^5
    assert(bit_manipulation::isDivisibleBy2PowerK(32, 5) == true);
    // 100 is not divisible by 2^5
    assert(bit_manipulation::isDivisibleBy2PowerK(100, 5) == false);
    // 128 is divisible by 2^7
    assert(bit_manipulation::isDivisibleBy2PowerK(128, 7) == true);
    // 1024 is divisible by 2^10
    assert(bit_manipulation::isDivisibleBy2PowerK(1024, 10) == true);

    // Edge Cases for Large Numbers
    assert(bit_manipulation::isDivisibleBy2PowerK(1LL << 20, 20) == true);        // 2^20 % 2^20 = 0
    assert(bit_manipulation::isDivisibleBy2PowerK((1LL << 50), 50) == true);      // 2^50 % 2^50 = 0
    assert(bit_manipulation::isDivisibleBy2PowerK((1LL << 60) - 1, 59) == false); // Not divisible by 2^59
    assert(bit_manipulation::isDivisibleBy2PowerK(1LL << 40, 35) == true);        // 2^40 % 2^35 = 0
    assert(bit_manipulation::isDivisibleBy2PowerK(1LL << 62, 62) == true);        // 2^62 % 2^62 = 0
   

    // Edge Cases for Small Numbers
    assert(bit_manipulation::isDivisibleBy2PowerK(0, 5) == true);  // 0 is divisible by any power of 2
    assert(bit_manipulation::isDivisibleBy2PowerK(1, 0) == true);  // Any number is divisible by 2^0
    assert(bit_manipulation::isDivisibleBy2PowerK(2, 1) == true);  // 2 % 2^1 = 0
    assert(bit_manipulation::isDivisibleBy2PowerK(3, 1) == false); // 3 % 2 != 0
    assert(bit_manipulation::isDivisibleBy2PowerK(4, 2) == true);  // 4 % 4 = 0

    std::cout << "All test cases successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test(); // Run self-test implementations
    return 0;
}
