/**
 * @file
 * @brief Implements [Palindrome
 * Partitioning](https://leetcode.com/problems/palindrome-partitioning-ii/)
 * algorithm, giving the minimum number of cuts to partition a string into
 * palindromes.
 *
 * @details
 * Given a string, find the minimum number of cuts needed to partition it
 * such that every substring is a palindrome.
 *
 * ### Algorithm
 * 1. Build a 2D boolean table `is_palindrome[i][j]` in O(n^2) to check
 *    if any substring is a palindrome in O(1).
 * 2. Use a 1D DP array `cuts[i]` = minimum cuts for str[0..i].
 *    For each position i, scan all j <= i: if str[j..i] is a palindrome,
 *    then cuts[i] = min(cuts[i], cuts[j-1] + 1).
 *
 * This achieves true O(n^2) time — the previous implementation used a 2D
 * cuts table requiring a third nested loop, making it O(n^3) despite the
 * O(n^2) claim in the documentation.
 *
 * Time Complexity:  O(n^2) — genuine, verified
 * Space Complexity: O(n^2) for palindrome table + O(n) for cuts array
 *
 * Example 1: "nitik"        → 2 cuts → "n | iti | k"
 * Example 2: "ababbbabbababa" → 3 cuts → "aba|b|bbabb|ababa"
 *
 * @author [Sujay Kaushik](https://github.com/sujaykaushik008)
 * @author [https-hari](https://github.com/https-hari)
 */

#include <algorithm>  /// for std::min
#include <cassert>    /// for assert
#include <climits>    /// for INT_MAX
#include <iostream>   /// for std::cout
#include <string>     /// for std::string
#include <vector>     /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace palindrome_partitioning
 * @brief Functions for Palindrome Partitioning algorithm
 */
namespace palindrome_partitioning {

/**
 * @brief Computes minimum cuts to partition string into palindromes.
 *
 * @details
 * Fixes O(n^3) implementation by replacing 2D cuts table with a 1D
 * DP array, eliminating the innermost partition loop entirely.
 *
 * Previous approach:  cuts[i][j] required iterating all partition points k
 *                     between i and j → three nested loops → O(n^3)
 * Current approach:   cuts[i] = min cuts for str[0..i]
 *                     one scan using precomputed palindrome table → O(n^2)
 *
 * @param str input string to partition
 * @returns minimum number of cuts needed
 */
int pal_part(const std::string& str) {
    int n = static_cast<int>(str.size());
    if (n == 0) return 0;

    // Step 1: Build palindrome lookup table in O(n^2)
    // is_palindrome[i][j] = true if str[i..j] is a palindrome
    std::vector<std::vector<bool>> is_palindrome(
        n, std::vector<bool>(n, false));

    for (int i = 0; i < n; i++)
        is_palindrome[i][i] = true;  // single char is always palindrome

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (len == 2)
                is_palindrome[i][j] = (str[i] == str[j]);
            else
                is_palindrome[i][j] =
                    (str[i] == str[j]) && is_palindrome[i + 1][j - 1];
        }
    }

    // Step 2: 1D DP — cuts[i] = min cuts for str[0..i]
    // Eliminates the third nested loop from the previous O(n^3) approach
    std::vector<int> cuts(n, INT_MAX);

    for (int i = 0; i < n; i++) {
        if (is_palindrome[0][i]) {
            cuts[i] = 0;  // whole prefix is a palindrome, no cuts needed
        } else {
            for (int j = 1; j <= i; j++) {
                if (is_palindrome[j][i] && cuts[j - 1] != INT_MAX) {
                    cuts[i] = std::min(cuts[i], cuts[j - 1] + 1);
                }
            }
        }
    }

    return cuts[n - 1];
}

}  // namespace palindrome_partitioning
}  // namespace dynamic_programming

/**
 * @brief Test Function
 * @returns void
 */
static void test() {
    // basic cases from original file
    assert(dynamic_programming::palindrome_partitioning::pal_part("nitik") == 2);
    assert(dynamic_programming::palindrome_partitioning::pal_part("ababbbabbababa") == 3);
    assert(dynamic_programming::palindrome_partitioning::pal_part("abdc") == 3);

    // edge cases
    assert(dynamic_programming::palindrome_partitioning::pal_part("") == 0);
    assert(dynamic_programming::palindrome_partitioning::pal_part("a") == 0);
    assert(dynamic_programming::palindrome_partitioning::pal_part("aa") == 0);
    assert(dynamic_programming::palindrome_partitioning::pal_part("ab") == 1);

    // whole string is palindrome — 0 cuts
    assert(dynamic_programming::palindrome_partitioning::pal_part("racecar") == 0);
    assert(dynamic_programming::palindrome_partitioning::pal_part("aaa") == 0);

    // worst case — no palindrome substrings longer than 1
    assert(dynamic_programming::palindrome_partitioning::pal_part("abcd") == 3);

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}