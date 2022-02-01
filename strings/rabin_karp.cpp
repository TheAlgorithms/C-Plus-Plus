/**
 * \file
 * \brief The [Rabin-Karp
 * Algorithm](https://en.wikipedia.org/wiki/Rabin–Karp_algorithm) for finding a
 * pattern within a piece of text with complexity O(n + m)
 */
#include <cassert>
#include <cmath>
#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visucal C++
#else
#include <cstring>
#endif

#define PRIME 5  ///< Prime modulus for hash functions

namespace string_search {
/**
 * convert a string to an intger - called as hashing function
 * \param[in] s source of string to hash
 * \param[in] n length of substring to hash
 * \returns hash integer
 */
int64_t create_hash(const std::string& s, size_t n) {
    int64_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += (int64_t)(s[i] * (int64_t)pow(PRIME, i));
    }
    return result;
}

/**
 * re-hash a string using known existing hash
 * \param[in] s source of string to hash
 * \param[in] previous_index previous index of string
 * \param[in] previous_hased_value previous hash of substring
 * \param[in] pattern_length length of substring to hash
 * \returns new hash integer
 */
int64_t recalculate_hash(const std::string& s, size_t previous_index,
                         int64_t previous_hased_value, size_t pattern_length) {
    auto current_index = previous_index + pattern_length;

    int64_t new_hash = previous_hased_value - s[previous_index];
    new_hash /= PRIME;
    new_hash +=
        (int64_t)(s[current_index] * (int64_t)pow(PRIME, pattern_length - 1));

    return new_hash;
}

/**
 * compare if two sub-strings are equal
 * \param[in] pattern string pattern to search
 * \param[in] text string in which to search
 * \param[in] index starting index for pattern
 * \returns `true` if pattern was found, false otherwise
 * @note can this be replaced by std::string::compare?
 */
bool check_if_equal(const std::string& pattern, const std::string& text,
                    size_t index) {
    auto distance = text.size() - 1;
    return pattern.substr(index, distance) == text.substr(0, distance);
}

/**
 *  Perform string pattern search using Rabin-Karp algorithm
 *  @param[in] text string to search in
 *  @param[in] pattern string to search for
 *  @return index of first occurrence of pattern, -1 otherwise
 */
int rabin_karp(const std::string& text, const std::string& pattern) {
    auto pattern_size = pattern.size();
    auto string_variance = text.size() - pattern_size;

    int64_t hashed_pattern = create_hash(pattern, pattern_size);
    int64_t hashed_text = create_hash(text, pattern_size);

    for (size_t i = 0; i <= string_variance; ++i) {
        if (hashed_pattern == hashed_text && check_if_equal(text, pattern, i)) {
            return i;
        }
        if (i < string_variance) {
            hashed_text = recalculate_hash(text, i, hashed_text, pattern_size);
        }
    }
    return -1;  // return -1 if given pattern not found
}

}  // namespace string_search

using string_search::rabin_karp;

/** Main function */
int main(void) {
    assert(rabin_karp("helloWorld", "world") == -1);
    assert(rabin_karp("helloWorld", "World") == 5);
    assert(rabin_karp("this_is_c++", "c++") == 8);
    assert(rabin_karp("happy_coding", "happy") == 0);
    return 0;
}
