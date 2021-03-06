
/**
 * @file
 * @brief Implementation of Abbrievation
 * (https://www.hackerrank.com/challenges/abbr/problem)
 *
 * @details
 * You can perform the following operations on the string a:
 * Capitalize zero or more of a's lowercase letters.
 * Delete all of the remaining lowercase letters in a.
 * Given two strings, a and b, determine if it's possible to make a equal to b
 * as described. If so, print YES on a new line. Otherwise, print NO.
 *
 * E.g., For example, given a = AbcDE and b = ABDE, in a we can convert 'b' and
 * delete 'c' to match b. If a = AbcDE and b = AFDE, matching is not possible
 * because letters may only be capitalized or discarded, not changed
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming Algorithms
 */
namespace dynamic_programming {
/**
 * @namespace Knapsack
 * @brief Implementation of Abbreivation problem
 */
namespace abbreviation {
/**
 *  (recursive dp function) https://www.hackerrank.com/challenges/abbr/problem
 *  Returns whether s can be converted to t with following rules:
 *  a. Capitalize zero or more of a's lowercase letters from string s
 *  b. remove all other lowercase letters from string s
 * @param dp: memo as parameter to store the result
 * @param v: visited boolean to check if the result is already computed
 * @param s: given string
 * @param t: resultant abbreivated string
 * @param i: start of string s
 * @param j: start of string j
 * @returns bool whether s can be converted to t
 */
bool abbreviation_recursion(std::vector<std::vector<bool>> &memo,
                            std::vector<std::vector<bool>> &visited,
                            const std::string &s, const std::string &t,
                            int i = 0, int j = 0) {
    bool ans = memo[i][j];
    // If the check is finished, then return true
    if (i == s.size() and j == t.size())
        return true;
    // if s string is converted but the check is not complete, return false
    else if (i == s.size() and j != t.size())
        return false;
    else if (!visited[i][j]) {
        /**
         * (s[i] == t[j]): if s char at position i is equal to t char at
         * position j, then s character is a capitalized one, move on to next
         * character
         * s[i] - 32 == t[j]: if s char at position is lowercase of t
         * at position j, then explore two possibilites:
         * 1. convert it to capitalized and move both to next pointer (i + 1, j
         * + 1)
         * 2. Discard the character and move to next char (i + 1, j)
         */
        if (s[i] == t[j])
            ans = abbreviation_recursion(memo, visited, s, t, i + 1, j + 1);
        else if (s[i] - 32 == t[j])
            ans = abbreviation_recursion(memo, visited, s, t, i + 1, j + 1) or
                  abbreviation_recursion(memo, visited, s, t, i + 1, j);
        else {
            // if s[i] is uppercase, then cannot be converted, return false
            if (s[i] >= 'A' and s[i] <= 'Z')
                ans = false;
            // s[i] is lowercase, only option is to discard this character
            else
                ans = abbreviation_recursion(memo, visited, s, t, i + 1, j);
        }
    }
    memo[i][j] = ans;
    visited[i][j] = true;
    return memo[i][j];
}
/**
 *  (iterative dp function) https://www.hackerrank.com/challenges/abbr/problem:
 *  Returns whether s can be converted to t with following rules:
 *  a. Capitalize zero or more of a's lowercase letters from string s
 *  b. remove all other lowercase letters from string s
 * @param s: string
 * @param t: resultant string
 * @returns boolean (true or false) whether s can be converted to t
 */
bool abbreviation(const std::string &s, const std::string &t) {
    std::vector<std::vector<bool>> memo(s.size() + 1,
                                        std::vector<bool>(t.size() + 1, 0));
    for (int i = 0; i <= s.size(); ++i) memo[i][0] = true;
    for (int i = 1; i <= t.size(); ++i) memo[0][i] = false;
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= t.size(); ++j) {
            if (s[i - 1] == t[j - 1])
                memo[i][j] = memo[i - 1][j - 1];
            else if (s[i - 1] - 32 == t[j - 1])
                memo[i][j] = (memo[i - 1][j - 1] or memo[i - 1][j]);
            else {
                if (s[i - 1] >= 'A' and s[i - 1] <= 'Z')
                    memo[i][j] = false;
                else
                    memo[i][j] = memo[i - 1][j];
            }
        }
    }
    return memo.back().back();
}
}  // namespace abbreviation
}  // namespace dynamic_programming

static void test() {
    std::string s = "daBcd", t = "ABC";
    std::vector<std::vector<bool>> memo(s.size() + 1,
                                        std::vector<bool>(t.size() + 1, 0)),
        visited(s.size() + 1, std::vector<bool>(t.size() + 1, 0));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               memo, visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
    s = "XXVVnDEFYgYeMXzWINQYHAQKKOZEYgSRCzLZAmUYGUGILjMDET";
    t = "XXVVDEFYYMXWINQYHAQKKOZEYSRCLZAUYGUGILMDETQVWU";
    memo = std::vector<std::vector<bool>>(s.size() + 1,
                                          std::vector<bool>(t.size() + 1, 0));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, 0));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               memo, visited, s, t) == false);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == false);

    s = "DRFNLZZVHLPZWIupjwdmqafmgkg";
    t = "DRFNLZZVHLPZWI";

    memo = std::vector<std::vector<bool>>(s.size() + 1,
                                          std::vector<bool>(t.size() + 1, 0));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, 0));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               memo, visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
}

int main() {
    test();
    return 0;
}
