/**
 * @file
 * @brief [Neon Number](https://en.wikipedia.org/wiki/Neon_number) implementation
 * @details
 * A neon number is a number where the sum of digits of its square is equal to the number itself.
 * Example: 9 is a neon number because 9^2 = 81 and 8 + 1 = 9.
 *
 * @author [Nithwin](https://github.com/Nithwin)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Checks if a number is a neon number
 * @param n the number to check
 * @return true if the number is a neon number
 * @return false if the number is not a neon number
 */
bool is_neon(int n) {
    if (n < 0) {
        return false; // Negative numbers cannot be neon numbers
    }
    
    int square = n * n;
    int sum_digits = 0;
    
    while (square > 0) {
        sum_digits += square % 10;
        square /= 10;
    }
    
    return sum_digits == n;
}

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test Case 1: 0 is a neon number (0^2 = 0, sum = 0)
    assert(math::is_neon(0) == true);

    // Test Case 2: 1 is a neon number (1^2 = 1, sum = 1)
    assert(math::is_neon(1) == true);

    // Test Case 3: 9 is a neon number (9^2 = 81, 8+1 = 9)
    assert(math::is_neon(9) == true);

    // Test Case 4: 12 is NOT a neon number (12^2 = 144, 1+4+4 = 9 != 12)
    assert(math::is_neon(12) == false);

    // Test Case 5: 45 is NOT a neon number (45^2 = 2025, 2+0+2+5 = 9 != 45)
    assert(math::is_neon(45) == false);

    std::cout << "All tests passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
