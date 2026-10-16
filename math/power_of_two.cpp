/**
 * @file
 * @brief Implementation to check whether a number is a power of 2 or not.
 *
 * @details
 * This algorithm uses bit manipulation to check if a number is a power of 2 or
 * not.
 *
 * ### Algorithm
 * Let the input number be n, then the bitwise and between n and n-1 will let us
 * know whether the number is power of 2 or not
 *
 * For Example,
 * If N= 32 then N-1 is 31, if we perform bitwise and of these two numbers then
 * the result will be zero, which indicates that it is the power of 2
 * If N=23 then N-1 is 22, if we perform bitwise and of these two numbers then
 * the result will not be zero , which indicates that it is not the power of 2
 * \note This implementation is better than naive recursive or iterative
 * approach.
 *
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 * @author [Rijul.S](https://github.com/Rijul24)
 * @author [Akhila Pynam](https://github.com/akhila-pynam)
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for std::uint64_t
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief This function finds whether a number is a power of 2 or not.
 * @param n Value for which we want to check.
 * @return `true` if `n` is a power of 2.
 * @return `false` if `n` is not a power of 2.
 */
bool is_power_of_two(uint64_t n) {
    /// result stores the
    /// bitwise and of n and n-1
    if (n == 0) {
        return false;
    }
    return (n & (n - 1)) == 0;
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 0 is not a power of 2
    assert(math::is_power_of_two(0) == false);

    // 1 is 2^0 (true)
    assert(math::is_power_of_two(1) == true);

    // Powers of 2
    assert(math::is_power_of_two(2) == true);
    assert(math::is_power_of_two(4) == true);
    assert(math::is_power_of_two(8) == true);
    assert(math::is_power_of_two(16) == true);
    assert(math::is_power_of_two(32) == true);
    assert(math::is_power_of_two(64) == true);
    assert(math::is_power_of_two(1024) == true);
    assert(math::is_power_of_two(1ULL << 30) == true);
    assert(math::is_power_of_two(1ULL << 62) == true);

    // Non-powers of 2
    assert(math::is_power_of_two(3) == false);
    assert(math::is_power_of_two(5) == false);
    assert(math::is_power_of_two(6) == false);
    assert(math::is_power_of_two(7) == false);
    assert(math::is_power_of_two(9) == false);
    assert(math::is_power_of_two(232) == false);
    assert(math::is_power_of_two(1000) == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    test();  // run self-test implementations
    return 0;
}
