#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::vector;

int minimax(int depth, int node_index, bool is_max, vector<int> scores,
            int height) {
    if (depth == height)
        return scores[node_index];

    int v1 = minimax(depth + 1, node_index * 2, !is_max, scores, height);
    int v2 = minimax(depth + 1, node_index * 2 + 1, !is_max, scores, height);

    return is_max ? max(v1, v2) : min(v1, v2);
}

int main() {
    vector<int> scores = { 90, 23, 6, 33, 21, 65, 123, 34423 };
    int height = log2(scores.size());

    cout << "Optimal value: " << minimax(0, 0, true, scores, height) << endl;
}
