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
int64_t create_hash(const std::string& s, int n) {
    int64_t result = 0;
    for (int i = 0; i < n; ++i) {
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
int64_t recalculate_hash(const std::string& s, int old_index, int new_index,
                         int64_t old_hash, int patLength) {
    int64_t new_hash = old_hash - s[old_index];
    new_hash /= PRIME;
    new_hash += (int64_t)(s[new_index] * (int64_t)pow(PRIME, patLength - 1));
    return new_hash;
}

/**
 * compare if two sub-strings are equal
 * \param[in] str1 string pattern to search
 * \param[in] str2 text in which to search
 * \param[in] start1,end1 start and end indices for substring in str1
 * \param[in] start2,end2 start and end indices for substring in str2
 * \returns `true` if pattern was found
 * \returns `false` if pattern was not found
 * @note can this be replaced by std::string::compare?
 */
bool check_if_equal(const std::string& str1, const std::string& str2,
                    int start1, int end1, int start2, int end2) {
    if (end1 - start1 != end2 - start2) {
        return false;
    }
    while (start1 <= end1 && start2 <= end2) {
        if (str1[start1] != str2[start2]) {
            return false;
        }
        start1++;
        start2++;
    }
    return true;
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
        if (pat_hash == str_hash &&
            check_if_equal(str, pat, i, i + pat.size() - 1, 0,
                           pat.size() - 1)) {
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
