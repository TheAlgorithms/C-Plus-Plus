/**
 * @file
 * @brief Implementation of the [Wildcard
 * Matching](https://www.geeksforgeeks.org/wildcard-pattern-matching/) problem.
 * @details
 * Given a matching string and a pattern, implement wildcard pattern
 * matching with support for `?` and `*`. `?` matches any single character.
 * `*` matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire matching string (not partial). The task
 * is to determine if the pattern matches with the matching string
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace wildcard_matching
 * @brief Functions for the [Wildcard
 * Matching](https://www.geeksforgeeks.org/wildcard-pattern-matching/) problem.
 */
namespace wildcard_matching {
/**
 * @brief The main function implements if pattern can be matched with given
 * string
 * @param s is the given matching string
 * @param p is the given pattern
 * @param pos1 is the starting index
 * @param pos2 is the last index
 * @returns 1 if pattern matches with matching string otherwise 0
 */
std::vector<std::vector<int64_t>> dpTable(1000, std::vector<int64_t>(1000, -1));
bool wildcard_matching(std::string s, std::string p, uint32_t pos1,
                       uint32_t pos2) {
    uint32_t n = s.length();
    uint32_t m = p.length();
    // matching is successfull if both strings are done
    if (pos1 == n && pos2 == m) {
        return true;
    }

    // matching is unsuccessfull if pattern is not finished but matching string
    // is
    if (pos1 != n && pos2 == m) {
        return false;
    }

    // all the remaining characters of patterns must be * inorder to match with
    // finished string
    if (pos1 == n && pos2 != m) {
        while (pos2 < m && p[pos2] == '*') {
            pos2++;
        }

        return pos2 == m;
    }

    // if already calculted for these positions
    if (dpTable[pos1][pos2] != -1) {
        return dpTable[pos1][pos2];
    }

    // if the characters are same just go ahead in both the string
    if (s[pos1] == p[pos2]) {
        return dpTable[pos1][pos2] =
                   wildcard_matching(s, p, pos1 + 1, pos2 + 1);
    }

    else {
        // can only single character
        if (p[pos2] == '?') {
            return dpTable[pos1][pos2] =
                       wildcard_matching(s, p, pos1 + 1, pos2 + 1);
        }
        // have choice either to match one or more charcters
        else if (p[pos2] == '*') {
            return dpTable[pos1][pos2] =
                       wildcard_matching(s, p, pos1, pos2 + 1) ||
                       wildcard_matching(s, p, pos1 + 1, pos2);
        }
        // not possible to match
        else {
            return dpTable[pos1][pos2] = 0;
        }
    }
}

}  // namespace wildcard_matching
}  // namespace backtracking

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::cout << "1st test ";
    std::string matching1 = "baaabab";
    std::string pattern1 = "*****ba*****ab";
    assert(backtracking::wildcard_matching::wildcard_matching(matching1,
                                                              pattern1, 0, 0) ==
           1);  // here the pattern matches with given string
    std::cout << "passed" << std::endl;

    // 2nd test
    std::cout << "2nd test ";
    std::string matching2 = "baaabab";
    std::string pattern2 = "ba*****ab";
    assert(backtracking::wildcard_matching::wildcard_matching(matching2,
                                                              pattern2, 0, 0) ==
           1);  // here the pattern matches with given string
    std::cout << "passed" << std::endl;

    // 3rd test
    std::cout << "3rd test ";
    std::string matching3 = "baaabab";
    std::string pattern3 = "ba*ab";
    assert(backtracking::wildcard_matching::wildcard_matching(matching3,
                                                              pattern3, 0, 0) ==
           1);  // here the pattern matches with given string
    std::cout << "passed" << std::endl;

    // 4th test
    std::cout << "4th test ";
    std::string matching4 = "baaabab";
    std::string pattern4 = "a*ab";
    assert(backtracking::wildcard_matching::wildcard_matching(matching4,
                                                              pattern4, 0, 0) ==
           1);  // here the pattern matches with given string
    std::cout << "passed" << std::endl;

    // 5th test
    std::cout << "5th test ";
    std::string matching5 = "baaabab";
    std::string pattern5 = "aa?ab";
    assert(backtracking::wildcard_matching::wildcard_matching(matching5,
                                                              pattern5, 0, 0) ==
           1);  // here the pattern matches with given string
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
