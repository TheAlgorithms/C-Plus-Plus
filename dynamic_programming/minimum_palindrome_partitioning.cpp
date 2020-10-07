/**
 * @file
 * @brief Program to find the Minimum Palindrome
 * Partitioning of a string
 *
 * @details
 * [Palindrome](https://en.wikipedia.org/wiki/Palindrome) string is sequence
 * of characters which reads the same backward as forward
 * [Substring](https://en.wikipedia.org/wiki/Substring) is a contiguous sequence
 * of characters within a string
 * Partitioning of a string is palindrome partitioning if every substring
 * of the partition is a palindrome.
 * This code will calculate the minimum number of partitions in a string
 * such that all substrings are palindrome.

 * @author [Anjali Jha](https://github.com/anjali1903)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace mpp
 * @brief Minimum palindrome partition algorithm
 */ 
namespace mpp {

/**
 * Function that returns the minimum palindrome
 * partitioning of a string
 */
int mpp(std::string s) {  // mpp: minimum palindrome partitioning
    int n = s.length();
    std::vector<std::vector<bool> > palin(
        n);  // stores whether a particular substring
             // is palindromic or not
    std::vector<int> cuts(
        n);  // stores minimum number of cuts in bootom-up manner
    int i, j, L;

    // every substring of length=1 is a palindrome
    for (i = 0; i < n; i++) {
        palin[i][i] = true;
    }

    // for every substring of length >= 2 till n is checked
    for (L = 2; L <= n; L++) {
        // different substring of length = L are checked
        // i is the starting index of the substring
        for (i = 0; i < n - L + 1; i++) {
            // j is the end index of the substring
            j = i + L - 1;
            if (L ==
                2) {  // if L=2, both characters must be same to be palindrome
                palin[i][j] = s[i] == s[j];
            }
            // if L>2, check the first and last characters and palin[i+1][j-1]
            else {
                palin[i][j] = (s[i] == s[j] && palin[i + 1][j - 1]);
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (palin[0][i]) {
            cuts[i] = 0;
        } else {
            cuts[i] = 2147483647;
            for (j = 0; j < i; j++) {
                if (palin[j + 1][i]) {
                    cuts[i] = std::min(cuts[i], cuts[j] + 1);
                }
            }
        }
    }
    return cuts[n - 1];
}

/** Test function */
void test() {
    // mpp("banana") return 1
    assert(mpp("banana") == 1);
    // mpp("abbcbaa") return 3
    assert(mpp("abbcbaa") == 3);
    // mpp("radar") return 0
    assert(mpp("radar") == 0);
}

/**
 * Main Function
 */
int main() {
    test();  // execute the tests
    return 0;
}
