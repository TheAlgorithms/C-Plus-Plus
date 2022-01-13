/**
 * @file
 * @brief Greedy algorithm to find length of longest substring without repeating
 * characters
 *
 * @details
 * We are given a string. We need to compute the length of the longest
 * substring, such that no character in the substring occurs more than once.
 *
 * For a string of length n, the time complexity of this algorithm is O(n)
 * (amortized)
 *
 * @author [Nishant Mahesh](https://github.com/nishant-mahesh)
 */

#include <algorithm>  // To use the inbuilt 'max' function
#include <cassert>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/**
 * This function takes a string as input, and returns the length of the longest
 * substring that contains no repeated characters
 */

int solver(string input) {
    map<char, int> prev_occurence;  // a map that keeps track of the position a
                                    // given character's previous occurence in
                                    // the current substring

    for (auto character : input) {       // initialising prev_occurence of all
                                         // characters in the string
        prev_occurence[character] = -1;  // to an arbitrary default value (-1)
    }

    prev_occurence[input[0]] = 0;

    int cur_len =
        1;  // keeps track of length of the current substring in consideration
    int ans = 1;  // the final answer i.e, length of longest susbtring w/o
                  // repeating chars

    // we start scanning from the second character of the input till the end of
    // the string
    for (int i = 1; i < input.length(); i++) {
        if (prev_occurence[input[i]] >=
            i - cur_len) {  // if the current character has already occured in
                            // the substring we're currently considering

            ans = max(ans, cur_len);  // update the final answer if necessary
            cur_len =
                i - prev_occurence[input[i]];  // the new substring we consider
                                               // spans from the character after
                                               // the previous occurence of the
                                               // now repeated character, till
                                               // the i^th character

            prev_occurence[input[i]] = i;  // update the map
        } else {                           // no repetitions encoutnered
            cur_len += 1;
            prev_occurence[input[i]] = i;  // update the prev_occrence map
        }
    }
    ans = max(ans, cur_len);  // update answer one last time
    return ans;
}

void tests() {
    pair<string, int> testcases[5];

    testcases[0] = {"abccdefgh", 6};
    testcases[1] = {"aaaaaaaaaaab", 2};
    testcases[2] = {"this_is_a_test", 5};
    testcases[3] = {"anothertest", 7};
    testcases[4] = {"this_is_a_test_string", 7};

    cout << "********************** Running Hardcoded TestCases "
            "**********************\n\n";
    for (int i = 1; i <= 5; i++) {
        cout << i << ". ";
        cout.width(21);
        cout << testcases[i - 1].first << " --- ";
        int our_answer = solver(testcases[i - 1].first);
        string result;
        if (our_answer == testcases[i - 1].second) {
            result = "(SUCCESS)";
        } else {
            result = "(FAILED)";
        }

        cout << "Our Answer: " << our_answer
             << " | Actual Answer: " << testcases[i - 1].second << "..."
             << result << '\n';

        if (result == "(FAILED)")
            exit(0);
    }
    cout << "\n********************** Hardcoded TestCases Passed "
            "**********************\n";
}

int main() { tests(); }