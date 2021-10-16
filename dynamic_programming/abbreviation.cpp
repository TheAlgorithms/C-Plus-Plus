/**
 * @file
 * @brief Implementation of
 * [Abbrievation](https://www.hackerrank.com/challenges/abbr/problem)
 *
 * @details
 * Given two strings, `a` and `b`, determine if it's possible to make `a` equal
 * to `b` You can perform the following operations on the string `a`:
 * 1. Capitalize zero or more of `a`'s lowercase letters.
 * 2. Delete all of the remaining lowercase letters in `a`.
 *
 * ### Algorithm
 * The idea is in the problem statement itself: iterate through characters of
 * string `a` and `b` (for character indexes `i` and `j` respectively):
 * 1. If `a[i]` and `b[j]` are equal, then move to next position
 * 2. If `a[i]` is lowercase of `b[j]`, then explore two possibilities:
 * a. Capitalize `a[i]` or
 * b. Skip `a[i]`
 * 3. If the `a[i]` is not uppercase, just discard that character, else return
 * `false`
 *
 * Time Complexity: (O(|a|*|b|)) where `|a|` => length of string `a`
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */

#include <cassert>   /// for `assert`
#include <iostream>  /// for IO operations
#include <string>    /// for `std::string` library
#include <vector>    /// for `std::vector` STL library
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming Algorithms
 */
namespace dynamic_programming {
/**
 * @namespace abbreviation
 * @brief Functions for
 * [Abbreviation](https://www.hackerrank.com/challenges/abbr/problem)
 * implementation
 */
namespace abbreviation {
/**
 * @brief
 * Recursive Dynamic Programming function
 * @details
 * Returns whether `s` can be converted to `t` with following rules:
 * a. Capitalize zero or more of a's lowercase letters from string `s`
 * b. remove all other lowercase letters from string `s`
 * @param memo To store the result
 * @param visited boolean to check if the result is already computed
 * @param str given string, which might not be abbreivated
 * @param result resultant abbreivated string
 * @param str_idx index for string `str`, helpful for transitions
 * @param result_idx index for string `result`, helpful for transitions
 * @returns `false` if string `str` cannot be converted to `result`
 * @returns `true` if string `str` can be converted to `result`
 */
bool abbreviation_recursion(std::vector<std::vector<bool>> *memo,
                            std::vector<std::vector<bool>> *visited,
                            const std::string &str, const std::string &result,
                            uint32_t str_idx = 0, uint32_t result_idx = 0) {
    bool ans = memo->at(str_idx).at(result_idx);
    if (str_idx == str.size() && result_idx == result.size()) {
        return true;
    } else if (str_idx == str.size() && result_idx != result.size()) {
        // result `t` is not converted, return false
        return false;
    } else if (!visited->at(str_idx).at(result_idx)) {
        /**
         * `(str[i] == result[j])`: if str char at position i is equal to
         * `result` char at position j, then s character is a capitalized one,
         * move on to next character `str[i] - 32 == result[j]`:
         * if `str[i]` character is lowercase of `result[j]` then explore two
         * possibilites:
         * 1. convert it to capitalized letter and move both to next pointer
         * `(i + 1, j + 1)`
         * 2. Discard the character `(str[i])` and move to next char `(i + 1,
         * j)`
         */
        if (str[str_idx] == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1);
        } else if (str[str_idx] - 32 == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1) ||
                  abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx);
        } else {
            // if `str[i]` is uppercase, then cannot be converted, return
            // `false`
            // else `str[i]` is lowercase, only option is to discard this
            // character
            if (str[str_idx] >= 'A' && str[str_idx] <= 'Z') {
                ans = false;
            } else {
                ans = abbreviation_recursion(memo, visited, str, result,
                                             str_idx + 1, result_idx);
            }
        }
    }
    (*memo)[str_idx][result_idx] = ans;
    (*visited)[str_idx][result_idx] = true;
    return (*memo)[str_idx][result_idx];
}
/**
 * @brief
 * Iterative Dynamic Programming function
 * @details
 * Returns whether `s` can be converted to `t` with following rules:
 * a. Capitalize zero or more of s's lowercase letters from string `s`
 * b. remove all other lowercase letters from string `s`
 * Note: The transition states for iterative is similar to recursive as well
 * @param str given string, which might not be abbreivated
 * @param result resultant abbreivated string
 * @returns `false` if string `str` cannot be converted to `result`
 * @returns `true` if string `str` can be converted to `result`
 */
bool abbreviation(const std::string &str, const std::string &result) {
    std::vector<std::vector<bool>> memo(
        str.size() + 1, std::vector<bool>(result.size() + 1, false));

    for (uint32_t i = 0; i <= str.size(); ++i) {
        memo[i][0] = true;
    }
    for (uint32_t i = 1; i <= result.size(); ++i) {
        memo[0][i] = false;
    }
    for (uint32_t i = 1; i <= str.size(); ++i) {
        for (uint32_t j = 1; j <= result.size(); ++j) {
            if (str[i - 1] == result[j - 1]) {
                memo[i][j] = memo[i - 1][j - 1];
            } else if (str[i - 1] - 32 == result[j - 1]) {
                memo[i][j] = (memo[i - 1][j - 1] || memo[i - 1][j]);
            } else {
                if (str[i - 1] >= 'A' && str[i - 1] <= 'Z') {
                    memo[i][j] = false;
                } else {
                    memo[i][j] = memo[i - 1][j];
                }
            }
        }
    }
    return memo.back().back();
}
}  // namespace abbreviation
}  // namespace dynamic_programming

/**
 * @brief Self test-implementations
 * @returns void
 */
static void test() {
    std::string s = "daBcd", t = "ABC";
    std::vector<std::vector<bool>> memo(s.size() + 1,
                                        std::vector<bool>(t.size() + 1, false)),
        visited(s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
    s = "XXVVnDEFYgYeMXzWINQYHAQKKOZEYgSRCzLZAmUYGUGILjMDET";
    t = "XXVVDEFYYMXWINQYHAQKKOZEYSRCLZAUYGUGILMDETQVWU";
    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == false);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == false);

    s = "DRFNLZZVHLPZWIupjwdmqafmgkg";
    t = "DRFNLZZVHLPZWI";

    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
