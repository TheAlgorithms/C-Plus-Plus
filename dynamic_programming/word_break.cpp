
/*
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, determine if s can be segmented into a space-separated sequence
of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the
segmentation. You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen
apple". Note that you are allowed to reuse a dictionary word. Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
*/

#include <climits>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::vector;

/**
 * @namespace dynamic_programming
 * @brief Dynamic programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace word_break
 * @brief Functions for Word Break algorithm
 */
namespace word_break {
/**
 * @brief Solution class
 */
class Solution {
 public:
    /**
     * @brief Function that checks if the string passed in param is present in
     * the the unordered_set passed
     *
     * @param str the string to be searched
     * @param strSet unordered set of string, that is to be looked into
     * @returns true if str is present in strSet
     */
    bool exists(const string &str, const unordered_set<string> &strSet) {
        return strSet.find(str) != strSet.end();
    }

    /**
     * @brief Function that checks if the string passed in param can be
     * segmented from position 'pos', and then correctly go on to segment the
     * rest of the string correctly as well to reach a solution
     *
     * @param s the complete string to be segmented
     * @param strSet unordered set of string, that is to be used as the
     * reference dictionary
     * @param pos the index value at which we will segment string and test
     * further if it is correctly segmented at pos
     * @param dp the vector to memoize solution for each position
     * @returns `true` if str is present in strSet
     * @returns `false` if
     */
    bool check(const string &s, const unordered_set<string> &strSet, int pos,
               vector<int> *dp) {
        if (pos == s.length()) {
            // if we have reached till the end of the string, means we have
            // segmented throughout correctly hence we have a solution, thus
            // returning true
            return true;
        }

        if (dp->at(pos) != INT_MAX) {
            // if dp[pos] is not INT_MAX, means we must have saved a solution
            // for the position pos; then return if the solution at pos is true
            // or not
            return dp->at(pos) == 1;
        }

        string wordTillNow =
            "";  // string to save the prefixes of word till different positons

        for (int i = pos; i < s.length(); i++) {
            // Loop starting from pos to end, to check valid set of
            // segmentations if any
            wordTillNow +=
                string(1, s[i]);  // storing the prefix till the position i

            // if the prefix till current position is present in the dictionary
            // and the remaining substring can also be segmented legally, then
            // set solution at position pos in the memo, and return true
            if (exists(wordTillNow, strSet) and check(s, strSet, i + 1, dp)) {
                dp->at(pos) = 1;
                return true;
            }
        }
        // if function has still not returned, then there must be no legal
        // segmentation possible after segmenting at pos
        dp->at(pos) = 0;  // so set solution at pos as false
        return false;     // and return no solution at position pos
    }

    /**
     * @brief Function that checks if the string passed in param can be
     * segmented into the strings present in the vector.
     * In others words, it checks if any permutation of strings in
     * the vector can be concatenated to form the final string.
     *
     * @param s the complete string to be segmented
     * @param wordDict a vector of words to be used as dictionary to look into
     * @returns bool, true if s can be
     */
    bool wordBreak(const string &s, const vector<string> &wordDict) {
        // unordered set to store words in the dictionary for contant time
        // search
        unordered_set<string> strSet;
        for (const auto &s : wordDict) {
            strSet.insert(s);
        }
        // a vector to be used for memoization, whose value at index i will
        // tell if the string s can be segmented (correctly) at position i.
        // initializing it with INT_MAX (which will denote no solution)
        vector<int> dp(s.length(), INT_MAX);

        // calling check method with position = 0, to check from left
        // from where can be start segmenting the complete string in correct
        // manner
        return check(s, strSet, 0, &dp);
    }
};
}  // namespace word_break
}  // namespace dynamic_programming


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // the complete string
    const string s = "applepenapple";
    // the dictionary to be used
    const vector<string> wordDict = {"apple", "pen"};

    // should return true, as applepenapple can be segmented as apple + pen +
    // apple
    cout << Solution().wordBreak(s, wordDict) << endl;
}
