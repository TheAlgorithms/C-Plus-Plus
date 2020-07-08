/**
 * @file
 * @brief returns which is the longest/shortest number, using minimax algorithm
 *
 * Wikipedia: https://en.wikipedia.org/wiki/Minimax
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

/**
 * Check which number is the maximum/minimum in the array
 * @param depth depth of array
 * @param node_index current index in array
 * @param is_max if current index is the longest number
 * @param scores saved numbers in vector
 * @return if maximum or not
 */
int minimax(int depth, int node_index, bool is_max, const std::vector<int> &scores,
            int height) {
    if (depth == height) {
        return scores[node_index];
    }

    int v1 = minimax(depth + 1, node_index * 2, !is_max, scores, height);
    int v2 = minimax(depth + 1, node_index * 2 + 1, !is_max, scores, height);

    return is_max ? std::max(v1, v2) : std::min(v1, v2);
}

/**
 * Main function
 */
int main() {
    std::vector<int> scores = {90, 23, 6, 33, 21, 65, 123, 34423};
    int height = log2(scores.size());

    std::cout << "Optimal value: " << minimax(0, 0, true, scores, height) << std::endl;
    return 0;
}
