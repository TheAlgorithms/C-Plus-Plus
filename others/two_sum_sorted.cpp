/**
 * @file
 * @brief Two sum problem using two pointers
 */

#include <cassert>
#include <iostream>
#include <vector>

namespace others {

std::pair<int, int> two_sum_sorted(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target)
            return {left, right};
        else if (sum < target)
            left++;
        else
            right--;
    }

    return {-1, -1};
}

}  // namespace others

static void test() {
    std::vector<int> arr = {1, 2, 3, 4, 6};
    auto res = others::two_sum_sorted(arr, 6);

    assert(res.first == 1);
    assert(res.second == 3);

    std::cout << "Tests passed\n";
}

int main() { test(); }