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

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector STL
#ifdef _MSC_VER
#include <string>  /// for string (required for MS Visual C++)
#else
#include <cstring>  /// for string
#endif

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
 * @brief A function to stuff characters between a string to handle cases with
 * even length palindrome
 * @param s text to facilitate stuffing
 * @returns a copy of 's' with stuffed characters
 */
auto stuffed(const std::string& s) {
    std::string stuffed_str;
    for (auto const& c : s) {
        stuffed_str += c;
        stuffed_str += '#';
    }

    return stuffed_str = "@#" + stuffed_str + '&';
}

/**
 * @brief A function expanding the palindrome across the maximum stored length
 * in the array, centered at i
 * @param s text returned from stuffed(const std::string&)
 * @param max_length current max half length of palindrome
 * @param i center lying within one half of the palindrone
 * @returns void
 */
auto expand_palindrome(const std::string& s, uint64_t& max_length, uint64_t i) {
    while (s[i + (max_length + 1)] == s[i - (max_length + 1)]) {
        ++max_length;
    }
}

/**
 * @brief A function to find the min possible half length among the palindrome
 * @param stuffed_string text returned from stuffed(const std::string&)
 * @returns a vector of largest possible half length of palindrome centered at
 * index (say i with respect to the stuffed string). This value will be lower
 * bound of half length since single character is a palindrome in itself.
 */
auto half_lengths(const std::string& stuffed_string) {
    auto stuffed_str_size = stuffed_string.size();
    std::vector<uint64_t> half_lengths(stuffed_str_size);

    uint64_t bigger_center =
        0;  // index of the center of palindromic substring which would be
            // considered as the larger palindrome, having symmetric halves

    uint64_t right = 0;  // maximum length of the palindrome from
                         // 'bigger_center' to the rightmost end

    // i is considered as center lying within one half of the palindrone
    // which is centered at 'bigger_center'
    for (uint64_t i = 1; i < stuffed_str_size - 1; ++i) {
        if (i < right) {
            auto opposite_to_i =
                2 * bigger_center - i;  // opposite end of string, if centered
                                        // at center, and having one end as i

            half_lengths[i] = std::min(half_lengths[opposite_to_i], right - i);
        }

        auto& current_max_half_length = half_lengths[i];
        expand_palindrome(stuffed_string, current_max_half_length, i);

        // if palindrome centered at i exceeds the rightmost end of palindrome
        // centered at 'bigger_center', then i will be made the 'bigger_center'
        // and right value will also be updated with respect to center i
        if (i + current_max_half_length > right) {
            bigger_center = i;
            right = i + current_max_half_length;
        }
    }

    return half_lengths;
}

/**
 * @brief A helper function to extract indices
 * @param stuffed_str_sz is the length of the stuffed string
 * @param v contains largest possible half length of palindrome
 * @returns a pair, {half length of largest palindrome, and index of its center}
 */
auto extract_indices(const std::vector<uint64_t>& v, uint64_t stuffed_str_sz) {
    uint64_t half_length = 0;
    uint64_t center_index = 0;

    for (uint64_t i{1}; i < stuffed_str_sz - 1; ++i) {
        if (auto max_half_length = v[i]; max_half_length > half_length) {
            half_length = max_half_length;
            center_index = i;
        }
    }

    return std::pair{half_length, center_index};
}

/**
 * @brief A helper function to simplify manacher(const std::string&)
 * @param half_length is half the length of the largest palindrome
 * @param center_index index of center of the largest palindrome
 * @param s main string we extract from
 * @returns the largest palindromic substring
 */
auto palindromic_substring(uint64_t half_length, uint64_t center_index,
                           const std::string& s) {
    auto start = center_index - half_length + 1;  // substring[0]
    auto end = center_index + half_length - 1;    // substring[n - 1]
    std::string substring;
    for (auto index = start; index <= end; index += 2) {
        substring += s[index];
    }

    return substring;
}

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

    auto stuffed_str_size = stuffed_string.size();
    auto palindrome_max_half_length;

    auto const& [half_length, center_index]{
        extract_indices(half_lengths(stuffed_string), stuffed_str_size)};

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
