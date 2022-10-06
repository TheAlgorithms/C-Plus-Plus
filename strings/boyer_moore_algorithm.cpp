/**
 * \file
 * \brief The [Boyer-Moore-Algorithm]
 * (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
 * for finding a pattern within a piece of text with complexity O(n / m)
 *
 * 1. Boyer Moore is a combination of the following two approaches.
 *     -> Bad Character Heuristic
 *     -> Good Suffix Heuristic
 * Both of the above heuristics can also be used independently to search a
 * pattern in a text.
 * 2. The idea of bad character heuristic is simple. The character of the text 
 * which doesn’t match with the current character of the pattern is called the Bad 
 * Character. Upon mismatch, we shift the pattern until – 
 *     -> he mismatch becomes a match 
 *     -> Pattern P moves past the mismatched character.
 */

#include <iostream>
#ifdef _MSC_VER
#include <string>  /// use this for MS Visual C++
#else
#include <cstring>
#endif
using namespace std;

constexpr int BAD 256;


/**
 * Filling Bad Char Heuristic
 * \param[in] badChar array 
 * \param[in] m size of pattern string
 * \param[in] pat string pattern to search
 * void function fill badChar array
 */

void fillBadChar(int badChar[], int m, string pat) {
    // First fill it with -1
    for (int i = 0; i < BAD; i++) badChar[i] = -1;

    // Fix the reuqired values
    for (int i = 0; i < m; i++) badChar[(int)pat[i]] = i;
}

/**
 * @brief Boyer Moore algorithm to find a pattern in a text.
 * It will print where the pattern has been found.
 * \param[in] text text in which to search
 * \param[in] pattern string pattern to search
 * @returns void
 */

void boyer_moore(string txt, string pat) {
    int n = txt.length();  
    int m = pat.length();  

    int badChar[BAD];
   
    fillBadChar(badChar, m, pat);

    int s = 0;  

    while (s <= (n - m)) {
        int j = m - 1;  

        while (j >= 0 && pat[j] == txt[s + j])  
            j--;

        if (j < 0) {  // If all char are matched then j is less than 0
            cout << "Pattern found at " << s << endl;  

            /* Shift the pattern so that the next character in text aligns
            with the last occurrence of it in pattern. The condition s+m < n
            is necessary for the case when pattern occurs at the end of text */
            s += (s + m < n) ? m - badChar[txt[s + m]] : 1;
        } else
            /* Shift the pattern so that the bad character in text aligns with
            the last occurrence of it in pattern. The max function is used to
            make sure that we get a positive shift. We may get a negative shift
            if the last occurrence of bad character in pattern is on the right
            side of the current character. */
            s += max(1, j - badChar[txt[s + j]]);
    }
}

/* Main Function */
int main() {
    string txt = "AABAACAADAABAABA";
    string pat = "AABA";

    boyer_moore(txt, pat);

    /* Output
    * Pattern found at 0
    * Pattern found at 9
    * Pattern found at 12
    */

    /* Sample Test Case
    * string txt = "ABAAABCD";
    * string pat = "ABC";
    * boyer_moore(txt, pat);
    * // output -> Pattern found at 4
    */

    return 0;
}