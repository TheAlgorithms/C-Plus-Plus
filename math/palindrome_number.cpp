#include <cassert>

/**
 * @brief Checks whether a given integer is a palindrome.
 *
 * A palindrome number reads the same backward as forward.
 * Examples: 121, 1331
 *
 * @param n Integer to check
 * @return true if palindrome, false otherwise
 */
bool is_palindrome(int n) {
    if (n < 0) {
        return false;
    }

    int original = n;
    int reversed = 0;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }

    return original == reversed;
}

int main() {
    assert(is_palindrome(121));
    assert(is_palindrome(1331));
    assert(!is_palindrome(123));
    assert(!is_palindrome(-121));

    return 0;
}
