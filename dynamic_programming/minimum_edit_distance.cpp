/**
 * @file
 * @brief Implementation of [Minimum Edit Distance](https://en.wikipedia.org/wiki/Edit_distance) using Dynamic Programing
 *
 * @details
 *
 * Given two strings str1 & str2 and we have to calculate the minimum
 * number of operations (Insert, Remove, Replace) required to convert
 * str1 to str2.
 *
 * ### Algorithm
 *
 * We will solve this problem using Naive recursion. But as we are
 * approaching with a DP solution. So, we will take a DP array to
 * store the solution of all sub-problems so that we don't have to
 * perform recursion again and again. Now to solve the problem, We
 * can traverse all characters from either right side of the strings
 * or left side. Suppose we will do it from the right side. So, there
 * are two possibilities for every pair of characters being traversed.
 * 1. If the last characters of two strings are the same, Ignore
 * the characters and get the count for the remaining string.
 * So, we get the solution for lengths m-1 and n-1 in a DP array.
 *
 * 2. Else, (If last characters are not the same), we will consider all
 * three operations (Insert, Remove, Replace) on the last character of
 * the first string and compute the minimum cost for all three operations
 * and take the minimum of three values in the DP array.
 * For Insert: Recur for m and n-1
 * For Remove: Recur for for m-1 and n
 * For Replace: Recur for for m-1 and n-1
 *
 * @author [Nirjas Jakilim](github.com/nirzak)
 */

#include <cassert>     /// for assert
#include <iostream>   /// for IO operations
#include <vector>    /// for std::vector
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */

namespace dynamic_programming {

/**
 * @namespace Minimum Edit Distance
 * @brief Implementation of [Minimum Edit Distance](https://en.wikipedia.org/wiki/Edit_distance) algorithm
 */

namespace minimum_edit_distance {

/**
function to return minimum of three operations
Insert, Replace or Delete
*/

int min(int x, int y, int z) {
  if (x <= y && x <= z) {
    return x; // returns x, if x is the minimum value
  }
  if (y <= x && y <= z) {
    return y; // returns y, if y is the minimum value
  }
  else {
    return z; // returns z if z is the minimum value
  }
}

int editDistDP(std::string str1, std::string str2, int m, int n) {
  // Create a table to store results of subproblems
  std::vector<std::vector<int>>dp(m+1, std::vector<int>(n+1));

  // Fill d[][] in bottom up manner
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      // If first string is empty, only option is to
      // insert all characters of second string
      if (i == 0) {
        dp[i][j] = j; // Min. operations = j
      }

      // If second string is empty, only option is to
      // remove all characters of second string
      else if (j == 0) {
        dp[i][j] = i; // Min. operations = i
      }

      // If last characters are same, ignore last char
      // and recur for remaining string
      else if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      }

      // If the last character is different, consider all
      // possibilities and find the minimum
      else {
        dp[i][j] = 1 + min(dp[i][j - 1],      // Insert
                           dp[i - 1][j],      // Remove
                           dp[i - 1][j - 1]); // Replace
      }
    }
  }

  return dp[m][n];
}
} // namespace minimum_edit_distance
} // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
  // test 1
  std::string str1 = "INTENTION";
  std::string str2 = "EXECUTION";
  const int expected_output1 = 5;
  const int output1 = dynamic_programming::minimum_edit_distance::editDistDP(
      str1, str2, str1.length(), str2.length());
  assert(output1 == expected_output1);
  std::cout << "Minimum Number of Operations Required: " << output1
            << std::endl;

  // test 2
  std::string str3 = "SATURDAY";
  std::string str4 = "SUNDAY";
  const int expected_output2 = 3;
  const int output2 = dynamic_programming::minimum_edit_distance::editDistDP(
      str3, str4, str3.length(), str4.length());
  assert(output2 == expected_output2);
  std::cout << "Minimum Number of Operations Required: " << output2
            << std::endl;
}

/**
 * @brief main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
  test();  // run self-test implementations
  return 0;
}
