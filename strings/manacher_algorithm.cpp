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
 * @brief A function that implements Manacher's algorithm
 * @param prototype is the string where algorithm finds a palindromic substring.
 * This string can contain any character except `@` `#` `&`
 * @returns the largest palindromic substring
 */
std::string manacher(const std::string &prototype) {
    if (prototype.size() > 0) {
        // stuffing characters between the input string to handle cases with
        // even length palindrome
        std::string stuffed_string = "";
        for (auto str : prototype) {
            stuffed_string += str;
            stuffed_string += "#";
        }
        stuffed_string = "@#" + stuffed_string + "&";

        std::vector<uint64_t> palindrome_max_half_length(
            stuffed_string.size(),
            0);  // this array will consist of largest possible half length of
                 // palindrome centered at index (say i with respect to the
                 // stuffed string). This value will be lower bound of half
                 // length since single character is a palindrome in itself.

        uint64_t bigger_center =
            0;  // this is the index of the center of palindromic
                // substring which would be considered as the larger
                // palindrome, having symmetric halves

        uint64_t right = 0;  // this is the maximum length of the palindrome
                             // from 'bigger_center' to the rightmost end

        // i is considered as center lying within one half of the palindrone
        // which is centered at 'bigger_center'
        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (i < right) {  // when i is before right end, considering
                              // 'bigger_center' as center of palindrome
                uint64_t opposite_to_i =
                    2 * bigger_center -
                    i;  // this is the opposite end of string, if
                        // centered at center, and having one end as i

                // finding the minimum possible half length among
                // the palindrome on having center at opposite end,
                // and the string between i and right end,
                // considering 'bigger_center' as center of palindrome
                palindrome_max_half_length[i] = std::min(
                    palindrome_max_half_length[opposite_to_i], right - i);
            }

            // expanding the palindrome across the maximum stored length in the
            // array, centered at i
            while (stuffed_string[i + (palindrome_max_half_length[i] + 1)] ==
                   stuffed_string[i - (palindrome_max_half_length[i] + 1)]) {
                palindrome_max_half_length[i]++;
            }

            // if palindrome centered at i exceeds the rightmost end of
            // palindrome centered at 'bigger_center', then i will be made the
            // 'bigger_center' and right value will also be updated with respect
            // to center i
            if (i + palindrome_max_half_length[i] > right) {
                bigger_center = i;
                right = i + palindrome_max_half_length[i];
            }
        }

        // now extracting the first largest palindrome
        uint64_t half_length = 0;   // half length of the largest palindrome
        uint64_t center_index = 0;  // index of center of the largest palindrome

        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (palindrome_max_half_length[i] > half_length) {
                half_length = palindrome_max_half_length[i];
                center_index = i;
            }
        }

        std::string palindromic_substring =
            "";  // contains the resulting largest palindrome

        if (half_length > 0) {
            // extra information: when '#' is the center, then palindromic
            // substring will have even length, else palindromic substring will
            // have odd length

            uint64_t start =
                center_index - half_length +
                1;  // index of first character of palindromic substring
            uint64_t end =
                center_index + half_length -
                1;  // index of last character of palindromic substring
            for (uint64_t index = start; index <= end; index += 2) {
                palindromic_substring += stuffed_string[index];
            }
        } else {
            // if length = 0, then there does not exist any palindrome of length
            // > 1 so we can assign any character of length 1 from string as the
            // palindromic substring
            palindromic_substring = prototype[0];
        }
        return palindromic_substring;

    } else {
        // handling case when string is empty
        return "";
    }
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
