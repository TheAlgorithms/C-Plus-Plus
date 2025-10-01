/**
 * @file
 * @brief Implementation of [Longest Palindromic
 * Substring](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
 * using dynamic programming
 *
 * @details
 * The longest palindromic substring problem is to find the contiguous substring
 * of maximum length in a given string that is also a palindrome. A
 * [palindrome](https://en.wikipedia.org/wiki/Palindrome) is a string that
 * reads the same forwards and backwards, such as "racecar" or "noon".
 *
 * This is different from the longest palindromic subsequence, where characters
 * don't need to be contiguous. For example, for the string "banana":
 * - Longest palindromic substring: "anana" (length 5)
 * - Longest palindromic subsequence: "aanaa" (length 5, but not contiguous)
 *
 * ### Algorithm
 * The algorithm uses dynamic programming with a 2D table where dp[i][j]
 * represents whether the substring from index i to j is a palindrome.
 *
 * - All single characters are palindromes: dp[i][i] = true
 * - For two characters: dp[i][i+1] = (s[i] == s[i+1])
 * - For longer substrings: dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]
 *
 * ### Time Complexity: O(n^2) where n is the length of the input string
 * ### Space Complexity: O(n^2) for the DP table
 *
 * ### Applications
 * - DNA sequence analysis for identifying repeating patterns
 * - Text processing and pattern recognition
 * - Bioinformatics and genome sequencing
 * - Data compression algorithms
 *
 * @author [Arya Singh](https://github.com/ARYPROGRAMMER)
 * @see longest_palindromic_subsequence.cpp
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <string>    /// for std::string
#include <vector>    /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace longest_palindromic_substring
 * @brief Functions for the [Longest Palindromic
 * Substring](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
 * implementation
 */
namespace longest_palindromic_substring {

/**
 * @brief Find the longest palindromic substring in a given string
 * @param s input string to analyze
 * @return the longest palindromic substring found in the input
 *
 * @details
 * This function uses dynamic programming to find the longest contiguous
 * palindromic substring. It builds a table where dp[i][j] indicates whether
 * the substring from index i to j is a palindrome.
 *
 * The algorithm proceeds as follows:
 * 1. Initialize all single characters as palindromes
 * 2. Check all substrings of length 2
 * 3. Check longer substrings by extending from the center
 * 4. Track the longest palindrome found
 *
 * ### Example
 * Input: "babad"
 * Output: "bab" or "aba" (both are valid)
 *
 * Input: "cbbd"
 * Output: "bb"
 */
std::string longestPalindromicSubstring(const std::string &s) {
    int n = s.length();
    
    // Edge case: empty or single character string
    if (n <= 1) {
        return s;
    }

    // dp[i][j] will be true if substring s[i..j] is a palindrome
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    // Variables to track the longest palindrome
    int maxLength = 1;  // Every single character is a palindrome
    int start = 0;      // Starting index of longest palindrome

    // All substrings of length 1 are palindromes
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // Check for substrings of length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check for lengths greater than 2
    // len is the length of substring
    for (int len = 3; len <= n; len++) {
        // Fix the starting index
        for (int i = 0; i < n - len + 1; i++) {
            // Get the ending index of substring from
            // starting index i and length len
            int j = i + len - 1;

            // Check if s[i..j] is palindrome
            // If s[i] == s[j] and s[i+1..j-1] is a palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;

                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }

    // Return the longest palindromic substring
    return s.substr(start, maxLength);
}

/**
 * @brief Alternative approach using expand around center method
 * @param s input string to analyze
 * @param left starting left index of potential palindrome center
 * @param right starting right index of potential palindrome center
 * @return length of the palindrome centered at given indices
 *
 * @details
 * Helper function that expands around a center to find palindromes.
 * This is used by the optimized O(n^2) time, O(1) space approach.
 */
int expandAroundCenter(const std::string &s, int left, int right) {
    int n = s.length();
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    // Return the length of the palindrome
    return right - left - 1;
}

/**
 * @brief Find longest palindromic substring with optimized space complexity
 * @param s input string to analyze
 * @return the longest palindromic substring found in the input
 *
 * @details
 * This is a space-optimized version that uses the expand around center
 * approach. It considers all possible centers (both single characters and
 * pairs of characters) and expands outward to find palindromes.
 *
 * ### Time Complexity: O(n^2)
 * ### Space Complexity: O(1) - only uses constant extra space
 *
 * ### Example
 * Input: "racecar"
 * Output: "racecar"
 */
std::string longestPalindromicSubstringOptimized(const std::string &s) {
    if (s.empty()) {
        return "";
    }

    int start = 0;
    int maxLength = 0;
    int n = s.length();

    for (int i = 0; i < n; i++) {
        // Check for odd length palindromes (single character center)
        int len1 = expandAroundCenter(s, i, i);
        // Check for even length palindromes (two character center)
        int len2 = expandAroundCenter(s, i, i + 1);

        int len = std::max(len1, len2);

        if (len > maxLength) {
            start = i - (len - 1) / 2;
            maxLength = len;
        }
    }

    return s.substr(start, maxLength);
}

}  // namespace longest_palindromic_substring
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test case 1: Basic palindrome
    std::string test1 = "babad";
    std::string result1 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test1);
    std::string result1_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test1);
    // "bab" or "aba" are both valid answers
    assert((result1 == "bab" || result1 == "aba"));
    assert((result1_opt == "bab" || result1_opt == "aba"));
    std::cout << "Test 1 passed: Input \"" << test1 << "\" -> Output \""
              << result1 << "\"" << std::endl;

    // Test case 2: Even length palindrome
    std::string test2 = "cbbd";
    std::string result2 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test2);
    std::string result2_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test2);
    assert(result2 == "bb");
    assert(result2_opt == "bb");
    std::cout << "Test 2 passed: Input \"" << test2 << "\" -> Output \""
              << result2 << "\"" << std::endl;

    // Test case 3: Single character
    std::string test3 = "a";
    std::string result3 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test3);
    std::string result3_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test3);
    assert(result3 == "a");
    assert(result3_opt == "a");
    std::cout << "Test 3 passed: Input \"" << test3 << "\" -> Output \""
              << result3 << "\"" << std::endl;

    // Test case 4: Entire string is palindrome
    std::string test4 = "racecar";
    std::string result4 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test4);
    std::string result4_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test4);
    assert(result4 == "racecar");
    assert(result4_opt == "racecar");
    std::cout << "Test 4 passed: Input \"" << test4 << "\" -> Output \""
              << result4 << "\"" << std::endl;

    // Test case 5: No palindrome longer than 1
    std::string test5 = "abcdef";
    std::string result5 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test5);
    std::string result5_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test5);
    assert(result5.length() == 1);
    assert(result5_opt.length() == 1);
    std::cout << "Test 5 passed: Input \"" << test5 << "\" -> Output \""
              << result5 << "\"" << std::endl;

    // Test case 6: Complex case with multiple palindromes
    std::string test6 = "bananas";
    std::string result6 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test6);
    std::string result6_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test6);
    assert(result6 == "anana");
    assert(result6_opt == "anana");
    std::cout << "Test 6 passed: Input \"" << test6 << "\" -> Output \""
              << result6 << "\"" << std::endl;

    // Test case 7: All same characters
    std::string test7 = "aaaa";
    std::string result7 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test7);
    std::string result7_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test7);
    assert(result7 == "aaaa");
    assert(result7_opt == "aaaa");
    std::cout << "Test 7 passed: Input \"" << test7 << "\" -> Output \""
              << result7 << "\"" << std::endl;

    // Test case 8: Two character palindrome
    std::string test8 = "ac";
    std::string result8 =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(test8);
    std::string result8_opt =
        dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstringOptimized(test8);
    assert(result8.length() == 1);
    assert(result8_opt.length() == 1);
    std::cout << "Test 8 passed: Input \"" << test8 << "\" -> Output \""
              << result8 << "\"" << std::endl;

    std::cout << "\nAll tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // Interactive example
    std::cout << "\n--- Interactive Examples ---" << std::endl;
    
    std::vector<std::string> examples = {
        "forgeeksskeegfor",
        "noon",
        "programming",
        "abacdcaba"
    };

    for (const auto &example : examples) {
        std::string result = dynamic_programming::longest_palindromic_substring::
            longestPalindromicSubstring(example);
        std::cout << "Longest palindromic substring in \"" << example
                  << "\" is \"" << result << "\" (length: " << result.length()
                  << ")" << std::endl;
    }

    return 0;
}
