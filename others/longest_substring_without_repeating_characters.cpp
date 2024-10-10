/**
 * @file
 * @brief Solution for Longest Substring Without Repeating Characters problem.
 * @details
 * Problem link: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 * 
 * Intuition:
 * 1) The intuition is straightforward and simple. We track the frequency of characters.
 * 2) Since we can't use a string to track the longest substring without repeating characters efficiently (as removing a character from the front of a string isn't O(1)), we optimize the solution using a deque approach.
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
 * I hope this helps to understand.
 * Thank you!
 * @author [Ashish Kumar Sahoo](github.com/ashish5kmax)
 **/

#include <iostream>        // for IO Operations
#include <unordered_map>   // for std::unordered_map
#include <deque>           // for std::deque
#include <string>          // for string class/string datatype which is taken as input
#include <cassert>         // for assert

/**
 * @class Longest_Substring
 * @brief Class that solves the Longest Substring Without Repeating Characters problem.
 */
class Longest_Substring {
public:
    /**
     * @brief Function to find the length of the longest substring without repeating characters.
     * @param s Input string.
     * @return Length of the longest substring.
     */
    int lengthOfLongestSubstring(std::string s) {
        // If the size of string is 1, then it will be the answer.
        if (s.size() == 1) return 1;

        // Map used to store the character frequency.
        std::unordered_map<char, int> m;
        int n = s.length();

        // Deque to remove from back if repeating characters are present.
        std::deque<char> temp;
        std::deque<char> res;
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

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    Longest_Substring soln;
    assert(soln.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(soln.lengthOfLongestSubstring("bbbbb") == 1);
    assert(soln.lengthOfLongestSubstring("pwwkew") == 3);
    assert(soln.lengthOfLongestSubstring("") == 0); // Test case for empty string
    assert(soln.lengthOfLongestSubstring("abcdef") == 6); // Test case for all unique characters
    assert(soln.lengthOfLongestSubstring("a") == 1); // Single character
    std::cout << "All test cases passed!" << std::endl;
}

/**
 * @brief Main function.
 * @return 0 on successful execution.
 */
int main() {
    tests(); // run self-test implementations
    return 0;
}
