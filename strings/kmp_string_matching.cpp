/**
 * @file kmp_string_matching.cpp
 * @brief Implementation of the Knuth-Morris-Pratt (KMP) string matching algorithm
 *
 * @details
 * The KMP algorithm improves the naive string matching method by avoiding unnecessary rechecking of characters.
 * It uses a precomputed Longest Prefix Suffix (LPS) array to efficiently search for a pattern in a given text.
 *
 * Time Complexity: O(n + m), where n = length of text, m = length of pattern.
 * Space Complexity: O(m), for the LPS array.
 *
 * @author YashAstro11
 * @date 2025-04-13
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int> computeLPS(const string& pattern) {
    int n = pattern.length();
    vector<int> lps(n, 0);
    int len = 0;

    for (int i = 1; i < n; ) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

void KMPSearch(const string& text, const string& pattern) {
    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;
    int n = text.length(), m = pattern.length();

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++, j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            j = (j != 0) ? lps[j - 1] : 0;
        }
    }
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";
    KMPSearch(text, pattern);
    return 0;
}
