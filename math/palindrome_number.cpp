/**
 * @file
 * @brief Check whether a number is a palindrome.
 */

#include <iostream>
#include <cassert>

/**
 * @brief Checks if a number is a palindrome.
 * @param n Number to check
 * @return true if palindrome, false otherwise
 */
bool is_palindrome(int n) {
    if (n < 0) {
        return false;  // negative numbers are not palindromes
    }
    int original = n;
    int reversed = 0;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }

    return original == reversed;
}

/**
 * @brief Self-test implementations
 */
static void tests() {
    assert(is_palindrome(121) == true);
    assert(is_palindrome(123) == false);
    assert(is_palindrome(0) == true);
    assert(is_palindrome(7) == true);
    assert(is_palindrome(-121) == false);

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    tests();
    return 0;
}
