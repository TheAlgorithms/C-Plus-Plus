/* Given two strings str1 & str2
 * and below operations that can
 * be performed on str1. Find
 * minimum number of edits
 * (operations) required to convert
 * 'str1' into 'str2'/
 * a. Insert
 * b. Remove
 * c. Replace
 * All of the above operations are
 * of equal cost
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert> // Required for automated testing
using namespace std;

namespace dynamic_programming {
    int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

    /* A Naive recursive C++ program to find
    * minimum number of operations to convert
    * str1 to str2.
    * O(3^m)
    */

    /**
    * @brief Recursive implementation to find edit distance
    * @param str1 first string
    * @param str2 second string
    * @param m length of first string
    * @param n length of second string
    * @returns minimum number of edits
    */
    int editDist(string str1, string str2, int m, int n) {
        if (m == 0)
            return n;
        if (n == 0)
            return m;

        // If last characters are same then continue
        // for the rest of them.
        if (str1[m - 1] == str2[n - 1])
            return editDist(str1, str2, m - 1, n - 1);

        // If last not same, then 3 possibilities
        // a.Insert b.Remove c. Replace
        // Get min of three and continue for rest.
        return 1 + min(editDist(str1, str2, m, n - 1),
                    editDist(str1, str2, m - 1, n),
                    editDist(str1, str2, m - 1, n - 1));
    }

    /* A DP based program
    * O(m x n)
    */
    int editDistDP(string str1, string str2, int m, int n) {
        // Create Table for SubProblems
        std::vector<std::vector<int> > dp(m + 1, std::vector<int>(n + 1));

        // Fill d[][] in bottom up manner
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // If str1 empty. Then add all of str2
                if (i == 0)
                    dp[i][j] = j;

                // If str2 empty. Then add all of str1
                else if (j == 0)
                    dp[i][j] = i;

                // If character same. Recur for remaining
                else if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];

                else
                    dp[i][j] = 1 + min(dp[i][j - 1],     // Insert
                                    dp[i - 1][j],     // Remove
                                    dp[i - 1][j - 1]  // Replace
                                );
            }
        }

        return dp[m][n];
    }

/**
     * @brief Test function for edit distance with multiple test cases
     */
    void testEditDistance() {
        // Test case 1: Identical strings
        assert(editDistDP("hello", "hello", 5, 5) == 0);
        // Test case 2: Empty strings
        assert(editDistDP("", "", 0, 0) == 0);
        // Test case 3: One empty string
        assert(editDistDP("abc", "", 3, 0) == 3);
        assert(editDistDP("", "xyz", 0, 3) == 3);
        // Test case 4: Simple replacement
        assert(editDistDP("cat", "bat", 3, 3) == 1);
        // Test case 5: Simple insertion
        assert(editDistDP("cat", "cart", 3, 4) == 1);
        // Test case 6: Simple deletion
        assert(editDistDP("cart", "cat", 4, 3) == 1);
        // Test case 7: Multiple operations
        assert(editDistDP("sunday", "saturday", 6, 8) == 3);
        // Test case 8: Different lengths
        assert(editDistDP("kitten", "sitting", 6, 7) == 3);
        // Test case 9: Case sensitivity
        assert(editDistDP("Hello", "hello", 5, 5) == 1);
        // Test case 10: Longer strings
        assert(editDistDP("intention", "execution", 9, 9) == 5);

        std::cout << "All extended test cases passed!" << std::endl;
    }
} // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::string str1 = "sunday";
    std::string str2 = "saturday";
    
    // Test the recursive approach
    assert(dynamic_programming::editDist(str1, str2, str1.length(), str2.length()) == 3);
    
    // Test the Dynamic Programming approach
    assert(dynamic_programming::editDistDP(str1, str2, str1.length(), str2.length()) == 3);

    // Call your new extended test suite
    dynamic_programming::testEditDistance();

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}