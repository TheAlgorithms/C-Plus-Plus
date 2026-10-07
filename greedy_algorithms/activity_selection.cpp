/**
 * @file
 * @brief Implementation of the [Activity Selection
 * Problem](https://en.wikipedia.org/wiki/Activity_selection_problem)
 * using the greedy approach.
 * @details
 * The activity selection problem is an optimization problem concerning the
 * selection of non-conflicting activities to perform within a given time frame,
 * given a set of activities each marked by a start time and a finish time.
 * The goal is to select a maximum-size set of mutually compatible activities.
 *
 * The greedy strategy works by sorting activities in increasing order of their
 * finish times, then greedily selecting the first compatible activity that
 * finishes earliest. This greedy choice property is proven optimal in
 * Introduction to Algorithms (CLRS) Chapter 16.1.
 *
 * Time Complexity: $O(n \log n)$ due to sorting.
 * Space Complexity: $O(n)$ to store and return the selected activities.
 *
 * @author [Shriyans Bharuka](https://github.com/ShriyansBharuka)
 * @see jump_game.cpp, knapsack.cpp
 */

#include <algorithm>  /// for std::sort
#include <cassert>    /// for assert
#include <cstddef>    /// for std::size_t
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace greedy_algorithms
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @namespace activity_selection
 * @brief Functions for the [Activity Selection
 * Problem](https://en.wikipedia.org/wiki/Activity_selection_problem)
 * implementation
 */
namespace activity_selection {

/**
 * @brief Representation of an activity with start and finish times.
 * @tparam T numeric type representing time (e.g., int, double)
 */
template <typename T>
struct Activity {
    std::size_t id{0};    ///< Identifier of the activity
    T start_time{0};      ///< Start time of the activity
    T finish_time{0};     ///< Finish time of the activity

    /**
     * @brief Equality operator for verifying selected activities in tests.
     */
    bool operator==(const Activity<T> &other) const {
        return id == other.id && start_time == other.start_time &&
               finish_time == other.finish_time;
    }
};

/**
 * @brief Selects the maximum number of mutually compatible activities.
 * @tparam T numeric type representing time (e.g., int, double)
 * @param activities list of candidate activities
 * @return std::vector<Activity<T>> maximum set of mutually compatible
 * activities
 */
template <typename T>
std::vector<Activity<T>> select_activities(
    std::vector<Activity<T>> activities) {
    if (activities.empty()) {
        return {};
    }

    // Sort activities by finish time in non-decreasing order.
    // If finish times are equal, sort by start time.
    std::sort(activities.begin(), activities.end(),
              [](const Activity<T> &a, const Activity<T> &b) {
                  if (a.finish_time == b.finish_time) {
                      return a.start_time < b.start_time;
                  }
                  return a.finish_time < b.finish_time;
              });

    std::vector<Activity<T>> selected;
    // The activity with the earliest finish time is always selected
    selected.push_back(activities[0]);
    std::size_t last_selected_idx = 0;

    for (std::size_t i = 1; i < activities.size(); ++i) {
        // If the start time of the current activity is greater than or equal
        // to the finish time of the last selected activity, it is compatible.
        if (activities[i].start_time >= activities[last_selected_idx].finish_time) {
            selected.push_back(activities[i]);
            last_selected_idx = i;
        }
    }

    return selected;
}

}  // namespace activity_selection
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using ActivityInt = greedy_algorithms::activity_selection::Activity<int>;
    using ActivityDouble =
        greedy_algorithms::activity_selection::Activity<double>;

    // Test Case 1: Standard textbook example from CLRS Chapter 16.1
    std::vector<ActivityInt> clrs_activities = {
        {1, 1, 4},   {2, 3, 5},  {3, 0, 6},   {4, 5, 7},
        {5, 3, 9},   {6, 5, 9},  {7, 6, 10},  {8, 8, 11},
        {9, 8, 12},  {10, 2, 14}, {11, 12, 16}};

    auto selected_clrs =
        greedy_algorithms::activity_selection::select_activities(clrs_activities);

    // Expected selected activities: a1 (1, 4), a4 (5, 7), a8 (8, 11), a11 (12, 16)
    assert(selected_clrs.size() == 4);
    assert(selected_clrs[0].id == 1);
    assert(selected_clrs[1].id == 4);
    assert(selected_clrs[2].id == 8);
    assert(selected_clrs[3].id == 11);

    // Test Case 2: Empty input
    std::vector<ActivityInt> empty_activities = {};
    auto selected_empty =
        greedy_algorithms::activity_selection::select_activities(empty_activities);
    assert(selected_empty.empty());

    // Test Case 3: Single activity
    std::vector<ActivityInt> single_activity = {{1, 2, 5}};
    auto selected_single =
        greedy_algorithms::activity_selection::select_activities(single_activity);
    assert(selected_single.size() == 1);
    assert(selected_single[0].id == 1);

    // Test Case 4: Completely overlapping activities (all overlap each other)
    std::vector<ActivityInt> overlapping = {
        {1, 1, 10}, {2, 2, 9}, {3, 3, 8}, {4, 4, 7}};
    auto selected_overlap =
        greedy_algorithms::activity_selection::select_activities(overlapping);
    // Only one activity can be chosen, specifically the one finishing earliest (id: 4)
    assert(selected_overlap.size() == 1);
    assert(selected_overlap[0].id == 4);

    // Test Case 5: Non-overlapping sequential activities
    std::vector<ActivityInt> sequential = {
        {1, 0, 2}, {2, 2, 4}, {3, 4, 6}, {4, 6, 8}};
    auto selected_sequential =
        greedy_algorithms::activity_selection::select_activities(sequential);
    assert(selected_sequential.size() == 4);
    assert(selected_sequential[0].id == 1);
    assert(selected_sequential[1].id == 2);
    assert(selected_sequential[2].id == 3);
    assert(selected_sequential[3].id == 4);

    // Test Case 6: Floating-point times
    std::vector<ActivityDouble> floating_activities = {
        {1, 1.5, 3.5}, {2, 3.5, 5.0}, {3, 2.0, 4.0}, {4, 5.0, 6.5}};
    auto selected_float =
        greedy_algorithms::activity_selection::select_activities(
            floating_activities);
    assert(selected_float.size() == 3);
    assert(selected_float[0].id == 1);
    assert(selected_float[1].id == 2);
    assert(selected_float[2].id == 4);

    // Test Case 7: Activities with identical finish times
    std::vector<ActivityInt> same_finish = {
        {1, 3, 6}, {2, 1, 6}, {3, 6, 9}};
    auto selected_same_finish =
        greedy_algorithms::activity_selection::select_activities(same_finish);
    assert(selected_same_finish.size() == 2);
    assert(selected_same_finish[1].id == 3);

    std::cout << "All activity selection tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
