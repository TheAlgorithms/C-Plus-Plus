/**
 * @file
 * @brief
 * The
 * [Boyer–Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
 * algorithm searches for occurrences of pattern P in text T by performing
 * explicit character comparisons at different alignments. Instead of a
 * brute-force search of all alignments (of which there are n - m + 1),
 * Boyer–Moore uses information gained by preprocessing P to skip as many
 * alignments as possible.
 *
 * @details
 * The key insight in this algorithm is that if the end of the pattern is
 * compared to the text, then jumps along the text can be made rather than
 * checking every character of the text. The reason that this works is that in
 * lining up the pattern against the text, the last character of the pattern is
 * compared to the character in the text.
 *
 * If the characters do not match, there is no need to continue searching
 * backwards along the text. This leaves us with two cases.
 *
 * Case 1:
 * If the character in the text does not match any of the characters in the
 * pattern, then the next character in the text to check is located m characters
 * farther along the text, where m is the length of the pattern.
 *
 * Case 2:
 * If the character in the text is in the pattern, then a partial shift of the
 * pattern along the text is done to line up along the matching character and
 * the process is repeated.
 *
 * There are two shift rules:
 *
 * [The bad character rule]
 * (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm#The_bad_character_rule)
 *
 * [The good suffix rule]
 * (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm#The_good_suffix_rule)
 *
 * The shift rules are implemented as constant-time table lookups, using tables
 * generated during the preprocessing of P.
 * @author [Stoycho Kyosev](https://github.com/stoychoX)
 */

#include <cassert>   /// for assert
#include <climits>   /// for CHAR_MAX macro
#include <cstring>   /// for strlen
#include <iostream>  /// for IO operations
#include <string>    /// for std::string
#include <vector>    /// for std::vector

#define APLHABET_SIZE CHAR_MAX  ///< number of symbols in the alphabet we use

/**
 * @namespace
 * @brief String algorithms
 */
namespace strings {
/**
 * @namespace
 * @brief Functions for the [Boyer
 * Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
 * algorithm implementation
 */
namespace boyer_moore {
/**
 * @brief A structure representing all the data we need to search the
 * preprocessed pattern in text.
 */
struct pattern {
    std::string pat;

    std::vector<size_t>
        bad_char;  ///< bad char table used in [Bad Character
                   ///< Heuristic](https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/)

    std::vector<size_t>
        good_suffix;  ///< good suffix table used for [Good Suffix
                      ///< heuristic](https://www.geeksforgeeks.org/boyer-moore-algorithm-good-suffix-heuristic/?ref=rp)
};

/**
 * @brief A function that preprocess the good suffix thable
 *
 * @param str The string being preprocessed
 * @param arg The good suffix table
 * @returns void
 */
void init_good_suffix(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(str.size() + 1, 0);

    // border_pos[i] - the index of the longest proper suffix of str[i..] which
    // is also a proper prefix.
    std::vector<size_t> border_pos(str.size() + 1, 0);

    size_t current_char = str.length();

    size_t border_index = str.length() + 1;

    border_pos[current_char] = border_index;

    while (current_char > 0) {
        while (border_index <= str.length() &&
               str[current_char - 1] != str[border_index - 1]) {
            if (arg[border_index] == 0) {
                arg[border_index] = border_index - current_char;
            }

            border_index = border_pos[border_index];
        }

        current_char--;
        border_index--;
        border_pos[current_char] = border_index;
    }

    size_t largest_border_index = border_pos[0];

    for (size_t i = 0; i < str.size(); i++) {
        if (arg[i] == 0) {
            arg[i] = largest_border_index;
        }

        // If we go pass the largest border we find the next one as we iterate
        if (i == largest_border_index) {
            largest_border_index = border_pos[largest_border_index];
        }
    }
}

/**
 * @brief A function that preprocess the bad char table
 *
 * @param str The string being preprocessed
 * @param arg The bad char table
 * @returns void
 */
void init_bad_char(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(APLHABET_SIZE, str.length());

    for (size_t i = 0; i < str.length(); i++) {
        arg[str[i]] = str.length() - i - 1;
    }
}

/**
 * @brief A function that initializes pattern
 *
 * @param str Text used for initialization
 * @param arg Initialized structure
 * @returns void
 */
void init_pattern(const std::string& str, pattern& arg) {
    arg.pat = str;
    init_bad_char(str, arg.bad_char);
    init_good_suffix(str, arg.good_suffix);
}
/**
 * @brief A function that implements Boyer-Moore's algorithm.
 *
 * @param str Text we are seatching in.
 * @param arg pattern structure containing the preprocessed pattern
 * @return Vector of indexes of the occurrences of pattern in text
 */
std::vector<size_t> search(const std::string& str, const pattern& arg) {
    size_t index_position = arg.pat.size() - 1;
    std::vector<size_t> index_storage;

    while (index_position < str.length()) {
        size_t index_string = index_position;
        int index_pattern = static_cast<int>(arg.pat.size()) - 1;

        while (index_pattern >= 0 &&
               str[index_string] == arg.pat[index_pattern]) {
            --index_pattern;
            --index_string;
        }

        if (index_pattern < 0) {
            index_storage.push_back(index_position - arg.pat.length() + 1);
            index_position += arg.good_suffix[0];
        } else {
            index_position += std::max(arg.bad_char[str[index_string]],
                                       arg.good_suffix[index_pattern + 1]);
        }
    }

    return index_storage;
}

/**
 * @brief Check if pat is prefix of str.
 *
 * @param str pointer to some part of the input text.
 * @param pat the searched pattern.
 * @param len length of the searched pattern
 * @returns `true` if pat IS prefix of str.
 * @returns `false` if pat is NOT a prefix of str.
 */
bool is_prefix(const char* str, const char* pat, size_t len) {
    if (strlen(str) < len) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != pat[i]) {
            return false;
        }
    }

    return true;
}
}  // namespace boyer_moore
}  // namespace strings
/**
 * @brief A test case in which we search for every appearance of the word 'and'
 * @param text The text in which we search for appearance of the word 'and'
 * @returns void
 */
void and_test(const char* text) {
    strings::boyer_moore::pattern ands;
    strings::boyer_moore::init_pattern("and", ands);
    std::vector<size_t> indexes = strings::boyer_moore::search(text, ands);

    assert(indexes.size() == 2);
    assert(strings::boyer_moore::is_prefix(text + indexes[0], "and", 3));
    assert(strings::boyer_moore::is_prefix(text + indexes[1], "and", 3));
}

/**
 * @brief  A test case in which we search for every appearance of the word 'pat'
 * @param text The text in which we search for appearance of the word 'pat'
 * @returns void
 */
void pat_test(const char* text) {
    strings::boyer_moore::pattern pat;
    strings::boyer_moore::init_pattern("pat", pat);
    std::vector<size_t> indexes = strings::boyer_moore::search(text, pat);

    assert(indexes.size() == 6);

    for (const auto& currentIndex : indexes) {
        assert(strings::boyer_moore::is_prefix(text + currentIndex, "pat", 3));
    }
}
/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    const char* text =
        "When pat Mr. and Mrs. pat Dursley woke up on the dull, gray  \
                            Tuesday our story starts, \
                there was nothing about pat the cloudy sky outside to pat suggest that\
                        strange and \
                    mysterious things would pat soon be happening all pat over the \
                        country.";

    and_test(text);
    pat_test(text);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
