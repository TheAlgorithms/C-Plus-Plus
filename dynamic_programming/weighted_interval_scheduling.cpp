/**
 * @file
 * @brief Implementation of [Weighted Interval Scheduling Problem]
 * (https://en.wikipedia.org/wiki/Interval_scheduling)
 *
 * @details
 * The Weighted Interval Scheduling problem is a classic optimization problem
 * where we have n intervals, each with a start time, end time, and profit.
 * The goal is to select a subset of non-overlapping intervals such that the
 * total profit is maximized.
 *
 * ### Problem Statement:
 * Given n intervals where each interval i has:
 * - start[i]: start time of interval i
 * - end[i]: end time of interval i  
 * - profit[i]: profit gained by selecting interval i
 *
 * Find the maximum profit that can be obtained by selecting non-overlapping
 * intervals.
 *
 * ### Algorithm:
 * 1. Sort intervals by their end times
 * 2. For each interval, use binary search to find the latest non-overlapping
 *    interval
 * 3. Use dynamic programming: dp[i] = max(profit[i] + dp[j], dp[i-1])
 *    where j is the latest non-overlapping interval with interval i
 *
 * Time Complexity: O(n log n) - due to sorting and binary search
 * Space Complexity: O(n) - for the DP array
 *
 * @author [Your Name]
 */

#include <algorithm>  /// for std::sort, std::max
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace weighted_interval_scheduling
 * @brief Implementation of Weighted Interval Scheduling problem
 */
namespace weighted_interval_scheduling {

/**
 * @brief Structure to represent an interval with start time, end time, and profit
 */
struct Interval {
    int start;   ///< start time of the interval
    int end;     ///< end time of the interval
    int profit;  ///< profit gained by selecting this interval
    
    /**
     * @brief Constructor for Interval
     * @param s start time
     * @param e end time  
     * @param p profit
     */
    Interval(int s, int e, int p) : start(s), end(e), profit(p) {}
};

/**
 * @brief Comparator to sort intervals by their end times
 * @param a first interval
 * @param b second interval
 * @return true if a should come before b in sorted order
 */
bool compareByEndTime(const Interval &a, const Interval &b) {
    return a.end < b.end;
}

/**
 * @brief Find the latest non-overlapping interval using binary search
 * @param intervals vector of sorted intervals (by end time)
 * @param index current interval index
 * @return index of latest non-overlapping interval, or -1 if none exists
 */
int findLatestNonOverlapping(const std::vector<Interval> &intervals, int index) {
    int left = 0, right = index - 1;
    int result = -1;
    
    // Binary search for the latest interval that ends before current interval starts
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (intervals[mid].end <= intervals[index].start) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

/**
 * @brief Solve the weighted interval scheduling problem
 * @param intervals vector of intervals with start time, end time, and profit
 * @return maximum profit that can be obtained
 */
int solveWeightedIntervalScheduling(std::vector<Interval> intervals) {
    if (intervals.empty()) {
        return 0;
    }
    
    int n = intervals.size();
    
    // Sort intervals by their end times
    std::sort(intervals.begin(), intervals.end(), compareByEndTime);
    
    // dp[i] represents maximum profit using intervals 0 to i
    std::vector<int> dp(n);
    dp[0] = intervals[0].profit;
    
    for (int i = 1; i < n; i++) {
        // Option 1: Don't include current interval
        int excludeProfit = dp[i - 1];
        
        // Option 2: Include current interval
        int includeProfit = intervals[i].profit;
        int latestNonOverlapping = findLatestNonOverlapping(intervals, i);
        
        if (latestNonOverlapping != -1) {
            includeProfit += dp[latestNonOverlapping];
        }
        
        // Take maximum of both options
        dp[i] = std::max(includeProfit, excludeProfit);
    }
    
    return dp[n - 1];
}

/**
 * @brief Solve and return the selected intervals (bonus: solution reconstruction)
 * @param intervals vector of intervals with start time, end time, and profit
 * @return pair containing maximum profit and vector of selected intervals
 */
std::pair<int, std::vector<Interval>> solveWithSolution(std::vector<Interval> intervals) {
    if (intervals.empty()) {
        return {0, {}};
    }
    
    int n = intervals.size();
    std::sort(intervals.begin(), intervals.end(), compareByEndTime);
    
    std::vector<int> dp(n);
    dp[0] = intervals[0].profit;
    
    for (int i = 1; i < n; i++) {
        int excludeProfit = dp[i - 1];
        int includeProfit = intervals[i].profit;
        int latestNonOverlapping = findLatestNonOverlapping(intervals, i);
        
        if (latestNonOverlapping != -1) {
            includeProfit += dp[latestNonOverlapping];
        }
        
        dp[i] = std::max(includeProfit, excludeProfit);
    }
    
    // Reconstruct solution
    std::vector<Interval> selectedIntervals;
    int i = n - 1;
    
    while (i >= 0) {
        if (i == 0 || dp[i] != dp[i - 1]) {
            // Current interval is included
            selectedIntervals.push_back(intervals[i]);
            int latestNonOverlapping = findLatestNonOverlapping(intervals, i);
            i = latestNonOverlapping;
        } else {
            // Current interval is not included
            i--;
        }
    }
    
    // Reverse to get chronological order
    std::reverse(selectedIntervals.begin(), selectedIntervals.end());
    
    return {dp[n - 1], selectedIntervals};
}

}  // namespace weighted_interval_scheduling
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using namespace dynamic_programming::weighted_interval_scheduling;
    
    // Test case 1: Basic example
    std::vector<Interval> intervals1 = {
        Interval(1, 4, 2),   // [1,4] profit=2
        Interval(3, 5, 4),   // [3,5] profit=4  
        Interval(0, 6, 1),   // [0,6] profit=1
        Interval(5, 7, 6),   // [5,7] profit=6
        Interval(8, 9, 5),   // [8,9] profit=5
        Interval(5, 9, 2)    // [5,9] profit=2
    };
    
    int result1 = solveWeightedIntervalScheduling(intervals1);
    // Let me trace through this step by step:
    // After sorting by end time: [1,4,2], [3,5,4], [0,6,1], [5,7,6], [8,9,5], [5,9,2]
    // Optimal solution: [3,5] (profit=4), [5,7] (profit=6), [8,9] (profit=5) = 15 total
    assert(result1 == 15);

    
    // Test case 1: Simple non-overlapping case  
    std::vector<Interval> simpleTest = {
        Interval(1, 2, 10),
        Interval(3, 4, 20), 
        Interval(5, 6, 30)
    };
    int simpleResult = solveWeightedIntervalScheduling(simpleTest);
    assert(simpleResult == 60); // All intervals can be selected: 10+20+30=60
    
    // Test case 2: Overlapping intervals where we need to choose
    std::vector<Interval> overlapTest = {
        Interval(0, 2, 1),   // [0,2] profit=1
        Interval(1, 3, 10),  // [1,3] profit=10 (overlaps with first)
        Interval(2, 4, 5)    // [2,4] profit=5 (overlaps with second)
    };
    int overlapResult = solveWeightedIntervalScheduling(overlapTest);
    assert(overlapResult == 10); // Should select [1,3] for maximum profit
    
    // Test case 3: Empty input
    std::vector<Interval> emptyTest = {};
    int emptyResult = solveWeightedIntervalScheduling(emptyTest);
    assert(emptyResult == 0);
    
    // Test solution reconstruction
    auto [maxProfit, selectedIntervals] = solveWithSolution(simpleTest);
    assert(maxProfit == 60);
    assert(selectedIntervals.size() == 3);
    
    std::cout << "All test cases passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    using namespace dynamic_programming::weighted_interval_scheduling;
    
    int n;
    std::cout << "Enter number of intervals: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Number of intervals must be positive." << std::endl;
        return 1;
    }
    
    std::vector<Interval> intervals;
    intervals.reserve(n);
    
    std::cout << "Enter intervals (start_time end_time profit):" << std::endl;
    for (int i = 0; i < n; i++) {
        int start, end, profit;
        std::cin >> start >> end >> profit;
        
        if (start >= end) {
            std::cout << "Invalid interval: start time must be less than end time." << std::endl;
            return 1;
        }
        
        intervals.emplace_back(start, end, profit);
    }
    
    int maxProfit = solveWeightedIntervalScheduling(intervals);
    std::cout << "\nMaximum profit: " << maxProfit << std::endl;
    
    // Also show the solution
    auto [profit, selectedIntervals] = solveWithSolution(intervals);
    std::cout << "\nSelected intervals:" << std::endl;
    for (const auto& interval : selectedIntervals) {
        std::cout << "[" << interval.start << ", " << interval.end 
                  << "] profit=" << interval.profit << std::endl;
    }
    
    test();  // run self-test implementations
    
    return 0;
}