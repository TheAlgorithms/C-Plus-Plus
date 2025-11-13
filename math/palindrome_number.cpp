/**
* @file
 * @brief Check if a number is a [palindrome number](https://en.wikipedia.org/wiki/Palindrome)
 *
 * @details
 * A palindrome number is a number that reads the same forward and backward.
 * Examples: 121, 1331, 5445.
 *
 * This implementation reverses the digits of the number and compares it
 * with the original value.
 *
 * @author [Aman Keshav Prasad](https://github.com/amank-23)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Function to check if a given number is a palindrome.
 * @param num number to check
 * @return true if num is pallindrome, false otherwise
 */
bool is_palindrome(int num) {
    if (num < 0) {
        return false;  // negative numbers are not palindrome
    }

    int original = num;
    int reversed = 0;

    while (num > 0) {
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }

    return original == reversed;
}

}  // namespace math

/**
 * @brief Self-test implementations
 */
static void tests() {
    assert(math::is_palindrome(121) == true);
    assert(math::is_palindrome(5445) == true);
    assert(math::is_palindrome(10) == false);
    assert(math::is_palindrome(123) == false);
    assert(math::is_palindrome(-121) == false);
    assert(math::is_palindrome(0) == true);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    tests();
    return 0;
}
