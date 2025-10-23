/**
 * @file
 * @brief Check if a given number is a palindrome
 * @details
 * This program defines a function `is_palindrome_number()` which checks whether
 * a number reads the same backward as forward.
 * Negative numbers are treated as non-palindromic.
 *
 * @see https://en.wikipedia.org/wiki/Palindrome
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Checks if an integer is a palindrome number.
 * @param n The number to check.
 * @return `true` if `n` is a palindrome, otherwise `false`.
 */
bool is_palindrome_number(long long n) {
    if (n < 0)
        return false;
    std::string s = std::to_string(n);
    int i = 0, j = static_cast<int>(s.size()) - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        ++i;
        --j;
    }
    return true;
}

#ifdef RUN_LOCAL
/**
 * @brief Example test cases for the palindrome number checker.
 */
int main() {
    std::vector<long long> tests = {121, -121, 10, 12321, 0};
    for (auto t : tests) {
        std::cout << t << " -> " << (is_palindrome_number(t) ? "True" : "False")
                  << "\n";
    }
    return 0;
}
#endif