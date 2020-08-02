/**
 * @file
 * @brief returns which is the longest/shortest number
 * using [minimax](https://en.wikipedia.org/wiki/Minimax) algorithm
 *
 * @details
 * Minimax (sometimes MinMax, MM or saddle point) is a decision rule used in
 * artificial intelligence, decision theory, game theory, statistics,
 * and philosophy for minimizing the possible loss for a worst case (maximum loss) scenario.
 * When dealing with gains, it is referred to as "maximin"—to maximize the minimum gain.
 * Originally formulated for two-player zero-sum game theory, covering both the cases where players take
 * alternate moves and those where they make simultaneous moves, it has also been extended to more
 * complex games and to general decision-making in the presence of uncertainty.
 * 
 * @author [Gleison Batista](https://github.com/gleisonbs)
 * @author [David Leal](https://github.com/Panquesito7)
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <array>

/** 
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * Check which number is the maximum/minimum in the array
 * @param depth current depth in game tree
 * @param node_index current index in array
 * @param is_max if current index is the longest number
 * @param scores saved numbers in array
 * @param height maximum height for game tree
 * @return maximum or minimum number
 */
template <size_t T>
int minimax(int depth, int node_index, bool is_max,
            const std::array<int, T> &scores, double height) {
    if (depth == height) {
        return scores[node_index];
    }

    int v1 = minimax(depth + 1, node_index * 2, !is_max, scores, height);
    int v2 = minimax(depth + 1, node_index * 2 + 1, !is_max, scores, height);

    return is_max ? std::max(v1, v2) : std::min(v1, v2);
}
} // namespace backtracking

/**
 * Main function
 */
int main() {
    std::array<int, 8> scores = {90, 23, 6, 33, 21, 65, 123, 34423};
    double height = log2(scores.size());

    std::cout << "Optimal value: " << backtracking::minimax(0, 0, true, scores, height)
              << std::endl;
    return 0;
}
