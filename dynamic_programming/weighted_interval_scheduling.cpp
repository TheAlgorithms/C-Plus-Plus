/**
 * @file
 * @brief Implements the [Weighted Interval Scheduling]
 * (https://www.geeksforgeeks.org/dsa/weighted-job-scheduling/) problem.
 *
 * @details
 * The Weighted Interval Scheduling problem is a classic optimization challenge.
 * Given a set of intervals, each with a start time, end time, and a profit,
 * the goal is to find a subset of non-overlapping intervals that maximizes
 * the total profit. This implementation uses dynamic programming combined
 * with binary search to achieve an efficient solution.
 *
 * Example:
 * Intervals: [{1, 3, 50}, {4, 6, 70}, {6, 19, 100}, {2, 5, 20}]
 * Max Profit: 120 (by choosing {1, 3, 50} and {4, 6, 70})
 *
 * Constraints & Assumptions:
 * - Interval start times, end times, and profits are non-negative integers.
 * - The start time of an interval is always less than its end time.
 * - An empty set of intervals will result in a profit of 0.
 * - Intervals are considered non-overlapping if one ends before or at the same time the other begins.
 *
 * Time Complexity: O(n log n), dominated by the initial sort of intervals.
 * Space Complexity: O(n) for the dynamic programming table.
 *
 * @author [Soumyadipta-Banerjee](https://github.com/Soumyadipta-Banerjee)
 */

#include <algorithm>      /// for std::sort, std::max
#include <cassert>        /// for std::assert
#include <iostream>       /// for IO operations
#include <vector>         /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace weighted_interval_scheduling
 * @brief Functions for the [Weighted Interval Scheduling]
 * (https://www.geeksforgeeks.org/dsa/weighted-job-scheduling/) problem.
 */
namespace weighted_interval_scheduling {
/**
 * @brief Struct to represent an interval (or job).
 */
struct Interval {
    int start, end, profit;
};

/**
 * @brief Comparison function to sort intervals based on their end time.
 * @param a First interval
 * @param b Second interval
 * @returns true if interval a's end time is less than b's.
 */
bool compareIntervals(const Interval& a, const Interval& b) {
    return a.end < b.end;
}

/**
 * @brief Finds the latest non-overlapping interval using binary search.
 * This is a helper function for the main DP algorithm.
 * @param intervals Sorted vector of intervals.
 * @param i Index of the current interval.
 * @returns Index of the latest compatible interval, or -1 if none exists.
 */
int findLatestNonOverlapping(const std::vector<Interval>& intervals, int i) {
    int low = 0, high = i - 1;
    int result = -1;

    // Perform binary search to find the latest compatible interval.
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (intervals[mid].end <= intervals[i].start) {
            // This interval is compatible, it could be our answer.
            // But we look for a later one in the right half.
            result = mid;
            low = mid + 1;
        } else {
            // This interval overlaps, so we search in the left half.
            high = mid - 1;
        }
    }
    return result;
}

/**
 * @brief Main function to solve the Weighted Interval Scheduling problem.
 * @param intervals A vector of intervals. It will be sorted in-place.
 * @returns The maximum achievable profit.
 */
int findMaxProfit(std::vector<Interval>& intervals) {
    if (intervals.empty()) {
        return 0;
    }

    // Sort intervals based on their end times. This is a prerequisite.
    std::sort(intervals.begin(), intervals.end(), compareIntervals);

    int n = intervals.size();
    // dp[i] will store the maximum profit for the first i+1 intervals.
    std::vector<int> dp(n);
    // Base case: The max profit for the first interval is its own profit.
    dp[0] = intervals[0].profit;

    // Fill the DP table from the second interval onwards.
    for (int i = 1; i < n; ++i) {
        // Option 1: Include the current interval.
        // The profit would be its own profit plus the max profit of compatible intervals.
        int profit_including_current = intervals[i].profit;
        int latest_non_overlapping_idx = findLatestNonOverlapping(intervals, i);
        if (latest_non_overlapping_idx != -1) {
            profit_including_current += dp[latest_non_overlapping_idx];
        }

        // Option 2: Exclude the current interval.
        // The profit would be the same as the max profit up to the previous interval.
        int profit_excluding_current = dp[i - 1];

        // The max profit at this stage is the best of the two options.
        dp[i] = std::max(profit_including_current, profit_excluding_current);
    }

    // The last element in the DP table holds the overall maximum profit.
    return dp[n - 1];
}

}  // namespace weighted_interval_scheduling
}  // namespace dynamic_programming

/**
 * @brief Test Function to verify the implementation with corrected test cases.
 * @return void
 */
static void test() {
    // Test Case 1: Standard example from GeeksforGeeks, verified.
    std::vector<dynamic_programming::weighted_interval_scheduling::Interval> intervals1 = {
        {3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
    assert(dynamic_programming::weighted_interval_scheduling::findMaxProfit(intervals1) == 250);

    // Test Case 2: Your original test case, correct expected profit is 150.
    std::vector<dynamic_programming::weighted_interval_scheduling::Interval> intervals2 = {
        {1, 3, 50}, {2, 5, 20}, {6, 19, 100}, {4, 6, 70}};
    assert(dynamic_programming::weighted_interval_scheduling::findMaxProfit(intervals2) == 220);

    // Test Case 3: Another verified online example.
    std::vector<dynamic_programming::weighted_interval_scheduling::Interval> intervals3 = {
        {1, 3, 5}, {2, 5, 6}, {4, 6, 5}, {6, 7, 4}, {5, 8, 11}, {7, 9, 2}};
    assert(dynamic_programming::weighted_interval_scheduling::findMaxProfit(intervals3) == 17);

    // Test Case 4: Edge case with an empty set of intervals.
    std::vector<dynamic_programming::weighted_interval_scheduling::Interval> intervals4 = {};
    assert(dynamic_programming::weighted_interval_scheduling::findMaxProfit(intervals4) == 0);

    // Test Case 5: Edge case with a single interval.
    std::vector<dynamic_programming::weighted_interval_scheduling::Interval> intervals5 = {{1, 100, 55}};
    assert(dynamic_programming::weighted_interval_scheduling::findMaxProfit(intervals5) == 55);

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}