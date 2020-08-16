/**
 * @file
 * @brief SCS is a string Z which is the shortest supersequence of strings X and Y (may not be continuous in Z, but order is maintained).
 * @details
 * Details for [Shortest Common Supersequence](https://en.wikipedia.org/wiki/Shortest_common_supersequence_problem)
 * 
 * The idea is to use lookup table method as used in LCS.
 * For example: example 1:-
 * X: 'ABCXYZ', Y: 'ABZ' then Z will be 'ABCXYZ' (y is not continuous but in order)
 * 
 * For example: example 2:-
 * X: 'AGGTAB', Y: 'GXTXAYB' then Z will be 'AGGXTXAYB'
 * @author [Ridhish Jain](https://github.com/ridhishjain)
 * @see related problem [Leetcode](https://leetcode.com/problems/shortest-common-supersequence/)
*/

// header files
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
*/
namespace dynamic_programming {

    /**
    * @namespace shortest_common_supersequence
    * @brief Shortest Common Super Sequence algorithm
    */
    namespace shortest_common_supersequence {
        
        /**
         * Function scs
         * @param string first string 'X'
         * @param string second string 'Y'
         * @param int length of first string
         * @param int length of second string
         * @return string superSequence of X and Y 
        */
        std::string scs(std::string str1, std::string str2, int n1, int n2) {

            // Edge cases
            // If either n1 or n2 or both are zeroes
            if(n1 == 0 && n2 == 0) {
                return "";
            }
            else if(n1 == 0) {
                return str2;
            }
            else if(n2 == 0) {
                return str1;
            }

            // creating lookup table
            std::vector <std::vector <int>> lookup(n1 + 1, std::vector <int> (n2 + 1, 0));
      
            for(int i=1; i <= n1; i++) {
                for(int j=1; j <= n2; j++) {
                    if(str1[i-1] == str2[j-1]) {
                        lookup[i][j] = lookup[i-1][j-1] + 1;
                    }
                    else {
                        lookup[i][j] = std::max(lookup[i-1][j], lookup[i][j-1]);
                    }
                }
            }

            // making supersequence
            // i and j are initially pointed towards end of strings
            // Super-sequence will be constructed backwards
            int i=n1;
            int j=n2;
            std::string s;
      
            while(i>0 && j>0) {

                // If the characters at i and j of both strings are same
                // We only need to add them once in s
                if(str1[i-1] == str2[j-1]) {
                    s.push_back(str1[i-1]);
                    i--;
                    j--;
                }
                // otherwise we check lookup table for recurrences of characters
                else {
                    if(lookup[i-1][j] > lookup[i][j-1]) {
                        s.push_back(str1[i-1]);
                        i--;
                    }
                    else {
                        s.push_back(str2[j-1]);
                        j--;
                    }
                }
            }

            // copying remaining elements
            // if j becomes 0 before i
            while(i > 0) {
                s.push_back(str1[i-1]);
                i--;
            }

            // if i becomes 0 before j
            while(j > 0) {
                s.push_back(str2[j-1]);
                j--;
            }

            // As the super sequence is constructd backwards
            // reversing the string before returning gives us the correct output  
            reverse(s.begin(), s.end());
            return s;
        }
    } // namespace shortest_common_supersequence
} // namespace dynamic_programming

/** 
 * Test Function
 * @return void 
*/
static void test() {

    // custom input vector
    std::vector <std::vector <std::string>> scsStrings {
        {"ABCXYZ", "ABZ"},
        {"ABZ", "ABCXYZ"},
        {"AGGTAB", "GXTXAYB"},
        {"X", "Y"},
    };

    // calculated output vector by scs function
    std::vector <std::string> calculatedOutput;
    for(auto & scsString : scsStrings) {
        int n1 = scsString[0].length();
        int n2 = scsString[1].length();
        
        calculatedOutput.push_back(dynamic_programming::shortest_common_supersequence::scs(
            scsString[0], scsString[1], n1, n2
        ));
    }

    // expected output vector acc to problem statement
    std::vector <std::string> expectedOutput {
        "ABCXYZ",
        "ABCXYZ",
        "AGGXTXAYB",
        "XY"
    };

    // Testing implementation via assert function
    // It will throw error if any of the expected test fails
    // Else it will give nothing
    for(int i=0; i < scsStrings.size(); i++) {
        assert(expectedOutput[i] == calculatedOutput[i]);
    }

    std::cout << "All tests passed successfully!\n";
    return;
}

/** Main function (driver code)*/
int main() {

    // test for implementation
    std::cout << "\nTesting implementation\n";
    test();

    // user input
    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;

    int n1 = s1.length();
    int n2 = s2.length();
    std::string ans;

    // user output
    ans = dynamic_programming::shortest_common_supersequence::scs(s1, s2, n1, n2);
    std::cout << ans;
    return 0;
}
