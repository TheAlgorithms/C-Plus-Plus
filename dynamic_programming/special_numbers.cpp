/**
 * @file
 * @brief A positive number is special if all of its digits are distinct.
 * The purpose of this problem is to find out all the special numbers
 * in range [1,n]
 *
 * @details
 * This problem can be classified under Digit DP. The idea is to use bitmask and
 * Dynamic Programmic to optimize our solution for the larger values of n.
 * For example: example 1:- N: 20, OUTPUT: 19
 *
 * For example: example 2:-
 * X: '5', OUTPUT: 2
 * @author [Maaz](https://github.com/riddle07)
 * @see more on
 * https://leetcode.com/problems/count-special-integers/description/
 */

// header files
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
/**
 * @namespace dynamic_programming
 * @brief Digit Dynamic Programming Algorithms
 */
namespace dynamic_programming {

/**
 * @namespace special_numbers
 * @brief Counting Special Numbers in range [1,n]
 */
namespace special_numbers {

// vector for storing the upper limit for each digit place

std::vector<int> v;

// dp array to memoize the solution for given transition states

int dp[(1 << 10)][11][2][2];
/**
 * Depth-first-Search Function to check for the eligibility for digits
 * at available digit place.
 *
 * Before talking about the memoization part, let us first talk about the
 * transiion states:
 *
 * d: Marks the digit place we are considering the allowable digits for.
 * mask: Tells us what digits are already present in the soln subset
 * flag: Tells us if a digit bigger than the upper bound can be taken or not,
 * note -> flag will only be one for less significant digit place, if there is
 * smaller than available digit in higher digit place. s: Equals to 1 if there
 * is a non zero digit in soln subset
 *
 */
int dfs(int d, int mask, bool flag, bool s) {
    if (d <= 0)
        return 1;

    if (dp[mask][d][flag][s] != -1)
        return dp[mask][d][flag][s];

    int ans = 0;
    /**
     * here, for every digit place starting from left
     * we will check the eligibility of all digits 0-9 in that position
     *
     */
    for (int i = 0; i <= 9; i++) {
        // conidering for digit 0
        if (!i) {
            /**
             * If there i a non zero digit present in soln subset
             * and 0 is already there in soln subset, we can't do anything
             * so we move ahead
             *
             */

            if (s && ((mask & (1 << i)) == 0)) {
            }

            // If zero is not in subset we have following cases

            else if (s) {
                // if (flag = 1) we have can take higher digits too

                if (flag || (i < v[v.size() - d])) {
                    ans += dfs(d - 1, (mask ^ (1 << i)), 1, 1);

                    // if flag is not 1, only 0 can be taken, hence, flag is
                    // continued as 1

                } else
                    ans += dfs(d - 1, (mask ^ (1 << i)), 0, 1);
            }

            // if there is no digit before 0, we can take multiple 0 to fill in
            // positions

            else {
                if (flag || (i < v[v.size() - d])) {
                    ans += dfs(d - 1, mask, 1, 0);
                } else
                    ans += dfs(d - 1, mask, 0, 0);
            }
        }

        // if the digit is not zero and not in soln subset

        else if (mask & (1 << i)) {
            // (flag = 1) we can take any digit but if not and digit is lesser
            // than upper bound
            // we can still take it

            if (flag || (i < v[v.size() - d]))
                ans += dfs(d - 1, (mask ^ (1 << i)), 1, 1);

            // highest attainable digit taken hence, flag is passed as 0

            else if (i == v[v.size() - d])
                ans += dfs(d - 1, (mask ^ (1 << i)), 0, 1);
        }
    }
    return dp[mask][d][flag][s] = ans;
}
int countSpecialNumbers(int n) {
    // calculating the length of the number

    int d = log10(n) + 1;

    // converting number -> vector format
    v.clear();
    while (n) {
        v.push_back(n % 10);
        n = n / 10;
    }
    reverse(v.begin(), v.end());
    /**
     * creating a mask to store what digit has been taken in the subset
     * of solution. If a bit is set then the corresponding digit is
     * yet to be considered in the solution.
     *
     */
    int mask = (1 << 10) - 1;
    memset(dp, -1, sizeof(dp));
    //-1 is done to remove 0 as it is not in range [1,n]
    return dfs(d, mask, 0, 0) - 1;
}
}  // namespace special_numbers
}  // namespace dynamic_programming

/**
 * @brief Test function
 *
 */

static void test() {
    // custom input vector
    std::vector<int> tests{20, 5, 135};

    // calculated output vector by countSpecialNumbers function
    std::vector<int> calculatedOutput(3, 0);
    int i = 0;
    for (auto &x : tests) {
        calculatedOutput[i] =
            dynamic_programming::special_numbers::countSpecialNumbers(x);
        i++;
    }

    // expected output vector acc to problem statement
    std::vector<int> expectedOutput{19, 5, 110};

    // Testing implementation via assert function
    // It will throw error if any of the expected test fails
    // Else it will give nothing
    for (int i = 0; i < tests.size(); i++) {
        assert(expectedOutput[i] == calculatedOutput[i]);
    }

    std::cout << "All tests passed successfully!\n";
    return;
}

// namespace dynamic_programming

/** Main function (driver code)*/
int main() {
    // test for implementation
    test();

    // user input
    int n;
    std::cin >> n;

    int ans;

    // user output
    ans = dynamic_programming::special_numbers::countSpecialNumbers(n);
    std::cout << ans;
    return 0;
}