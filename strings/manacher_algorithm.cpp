/**
 * @file
 * @brief Implementation of [Manacher's
 * Algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
 * @details
 * Manacher's Algorithm is used to find the longest palindromic substring within
 * a string in O(n) time. It exploits the property of a palindrome that its
 * first half is symmetric to the last half, and thus if the first half is a
 * palindrome, then last half is also a palindrome.
 * @author [Riti Kumari](https://github.com/riti2409)
 */

#include "manacher_algorithm.h"  // contains implementation of helper functions for the main algorithm

/**
 * @namespace strings
 * @brief Algorithms with strings
 */
namespace strings {
/**
 * @namespace manacher
 * @brief Functions for [Manacher's
 * Algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
 * implementation
 */
namespace manacher {

/**
 * @brief A function that implements Manacher's algorithm
 * @param prototype is the string where algorithm finds a palindromic substring.
 * This string can contain any character except `@` `#` `&`
 * @returns the largest palindromic substring
 */
std::string manacher(const std::string& prototype) {
    if (prototype.empty())
        return {};

    std::string stuffed_string = stuffed(prototype);

    auto const& [half_length, center_index]{
        extract_indices(half_lengths(stuffed_string), stuffed_string.size())};

    // now extracting the first largest palindrome...
    // if length = 0, then there does not exist any palindrome with length > 1
    // so we can return a character from string as substring
    return half_length > 0 ? palindromic_substring(half_length, center_index,
                                                   stuffed_string)
                           : std::string{prototype[0]};
}

}  // namespace manacher
}  // namespace strings

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(strings::manacher::manacher("") == "");
    assert(strings::manacher::manacher("abababc") == "ababa");
    assert(strings::manacher::manacher("cbaabd") == "baab");
    assert(strings::manacher::manacher("DedzefDeD") == "DeD");
    assert(strings::manacher::manacher("XZYYXXYZXX") == "YXXY");
    assert(strings::manacher::manacher("1sm222m10abc") == "m222m");
    assert(strings::manacher::manacher("798989591") == "98989");
    assert(strings::manacher::manacher("xacdedcax") == "xacdedcax");
    assert(strings::manacher::manacher("xaccax") == "xaccax");
    assert(strings::manacher::manacher("a") == "a");
    assert(strings::manacher::manacher("xy") == "x");
    assert(strings::manacher::manacher("abced") == "a");

    std::cout << "All tests have passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
