/**
 * @file
 * @brief brief one line description here
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int minimax(int depth, int node_index, bool is_max, std::vector<int> scores,
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
