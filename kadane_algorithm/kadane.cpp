#include <array>
#include <climits>
#include <iostream>

int maxSubArray(const std::array<int, 5> &n) {
    int curr_sum = 0;
    int max_sum = INT_MIN;
    for (int i = 0; i < n.size(); i++) {
        curr_sum += n[i];
        max_sum = std::max(max_sum, curr_sum);
        curr_sum = std::max(curr_sum, 0);
    }
    return max_sum;
}
int main() {
    std::array<int, 5> n;

    // taking values of elements from user
    for (int i = 0; i < n.size(); i++) {
        std::cout << "Enter value of n[" << i << "]"
                  << "\n";
        std::cin >> n[i];
    }
    int max_sum = maxSubArray(n);
    std::cout << "Maximum subarray sum is " << max_sum;

    return 0;
}