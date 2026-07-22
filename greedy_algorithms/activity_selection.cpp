/**
 * @file activity_selection.cpp
 * @brief Implementation of the [Activity Selection
 * Problem](https://en.wikipedia.org/wiki/Activity_selection_problem) using a
 * greedy approach.
 * @details
 * The activity selection problem is a combinatorial optimization problem
 * concerned with selecting the maximum number of non-conflicting activities
 * from a set of activities, each having a start time and a finish time,
 * given that a single resource (e.g., a lecture hall or a machine) can only
 * be used by one activity at a time.
 *
 * The greedy strategy is to always pick the next activity whose finish time
 * is the smallest among the remaining compatible activities. Sorting all
 * activities by finish time and then scanning through them once, only
 * selecting an activity whose start time is not earlier than the finish
 * time of the previously selected activity, yields an optimal solution in
 * O(n log n) time.
 * @author [Your Name](https://github.com/your-github-handle)
 */

#include <algorithm>  /// for std::sort
#include <cassert>    /// for assert
#include <cstdint>    /// for std::uint32_t
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {

/**
 * @brief Represents a single activity with a start time and a finish time.
 */
struct Activity {
    std::uint32_t start;   ///< start time of the activity
    std::uint32_t finish;  ///< finish time of the activity
};

/**
 * @brief A class that solves the Activity Selection Problem using a greedy
 * approach.
 */
class ActivitySelection {
 public:
    /**
     * @brief Selects the maximum number of non-conflicting activities.
     * @param activities A vector of activities, each with a start and a
     * finish time.
     * @return A vector containing the maximum set of non-conflicting
     * activities, ordered by finish time.
     */
    std::vector<Activity> selectActivities(
        std::vector<Activity> activities) const {
        std::vector<Activity> selected;

        if (activities.empty()) {
            return selected;
        }

        // Greedy choice: always process activities in increasing order of
        // finish time.
        std::sort(activities.begin(), activities.end(),
                  [](const Activity &a, const Activity &b) {
                      return a.finish < b.finish;
                  });

        // The first activity (smallest finish time) is always selected.
        selected.push_back(activities[0]);
        std::uint32_t lastFinishTime = activities[0].finish;

        for (std::size_t i = 1; i < activities.size(); i++) {
            // Select the activity only if its start time is not earlier
            // than the finish time of the previously selected activity.
            if (activities[i].start >= lastFinishTime) {
                selected.push_back(activities[i]);
                lastFinishTime = activities[i].finish;
            }
        }

        return selected;
    }
};

}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    greedy_algorithms::ActivitySelection activitySelection;

    // Test case 1: Standard case with overlapping activities.
    // Expected optimal selection (by finish time): (1,4), (5,7), (8,11),
    // (12,14)
    std::vector<greedy_algorithms::Activity> activities1 = {
        {1, 4},  {3, 5},  {0, 6},  {5, 7},  {3, 8},  {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}};
    std::vector<greedy_algorithms::Activity> expected1 = {
        {1, 4}, {5, 7}, {8, 11}, {12, 14}};
    std::vector<greedy_algorithms::Activity> result1 =
        activitySelection.selectActivities(activities1);
    assert(result1.size() == expected1.size());
    for (std::size_t i = 0; i < result1.size(); i++) {
        assert(result1[i].start == expected1[i].start);
        assert(result1[i].finish == expected1[i].finish);
    }

    // Test case 2: No overlapping activities, so all should be selected.
    std::vector<greedy_algorithms::Activity> activities2 = {
        {1, 2}, {3, 4}, {5, 6}, {7, 8}};
    std::vector<greedy_algorithms::Activity> result2 =
        activitySelection.selectActivities(activities2);
    assert(result2.size() == 4);

    // Test case 3: All activities overlap, so only one can be selected.
    std::vector<greedy_algorithms::Activity> activities3 = {
        {1, 10}, {2, 9}, {3, 8}, {4, 7}};
    std::vector<greedy_algorithms::Activity> result3 =
        activitySelection.selectActivities(activities3);
    assert(result3.size() == 1);
    assert(result3[0].start == 4);
    assert(result3[0].finish == 7);

    // Test case 4: Empty input.
    std::vector<greedy_algorithms::Activity> activities4 = {};
    std::vector<greedy_algorithms::Activity> result4 =
        activitySelection.selectActivities(activities4);
    assert(result4.empty());

    // Test case 5: Single activity.
    std::vector<greedy_algorithms::Activity> activities5 = {{2, 5}};
    std::vector<greedy_algorithms::Activity> result5 =
        activitySelection.selectActivities(activities5);
    assert(result5.size() == 1);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
