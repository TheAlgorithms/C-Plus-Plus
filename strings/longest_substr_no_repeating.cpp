/*
* @file
* @brief Sliding window solution to find the longest substring with no repeating characters
* @details
 * Given a string we are required to find the
 * longest possible substring without any repeating characters.
 * The time and space complexity are both O(n) since an unordered set is used
 * and the entire string is traversed.
* @author [Saketh Renangi](https://github.com/rensaketh)
*/

#include <cassert>         /// for assert
#include <unordered_set>  /// for unordered_set
#include <string>        /// for string

/**
 * @brief This function uses the sliding window approach to
 * find the longest substring that does not have a repeating character
 *
 * @param String named s, used to find substrings from this string
 *
 * @returns Retuns an integer that is the length of the longest substring
 * with no repeated characters
 */

int lengthOfLongestSubstring(std::string s) {
    std::unordered_set<char> letters;
    int leftPointer = 0, rightPointer = 0, length = 0;
    while (rightPointer < s.length()) {
        if (letters.find(s.at(rightPointer)) == letters.end()) {
            letters.insert(s.at(rightPointer));
            rightPointer++;
            if (letters.size() > length) {
                length = letters.size();
            }
        } else {
            letters.erase(s.at(leftPointer));
            leftPointer++;
        }
    }
    return length;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    assert(lengthOfLongestSubstring("abcabcbb") == 3); // this ensures that the algorithm works as expected
    assert(lengthOfLongestSubstring("aaaaaaaaaaa") == 1); //this ensures that the algorithm works for a string with all duplicates
    assert(lengthOfLongestSubstring("") == 0); //this ensures the algorithm works for an empty string
    assert(lengthOfLongestSubstring("abcdefghijklmnopqrstuvwxyz") == 26); //checks for longer strings
    // can have multiple checks
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    // code here
    return 0;
}
