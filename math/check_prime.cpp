/**
 * @file
 * @brief A simple program to check if a given number is [Prime](https://en.wikipedia.org/wiki/Primality_test) or not.
 * @details
 * A prime number is any natural number greater than 1 that has no positive divisors
 * other than 1 and itself. The only even prime number is 2; all other prime numbers
 * are odd numbers. This algorithm utilizes trial division optimized by skipping
 * multiples of 2 and 3.
 *
 * Additional resources for primality tests:
 * https://cp-algorithms.com/algebra/primality_tests.html
 *
 * @author [Omkar Langhe](https://github.com/omkarlanghe)
 * @author [ewd00010](https://github.com/ewd00010)
 * @author [Yasmeen](https://github.com/yasmeenMohammed)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace math
 */
namespace math {
/**
 * @brief Function to check if the given number is prime or not.
 * @param number The 64-bit integer to be checked for primality.
 * @return true if the number is a prime number.
 * @return false if the number is not a prime number.
 * @note Time Complexity: O(sqrt(number)) due to trial division optimization up to the square root.
 * @note Space Complexity: O(1) as it uses a constant amount of extra memory space.
 */
bool is_prime(int64_t number) {
    // Numbers less than or equal to 1 are not prime
    if (number <= 1) {
        return false;
    } 
    // 2 and 3 are prime numbers
    if (number == 2 || number == 3) {
        return true;
    } 
    // Exclude all even numbers and multiples of 3
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    } 
    
    // Check potential factors starting from 5, skipping multiples of 2 and 3 (i.e., step of 6)
    for (int64_t factor = 5; factor * factor <= number; factor += 6) {
        if (number % factor == 0 || number % (factor + 2) == 0) {
            return false;
        }
    }
    
    return true;
}
}  // namespace math

/**
 * @brief Self-test implementations to validate the correctness of the primality check.
 * @returns void
 */
static void tests() {
    assert(math::is_prime(0) == false);     /// Test boundary edge case 0
    assert(math::is_prime(1) == false);     /// Test boundary edge case 1
    assert(math::is_prime(2) == true);      /// Test smallest even prime
    assert(math::is_prime(3) == true);      /// Test smallest odd prime
    assert(math::is_prime(4) == false);     /// Test composite even number
    assert(math::is_prime(-4) == false);    /// Test negative composite number
    assert(math::is_prime(7) == true);      /// Test standard odd prime
    assert(math::is_prime(-7) == false);    /// Test negative odd number
    assert(math::is_prime(19) == true);     /// Test medium prime number
    assert(math::is_prime(50) == false);    /// Test large composite number
    assert(math::is_prime(115249) == true); /// Test a large prime number

    std::cout << "All primality checks have successfully passed!" << std::endl;
}

/**
 * @brief Main function to execute the self-test suite.
 * @returns 0 on clean exit
 */
int main() {
    tests();  // perform self-tests implementations
    return 0;
}