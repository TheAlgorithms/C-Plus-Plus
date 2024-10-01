/**
 * @file
 * @brief [Gale Shapley](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
 * @details
 * This implementation utilizes the Gale-Shapley algorithm to find stable matches
 *
 * **Gale Shapley** aims to find a stable matching between two equally sized 
 * sets of elements given an ordinal preference for each element. The algorithm was
 * introduced by David Gale and Lloyd Shapley in 1962.
 * 
 * Reference: 
 * [Wikipedia](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
 * [Wikipedia](https://en.wikipedia.org/wiki/Stable_marriage_problem)
 *
 * @author [B Karthik](https://github.com/BKarthik7)
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @namespace
 * @brief Functions for the [Gale Shapley](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm) algorithm
 */
namespace stable_marriage {
void gale_shapley(const std::vector<std::vector<int>>& set_2_prefs, const std::vector<std::vector<int>>& set_1_prefs) {
    int n = set_2_prefs.size();
    std::vector<int> engagements(n, -1);
    std::vector<bool> free_set_1_s(n, true);
    std::vector<int> next_proposal(n, 0); // Tracks the next set_2 to propose for each set_1

    while (true) {
        int free_set_1;
        for (free_set_1 = 0; free_set_1 < n; free_set_1++) {
            if (free_set_1_s[free_set_1]) break;
        }
        if (free_set_1 == n) break;

        int set_2_to_propose = set_1_prefs[free_set_1][next_proposal[free_set_1]];
        next_proposal[free_set_1]++;
        int currentFiance = engagements[set_2_to_propose];

        if (currentFiance == -1) {
            engagements[set_2_to_propose] = free_set_1;
            free_set_1_s[free_set_1] = false;
        } else {
            if (std::find(set_2_prefs[set_2_to_propose].begin(), set_2_prefs[set_2_to_propose].end(), free_set_1) <
                std::find(set_2_prefs[set_2_to_propose].begin(), set_2_prefs[set_2_to_propose].end(), currentFiance)) {
                engagements[set_2_to_propose] = free_set_1;
                free_set_1_s[free_set_1] = false;
                free_set_1_s[currentFiance] = true;
            }
        }
    }

    std::cout << "Stable Matches:\n";
    for (int set_2 = 0; set_2 < n; set_2++) {
        std::cout << "set_2's " << set_2 << " is matched to set_1's " << engagements[set_2] << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace stable_marriage
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */

static void tests() {
    // Test Case 1
    std::vector<std::vector<int>> set_1_prefs = {{0, 1, 2, 3}, {2, 1, 3, 0}, {1, 2, 0, 3}, {3, 0, 1, 2}};
    std::vector<std::vector<int>> set_2_prefs = {{1, 0, 2, 3},{3, 0, 1, 2},{0, 2, 1, 3},{1, 2, 0, 3}};
    greedy_algorithms::stable_marriage::gale_shapley(set_2_prefs, set_1_prefs);

    // Test Case 2
    set_1_prefs = {{0, 2, 1, 3}, {2, 3, 0, 1}, {3, 1, 2, 0}, {2, 1, 0, 3}};
    set_2_prefs = {{1, 0, 2, 3},{3, 0, 1, 2},{0, 2, 1, 3},{1, 2, 0, 3}};
    greedy_algorithms::stable_marriage::gale_shapley(set_2_prefs, set_1_prefs);

    // Test Case 3
    set_1_prefs = {{0, 1, 2}, {2, 1, 0}, {1, 2, 0}};
    set_2_prefs = {{1, 0, 2},{2, 0, 1},{0, 2, 1}};
    greedy_algorithms::stable_marriage::gale_shapley(set_2_prefs, set_1_prefs);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests(); // run self-test implementations
    return 0;
}
