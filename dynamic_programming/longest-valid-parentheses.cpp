/**
 * @file
 * @details
 * Given a string containing just the characters '(' and ')', 
 * find the length of the longest valid (well-formed) parentheses substring.
 *
 * ### Approach
 * This solution uses Dynamic Programming.
 * We maintain an array `longest[]` where `longest[i]` represents 
 * the length of the longest valid parentheses substring ending at index `i`.
 *
 * - If `s[i] == '('`, then `longest[i] = 0` (a valid substring cannot end with '(').
 * - If `s[i] == ')'`:
 *   - If `s[i - 1] == '('`, then `longest[i] = longest[i - 2] + 2`
 *   - Else if `s[i - 1] == ')'` and `s[i - longest[i - 1] - 1] == '('`,
 *     then `longest[i] = longest[i - 1] + 2 + longest[i - longest[i - 1] - 2]`
 *
 * Example:
 * Input: "()(())"
 * At i = 5, longest = [0, 2, 0, 0, 2, 0]
 * longest[5] = longest[4] + 2 + longest[1] = 6
 *
 * @note
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Dynamic Programming based solution to find the longest valid parentheses substring.
 * @param s Input string containing '(' and ')'
 * @return Length of the longest valid parentheses substring
 */
int longestValidParentheses(const string &s) {
    if (s.length() <= 1) return 0;

    int curMax = 0;
    vector<int> longest(s.size(), 0);

    for (int i = 1; i < s.length(); i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                longest[i] = (i - 2 >= 0 ? longest[i - 2] + 2 : 2);
            } else if (i - longest[i - 1] - 1 >= 0 && s[i - longest[i - 1] - 1] == '(') {
                longest[i] = longest[i - 1] + 2 +
                             ((i - longest[i - 1] - 2 >= 0) ? longest[i - longest[i - 1] - 2] : 0);
            }
            curMax = max(curMax, longest[i]);
        }
    }
    return curMax;
}

/**
 * @brief Concise version 
 * Same logic as above but written in a more compact form.
 */
int longestValidParenthesesConcise(const string &s) {
    if (s.length() <= 1) return 0;

    int curMax = 0;
    vector<int> longest(s.size(), 0);

    for (int i = 1; i < s.length(); i++) {
        if (s[i] == ')' && i - longest[i - 1] - 1 >= 0 && s[i - longest[i - 1] - 1] == '(') {
            longest[i] = longest[i - 1] + 2 +
                         ((i - longest[i - 1] - 2 >= 0) ? longest[i - longest[i - 1] - 2] : 0);
            curMax = max(curMax, longest[i]);
        }
    }
    return curMax;
}

/**
 * @brief Driver code for demonstration and basic testing.
 */
int main() {
    vector<string> test_cases = {
        "(()",          // expected 2
        ")()())",       // expected 4
        "()(())",       // expected 6
        "((((((",       // expected 0
        "()(()))))"     // expected 6
    };

    cout << "Testing Longest Valid Parentheses using DP:\n";
    for (const auto &s : test_cases) {
        cout << "Input: " << s 
             << " | Output: " << longestValidParentheses(s) << endl;
    }

    cout << "\nTesting Concise Version:\n";
    for (const auto &s : test_cases) {
        cout << "Input: " << s 
             << " | Output: " << longestValidParenthesesConcise(s) << endl;
    }

    return 0;
}
