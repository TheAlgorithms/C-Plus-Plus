/**
 * @file
 * @brief Sliding window with an array to find the longest substring with no repeating characters.
 * @details
    * Given a string, find the longest substring with no repeating any characters.
    * The time complexity is O(n) due to the sliding window method 
    * and the space complexity is O(1) because the array is fixed size of 256.
 * @author [Tan Nguyen](https://github.com/tazyqui)
 */

#include <cassert>   /// for assert
#include <string>    // for string
#include <algorithm> // for max

/**
 * @brief This function implement the sliding window technique along side an array in order to find
 * the longest substring with no repeating character.
 * @param String s, the given string to find the substring.
 * @returns Return an integer that indicates the size of the longest substring with no repeating characters.
 */
uint8_t lengthOfLongestSubstring(std::string s) {   
    int l = 0, r = 0, res = 0; // initialize left pointer, right pointer, and result
    int arr[256] = {0}; // array to keep track of the quantity of each characters by using char as indices

    while(r < s.length()){ // iterate over each character in the string
        arr[s[r]]++; // increment count of the character at the right pointer

        while(arr[s[r]] == 2){ // if the count of the character at the right pointer is 2, it means that there is a duplicate
            // since the substring need to be contiguos, we need to move the left pointer until we reach the duplicate character
            
            arr[s[l]]--; // decrement the count of each character in the substring
            l++; // move the left pointer up

            if(s.length() - l <= res){  //if the current "window" plus the rest of the string is less than or equal to the longest substring, 
                                        //there is no need to check the rest.
                return res;
            }
        }

        res = std::max(res, r - l + 1); // compare the current substring length with the new substring length
        r++; // move the right pointer up
    }

    return res;
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
    assert(lengthOfLongestSubstring("!@1$") == 4); //check that non alphabetic character works
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

