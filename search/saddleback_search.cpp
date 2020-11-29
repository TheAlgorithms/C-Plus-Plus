#include <cassert>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;

namespace search {
namespace saddleback {
pair<int, int> saddleback(vector<vector<int>> matrix, int element) {
    int left_index = 0;
    int right_index = matrix[0].size() - 1;
    while (left_index < matrix.size() && right_index >= 0) {
        if (element == matrix[left_index][right_index]) {
            return pair<int, int>(left_index, right_index);
        } else if (element > matrix[left_index][right_index]) {
            ++left_index;
        } else if (element < matrix[left_index][right_index]) {
            --right_index;
        }
    }
    return pair<int, int>(-1, -1);
}
}  // namespace saddleback
}  // namespace search

int main() {
    vector<vector<int>> matrix = {{1, 2, 3, 4, 5},
                                  {6, 7, 8, 9, 10},
                                  {11, 12, 13, 14, 15},
                                  {16, 17, 18, 19, 20},
                                  {21, 22, 23, 24, 25}};

    int opt = 0;
    while (opt != -1) {
        std::cin >> opt;
        pair<int, int> answer = search::saddleback::saddleback(matrix, opt);
        if (answer.first == -1 && answer.second == -1)
            std::cout << "No element";
        else
            std::cout << "Left = " << answer.first + 1
                      << " Right = " << answer.second + 1 << std::endl;
    }
}