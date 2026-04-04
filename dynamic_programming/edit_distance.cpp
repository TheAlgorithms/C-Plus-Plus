/**
 * @file
 * @brief [Edit Distance](https://en.wikipedia.org/wiki/Edit_distance) algorithm implementation.
 * @author [Rahul Paul](https://github.com/rahulpaul-07)
 */

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
#include <stdexcept>
#include <algorithm>

namespace dynamic_programming {


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
    int editDist(const std::string& str1, const std::string& str2, int m, int n) {
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
        return 1 + std::min({editDist(str1, str2, m, n - 1),
                             editDist(str1, str2, m - 1, n),
                             editDist(str1, str2, m - 1, n - 1)});
    }

    /**
    * @brief Space-optimized edit distance (O(n) space)
    * @param str1 first string
    * @param str2 second string
    * @returns minimum number of edits
    * @throws std::invalid_argument if input is too large (Security Guard)
    */
    int editDistDP(const std::string& str1, const std::string& str2) {
        size_t m = str1.length();
        size_t n = str2.length();

        // 1. Security Gate: Prevent Denial of Service (DoS) via memory exhaustion
        const size_t MAX_ALLOWED = 10000; 
        if (m > MAX_ALLOWED || n > MAX_ALLOWED) {
            throw std::invalid_argument("Input string length exceeds the safety limit of 10,000.");
        }

        // 2. Memory optimization: Ensure 'n' is the smaller length
        if (m < n) return editDistDP(str2, str1);

        // 3. O(n) Space: Only two rows needed
        std::vector<int> prev(n + 1);
        std::vector<int> curr(n + 1);

        // Initialize base cases for the first row (empty str1)
        for (size_t j = 0; j <= n; j++) prev[j] = static_cast<int>(j);

        for (size_t i = 1; i <= m; i++) {
            curr[0] = static_cast<int>(i); // Base case for the first column (empty str2)
            for (size_t j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    curr[j] = prev[j - 1]; // Characters match, no edit needed
                } else {
                    // Min of Insert (curr[j-1]), Remove (prev[j]), Replace (prev[j-1])
                    curr[j] = 1 + std::min({curr[j - 1], prev[j], prev[j - 1]});
                }
            }
            prev = curr; // Move current row to previous for next iteration
        }

        return prev[n];
    }

/**
     * @brief Test function for edit distance with multiple test cases
     */
    void testEditDistance() {
        // Test case 1: Identical strings
        assert(editDistDP("hello", "hello") == 0);
        // Test case 2: Empty strings
        assert(editDistDP("", "") == 0);
        // Test case 3: One empty string
        assert(editDistDP("abc", "") == 3);
        assert(editDistDP("", "xyz") == 3);
        // Test case 4: Simple replacement
        assert(editDistDP("cat", "bat") == 1);
        // Test case 5: Simple insertion
        assert(editDistDP("cat", "cart") == 1);
        // Test case 6: Simple deletion
        assert(editDistDP("cart", "cat") == 1);
        // Test case 7: Multiple operations
        assert(editDistDP("sunday", "saturday") == 3);
        // Test case 8: Different lengths
        assert(editDistDP("kitten", "sitting") == 3);
        // Test case 9: Case sensitivity
        assert(editDistDP("Hello", "hello") == 1);
        // Test case 10: Longer strings
        assert(editDistDP("intention", "execution") == 5);
        // Test 11: Security Gate Test
        try {
            std::string big(10001, 'a');
            editDistDP(big, "test");
            assert(false); // Should not reach here
        } catch (const std::invalid_argument& e) {
            std::cout << "Security Test Passed: Correctly blocked oversized input." << std::endl;
        }
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
    assert(dynamic_programming::editDistDP(str1, str2) == 3);

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