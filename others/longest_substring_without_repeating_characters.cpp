/**
 * @file
 * @brief Solution for Longest Substring Without Repeating Characters problem.
 * @details
 * Problem link: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 * 
 * Intuition:
 * The intuition is straightforward and simple. We track the frequency of characters.
 * Since we can't use a string to track the longest substring without repeating characters
 * efficiently (as removing a character from the front of a string isn't O(1)),
 * we optimize the solution using a deque approach.
 *
 * Approach:
 * 1) Initialize an unordered_map to track the frequency of characters.
 * 2) Use a deque for pushing characters, and update the result deque (`res`) with the current deque (`temp`) 
 *    whenever we find a longer substring.
 * 3) Use a while loop to reduce the frequency from the front, incrementing `i`, 
 *    and removing characters from the `temp` deque as we no longer need them.
 * 4) Return `res.size()` as we are interested in the length of the longest substring.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 * 
 * Examples:
 * - testcase1: s = "abcabcbb", output = 3.
 * - testcase2: s = "bbbbb", output = 1.
 * - testcase3: s = "pwwkew", output = 3.
 * 
 * I hope this helps to understand.
 * Thank you!
 **/

// ----------------- Header files ----------------------------------
#include <iostream>        // for input and output read/write.
#include <unordered_map>   // to use it for character frequency.
#include <deque>           // for push and pop operations at O(1) time.
#include <string>          // for taking string as input.

using namespace std;       // using the namespace standard to reduce redundant usage of std::

//------------------ Longest_Substring Class -------------------------------
/**
 * @class Solution
 * @brief Class that solves the Longest Substring Without Repeating Characters problem.
 */
class Longest_Substring {
public:
    /**
     * @brief Function to find the length of the longest substring without repeating characters.
     * @param s Input string.
     * @returns Length of the longest substring.
     */
    int lengthOfLongestSubstring(string s) {
        // If the size of string is 1, then it will be the answer.
        if (s.size() == 1) return 1;

        // Map used to store the character frequency.
        unordered_map<char, int> m;
        int n = s.length();

        // Deque to remove from back if repeating characters are present.
        deque<char> temp;
        deque<char> res;
        int i, j;

        // Sliding window approach using two pointers.
        for (i = 0, j = 0; i < n && j < n;) {
            m[s[j]]++;

            // If repeating character found, update result and remove from the front.
            if (m[s[j]] > 1) {
                if (temp.size() > res.size()) {
                    res = temp;
                }

                while (m[s[j]] > 1) {
                    temp.pop_front();
                    m[s[i]]--;
                    i++;
                }
            }

            // Add the current character to the deque.
            temp.push_back(s[j]);
            j++;
        }

        // Final check to update result.
        if (temp.size() > res.size()) {
            res = temp;
        }

        return res.size();  // Return the length of the longest substring.
    }
};

//-------------------- Main function -------------------------------
/**
 * @brief Main function.
 * @returns 0 on successful execution.
 */
int main() {
    // Create an object of the Solution class to call the function.
    Longest_Substring s;

    // User inputted string.
    string str;
    cout << "Enter the string: " << endl;
    cin >> str;

    // Function call to get the length of the longest substring without repeating characters.
    cout << soln.lengthOfLongestSubstring(str) << endl;

    return 0;
}
