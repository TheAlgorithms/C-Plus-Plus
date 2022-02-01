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
 * \param[in] old_index previous index of string
 * \param[in] new_index new index of string
 * \param[in] old_hash previous hash of substring
 * \param[in] patLength length of substring to hash
 * \returns new hash integer
 */
int64_t recalculate_hash(const std::string& s, size_t old_index,
                         size_t new_index, int64_t old_hash, size_t patLength) {
    int64_t new_hash = old_hash - s[old_index];
    new_hash /= PRIME;
    new_hash += (int64_t)(s[new_index] * (int64_t)pow(PRIME, patLength - 1));
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
 *  @param[in] str string to search in
 *  @param[in] pat pattern to search for
 *  @return index of first occurrence of pattern
 *  @return -1 if pattern not found
 */

int rabin_karp(const std::string& str, const std::string& pat) {
    int64_t pat_hash = create_hash(pat, pat.size());
    int64_t str_hash = create_hash(str, pat.size());
    for (int i = 0; i <= str.size() - pat.size(); ++i) {
        if (pat_hash == str_hash && check_if_equal(str, pat, i)) {
            return i;
        }
        if (i < str.size() - pat.size()) {
            str_hash =
                recalculate_hash(str, i, i + pat.size(), str_hash, pat.size());
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
