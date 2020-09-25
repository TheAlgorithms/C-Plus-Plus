/**
 * @file cut_rod.cpp
 * @brief Implementation of cutting a rod problem
 *
 * @details
 * Given a rod of length n inches and an array of prices that
 * contains prices of all pieces of size smaller than n. Determine
 * the maximum profit obtainable by cutting up the rod and selling
 * the pieces.
 *
 */

#include <array>
#include <climits>
#include <iostream>

template <size_t T>

/**
 * This function cuts the rod in different pieces and stores the maximum profit
 * for each piece of the rod.
 * @param n size of the rod in inches
 * @param price an array of prices that contains prices of all pieces of size<=n
 * @return maximum profit obtainable for @param n inch rod.
 */
int cut_rod(const std::array<int, T> &price, const int n) {
    // profit[i] will hold maximum profit for i inch rod
    int *profit = new int[n + 1];

    // if length of rod is zero, then no profit
    profit[0] = 0;

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
    int ans = profit[n];
    delete[] profit;
    return ans; /** return maximum profit obtainable for @param n inch rod */
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    const int n = 30;  // size of rod
    std::array<int, n> price = {
        1,  5,  8,  9,  10, 17, 17, 20, 24, 30,  // price array
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    // maximum profit
    std::cout << cut_rod(price, n);

    return 0;
}
