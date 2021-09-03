/**
 * @file
 * @brief The [Z function](https://cp-algorithms.com/string/z-function.html) for
 * finding occurences of a pattern within a piece of text with time and space
 * complexity O(n + m)
 * @details
 * 1. The Z-function for a string is an array of length n where the
 * i-th element is equal to the greatest number of characters starting
 * from the position i that coincide with the first characters of s.
 * 2. E.g.: string: ababb then z[2]=2 as s[2]=s[0] and s[3]=s[1] and s[4]!=s[2]
 * @author [Ritika Gupta](https://github.com/RitikaGupta8734)
 */

#include <iostream>  /// for IO operations
#ifdef _MSC_VER
#include <string>  /// for string (use this for MS Visual C++)
#else
#include <cstring>  /// for string
#endif
#include <cassert>  /// for assert
#include <vector>   /// for std::vector

/**
 * @brief Generate the Z-function for the inputted string.
 * \param[in] pattern text on which to apply the Z-function
 * \returns the Z-function output as a vector array
 */
std::vector<uint64_t> Z_function(const std::string &pattern) {
    uint64_t pattern_length = pattern.size();
    std::vector<uint64_t> z(pattern_length, 0);

    for (uint64_t i = 1, l = 0, r = 0; i < pattern_length; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < pattern_length &&
               pattern[z[i]] == pattern[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
        }
    }
    return z;
}

/**
 * @brief Using Z_function to find a pattern in a text
 * \param[in] pattern string pattern to search
 * \param[in] text text in which to search
 * \returns a vector of starting indexes where pattern is found in the text
 */
std::vector<uint64_t> find_pat_in_text(const std::string &pattern,
                                       const std::string &text) {
    uint64_t text_length = text.size(), pattern_length = pattern.size();
    std::vector<uint64_t> z = Z_function(pattern + '#' + text);
    std::vector<uint64_t> matching_indexes;

    for (uint64_t i = 0; i < text_length; i++) {
        if (z[i + pattern_length + 1] == pattern_length) {
            matching_indexes.push_back(i);
        }
    }
    return matching_indexes;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // usual case
    std::string text1 = "alskfjaldsabc1abc1abcbksbcdnsdabcabc";
    std::string pattern1 = "abc";

    // matching_indexes1 gets the indexes where pattern1 exists in text1
    std::vector<uint64_t> matching_indexes1 = find_pat_in_text(pattern1, text1);
    assert((matching_indexes1 == std::vector<uint64_t>{10, 14, 18, 30, 33}));

    // corner case
    std::string text2 = "greengrass";
    std::string pattern2 = "abc";

    // matching_indexes2 gets the indexes where pattern2 exists in text2
    std::vector<uint64_t> matching_indexes2 = find_pat_in_text(pattern2, text2);
    assert((matching_indexes2 == std::vector<uint64_t>{}));
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
