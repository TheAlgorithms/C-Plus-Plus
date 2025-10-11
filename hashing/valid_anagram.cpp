/**
 * @file
 * @brief Implementation of [Anagram
 * Checker](https://en.wikipedia.org/wiki/Anagram) using a hash table.
 * @details
 * An anagram is a word or phrase formed by rearranging the letters of a
 * different word or phrase, typically using all the original letters exactly
 * once. This implementation is case-sensitive and considers spaces and
 * punctuation as characters.
 *
 * ### Algorithm
 * To check if two strings are anagrams, we first perform a quick check on their
 * lengths. If the lengths are different, they cannot be anagrams.
 *
 * We then use a hash table (std::unordered_map) to store the character counts
 * of the first string. We iterate through the first string, mapping each
 * character to its frequency.
 *
 * Next, we iterate through the second string. For each character, we decrement
 * its count in the hash table. If a character's count drops below zero, or if
 * the character is not found in the map, the strings are not anagrams.
 *
 * If we successfully iterate through the second string without any issues, the
 * two strings are valid anagrams.
 */

#include <cassert>       /// for assert
#include <iostream>      /// for I/O operations
#include <string>        /// for std::string
#include <unordered_map> /// for std::unordered_map (hash table)

/**
 * @namespace string_algorithms
 * @brief String manipulation algorithms
 */
namespace string_algorithms {
/**
 * @namespace anagram_checker
 * @brief Functions for checking anagrams
 */
namespace anagram_checker {

/**
 * @brief Checks if two strings are valid anagrams of each other.
 * @param[in] s1 first string to compare.
 * @param[in] s2 second string to compare.
 * @return `true` if the strings are anagrams.
 * @return `false` if the strings are not anagrams.
 */
bool are_anagrams(const std::string& s1, const std::string& s2) {
    // Anagrams must have the same length.
    if (s1.length() != s2.length()) {
        return false;
    }

    // Use a hash map to store character frequencies.
    std::unordered_map<char, int> counts;

    // Count characters in the first string.
    for (char c : s1) {
        counts[c]++;
    }

    // Decrement counts using characters from the second string.
    for (char c : s2) {
        // If a char is not found or its count is already zero, they're not
        // anagrams.
        if (counts.find(c) == counts.end() || counts[c] == 0) {
            return false;
        }
        counts[c]--;
    }

    // If we get here, the strings are anagrams.
    return true;
}

}  // namespace anagram_checker
}  // namespace string_algorithms

/**
 * @brief Self-test implementations for the anagram checker.
 * @returns void
 */
static void test() {
    // Test case 1: Basic valid anagrams
    assert(string_algorithms::anagram_checker::are_anagrams("listen", "silent"));
    assert(string_algorithms::anagram_checker::are_anagrams("triangle",
                                                             "integral"));

    // Test case 2: Valid anagrams with spaces
    assert(string_algorithms::anagram_checker::are_anagrams("a gentleman",
                                                             "elegant man"));

    // Test case 3: Invalid anagrams (different characters)
    assert(!string_algorithms::anagram_checker::are_anagrams("hello", "world"));

    // Test case 4: Invalid anagrams (different lengths)
    assert(!string_algorithms::anagram_checker::are_anagrams("apple", "apples"));

    // Test case 5: Invalid anagrams (different character counts)
    assert(!string_algorithms::anagram_checker::are_anagrams("aabbc", "aaabc"));

    // Test case 6: Case-sensitive check (should be false)
    assert(!string_algorithms::anagram_checker::are_anagrams("Listen", "silent"));

    // Test case 7: Empty strings (should be true)
    assert(string_algorithms::anagram_checker::are_anagrams("", ""));

    // Test case 8: Strings with numbers and symbols
    assert(string_algorithms::anagram_checker::are_anagrams("123!!", "!1!23"));

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
