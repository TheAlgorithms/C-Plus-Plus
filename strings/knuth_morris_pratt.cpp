/**
 * @file
 * @brief The [Knuth-Morris-Pratt
 * Algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm) for
 * finding a pattern within a piece of text with complexity O(n + m)
 * @details
 * 1. Preprocess pattern to identify any suffixes that are identical to
 * prefixes. This tells us where to continue from if we get a mismatch between a
 * character in our pattern and the text.
 * 2. Step through the text one character at a time and compare it to a
 * character in the pattern updating our location within the pattern if
 * necessary
 * @author [Yancey](https://github.com/Yancey2023)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <string>    /// for std::string
#include <vector>    /// for std::vector

/**
 * @namespace string_search
 * @brief String search algorithms
 */
namespace string_search {
/**
 * @brief Generate the partial match table aka failure function for a pattern to
 * search.
 * @param pattern text for which to create the partial match table
 * @returns the partial match table as a vector array
 */
std::vector<size_t> getFailureArray(const std::string &pattern) {
    size_t pattern_length = pattern.size();
    std::vector<size_t> failure(pattern_length + 1);
    failure[0] = std::string::npos;
    size_t j = std::string::npos;
    for (int i = 0; i < pattern_length; i++) {
        while (j != std::string::npos && pattern[j] != pattern[i]) {
            j = failure[j];
        }
        failure[i + 1] = ++j;
    }
    return failure;
}

/**
 * @brief KMP algorithm to find a pattern in a text
 * @param pattern string pattern to search
 * @param text text in which to search
 * @returns the starting index of the pattern if found
 * @returns `std::string::npos` if not found
 */
size_t kmp(const std::string &pattern, const std::string &text) {
    if (pattern.empty()) {
        return 0;
    }
    std::vector<size_t> failure = getFailureArray(pattern);
    size_t text_length = text.size();
    size_t pattern_length = pattern.size();
    size_t k = 0;
    for (size_t j = 0; j < text_length; j++) {
        while (k != std::string::npos && pattern[k] != text[j]) {
            k = failure[k];
        }
        if (++k == pattern_length) {
            return j - k + 1;
        }
    }
    return std::string::npos;
}
}  // namespace string_search

using string_search::kmp;

/**
 * @brief self-test implementations
 * @returns void
 */
static void tests() {
    assert(kmp("abc1abc12l", "alskfjaldsabc1abc1abc12k2") == std::string::npos);
    assert(kmp("bca", "abcabc") == 1);
    assert(kmp("World", "helloWorld") == 5);
    assert(kmp("c++", "his_is_c++") == 7);
    assert(kmp("happy", "happy_coding") == 0);
    assert(kmp("", "pattern is empty") == 0);

    // this lets the user know that the tests have passed
    std::cout << "All KMP algorithm tests have successfully passed!\n";
}

/*
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
