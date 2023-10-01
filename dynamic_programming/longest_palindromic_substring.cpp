/*
The Longest Palindromic Substring (LPS) problem is a fundamental problem in
computer science and string processing. The goal of this problem is to find the
longest substring of a given string that is a palindrome.

Approach : Dynamic programming is one approach to efficiently solve this
problem. By creating a 2D array (matrix) and tracking whether substrings are
palindromes or not.
*/

// CODE STARTS

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @brief Calculate the length of the longest palindromic substring
 * for the specified string.
 * @param s the string used to calculate the longest palindromic substring
 * @returns the length of the longest palindromic substring in the `s` string
 */
uint64_t LPS(const std::string &s) {
    int n = s.size();
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    int maxLength = 1;
    int startIdx = 0;  // To keep track of the starting index of the longest
                       // palindromic substring.

    for (int start = n - 1; start >= 0; --start) {
        for (int end = start + 1; end < n; ++end) {
            if (s[start] == s[end]) {
                if (end - start == 1) {
                    dp[start][end] = true;
                } else {
                    dp[start][end] = dp[start + 1][end - 1];
                }
                if (dp[start][end] && end - start + 1 > maxLength) {
                    maxLength = end - start + 1;
                    startIdx = start;
                }
            }
        }
    }

    std::string longestPalindromicSubstring = s.substr(startIdx, maxLength);
    std::cout << "The longest palindromic substring is: "
              << longestPalindromicSubstring << std::endl;

    return maxLength;
}
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::string str = "babad";
    uint32_t lpsResult = dynamic_programming::LPS(str);
    assert(lpsResult ==
           3);  ///< The longest palindromic substring is "bab" or "aba"

    std::cout << "Self-test implementations passed!" << std::endl;
}

/**
 * @brief Main function
 * @param argc command-line argument count (ignored)
 * @param argv command-line array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const *argv[]) {
    std::string str;
    std::cout << "Enter a string: ";
    std::cin >> str;

    uint32_t lpsResult = dynamic_programming::LPS(str);
    std::cout << "The result for LPS is: " << lpsResult << std::endl;

    test();  // run self-test implementations

    return 0;
}
