/**
 * @file
 * @brief Implements [Palindrome
 * Partitioning](https://leetcode.com/problems/palindrome-partitioning-ii/)
 * algorithm, giving you the minimum number of partitions you need to make
 *
 * @details
 * palindrome partitioning uses dynamic programming and goes to all the possible
 * partitions to find the minimum you are given a string and you need to give
 * minimum number of partitions needed to divide it into a number of palindromes
 * [Palindrome Partitioning]
 * (https://www.geeksforgeeks.org/palindrome-partitioning-dp-17/) overall time
 * complexity O(n^2) For example: example 1:- String : "nitik" Output : 2 => "n
 * | iti | k" For example: example 2:- String : "ababbbabbababa" Output : 3 =>
 * "aba | b | bbabb | ababa"
 * @author [Sujay Kaushik] (https://github.com/sujaykaushik008)
 */

#include <algorithm>  // for std::min
#include <cassert>    // for std::assert
#include <climits>    // for INT_MAX
#include <iostream>   // for io operations
#include <vector>     // for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace palindrome_partitioning
 * @brief Functions for [Palindrome
 * Partitioning](https://leetcode.com/problems/palindrome-partitioning-ii/)
 * algorithm
 */
namespace palindrome_partitioning {

/**
 * Function implementing palindrome partitioning algorithm using lookup table
 * method.
 * @param str input string
 * @returns minimum number of partitions
 */
int pal_part(const std::string &str) {
    int n = str.size();

    // creating lookup table for minimum number of cuts
    std::vector<std::vector<int> > cuts(n, std::vector<int>(n, 0));

    // creating lookup table for palindrome checking
    std::vector<std::vector<bool> > is_palindrome(n,
                                                  std::vector<bool>(n, false));

    // initialization
    for (int i = 0; i < n; i++) {
        is_palindrome[i][i] = true;
        cuts[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int start_index = 0; start_index < n - len + 1; start_index++) {
            int end_index = start_index + len - 1;

            if (len == 2) {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]);
            } else {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]) &&
                    is_palindrome[start_index + 1][end_index - 1];
            }

            if (is_palindrome[start_index][end_index]) {
                cuts[start_index][end_index] = 0;
            } else {
                cuts[start_index][end_index] = INT_MAX;
                for (int partition = start_index; partition <= end_index - 1;
                     partition++) {
                    cuts[start_index][end_index] =
                        std::min(cuts[start_index][end_index],
                                 cuts[start_index][partition] +
                                     cuts[partition + 1][end_index] + 1);
                }
            }
        }
    }

    return cuts[0][n - 1];
}
}  // namespace palindrome_partitioning
}  // namespace dynamic_programming

/**
 * @brief Test Function
 * @return void
 */
static void test() {
    // custom input vector
    std::vector<std::string> custom_input{"nitik", "ababbbabbababa", "abdc"};

    // calculated output vector by pal_part Function
    std::vector<int> calculated_output(3);

    for (int i = 0; i < 3; i++) {
        calculated_output[i] =
            dynamic_programming::palindrome_partitioning::pal_part(
                custom_input[i]);
    }

    // expected output vector
    std::vector<int> expected_output{2, 3, 3};

    // Testing implementation via assert function
    // It will throw error if any of the expected test fails
    // Else it will give nothing
    for (int i = 0; i < 3; i++) {
        assert(expected_output[i] == calculated_output[i]);
    }

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
