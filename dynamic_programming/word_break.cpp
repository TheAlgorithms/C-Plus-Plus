
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

#include <limits.h>

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::vector;

class Solution {
 public:
    bool exists(const string s, const unordered_set<string> strSet) {
        return strSet.find(s) != strSet.end();
    }

    bool check(const string s, const unordered_set<string> strSet, int pos,
               vector<int>& dp) {
        if (pos == s.length()) {
            return true;
        }

        if (dp[pos] != INT_MAX) {
            return dp[pos] == 1;
        }

        string wordTillNow = "";
        for (int i = pos; i < s.length(); i++) {
            wordTillNow += string(1, s[i]);
            if (exists(wordTillNow, strSet) and check(s, strSet, i + 1, dp)) {
                dp[pos] = 1;
                return true;
            }
        }
        dp[pos] = 0;
        return false;
    }

    bool wordBreak(const string s, const vector<string>& wordDict) {
        unordered_set<string> strSet;
        for (const auto s : wordDict) {
            strSet.insert(s);
        }

        vector<int> dp(s.length(), INT_MAX);
        return check(s, strSet, 0, dp);
    }
};

int main() {
    const string s = "applepenapple";
    const vector<string> wordDict = {"apple", "pen"};
    cout << Solution().wordBreak(s, wordDict) << endl;
}