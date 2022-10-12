/**
 * @file
 * @brief Implementation of cutting a rod problem
 *
 * @details
 * Given a rod of length n inches and an array of prices that
 * contains prices of all pieces of size<=n. Determine
 * the maximum profit obtainable by cutting up the rod and selling
 * the pieces.
 *
 * ### Algorithm
 * The idea is to break the given rod into every smaller piece as possible
 * and then check profit for each piece, by calculating maximum profit for
 * smaller pieces we will build the solution for larger pieces in bottom-up
 * manner.
 *
 * @author [Anmol](https://github.com/Anmol3299)
 * @author [Pardeep](https://github.com/Pardeep009)
 */

#include <array>
#include <cassert>
#include <climits>
#include <iostream>
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace cut_rod
 * @brief Implementation of cutting a rod problem
 */
namespace cut_rod {
/**
 * @brief Cuts the rod in different pieces and
 * stores the maximum profit for each piece of the rod.
 * @tparam T size of the price array
 * @param n size of the rod in inches
 * @param price an array of prices that contains prices of all pieces of size<=n
 * @return maximum profit obtainable for @param n inch rod.
 */
template <size_t T>
int maxProfitByCuttingRod(const std::array<int, T> &price, const uint64_t &n) {
    int *profit =
        new int[n + 1];  // profit[i] will hold maximum profit for i inch rod

    profit[0] = 0;  // if length of rod is zero, then no profit

    // outer loop will select size of rod, starting from 1 inch to n inch rod.
    // inner loop will evaluate the maximum profit we can get for i inch rod by
    // making every possible cut on it and will store it in profit[i].
    for (size_t i = 1; i <= n; i++) {
        int q = INT_MIN;
        for (size_t j = 1; j <= i; j++) {
            q = std::max(q, price[j - 1] + profit[i - j]);
        }
        profit[i] = q;
    }
    const int16_t ans = profit[n];
    delete[] profit;
    return ans;  // returning maximum profit
}
}  // namespace cut_rod
}  // namespace dynamic_programming

/**
 * @brief Function to test above algorithm
 * @returns void
 */
static void test() {
    // Test 1
    const int16_t n1 = 8;                                        // size of rod
    std::array<int32_t, n1> price1 = {1,2,4,6,8,45,21,9};  // price array
    const int64_t max_profit1 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price1, n1);
    const int64_t expected_max_profit1 = 47;
    assert(max_profit1 == expected_max_profit1);
    std::cout << "Maximum profit with " << n1 << " inch road is " << max_profit1
              << std::endl;

    // Test 2
    const int16_t n2 = 30;  // size of rod
    std::array<int32_t, n2> price2 = {
        1,  5,  8,  9,  10, 17, 17, 20, 24, 30,  // price array
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    const int64_t max_profit2=
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price2, n2);
    const int32_t expected_max_profit2 = 90;
    assert(max_profit2 == expected_max_profit2);
    std::cout << "Maximum profit with " << n2 << " inch road is " << max_profit2
              << std::endl;
     // Test 3
    const int16_t n3 = 5;                                        // size of rod
    std::array<int32_t, n3> price3 = {2,9,17,23,45};  // price array
    const int64_t max_profit3 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price3, n3);
    const int64_t expected_max_profit3 = 45;
    assert(max_profit3 == expected_max_profit3);
    std::cout << "Maximum profit with " << n3 << " inch road is " << max_profit3
              << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing
    test();
    return 0;
}
