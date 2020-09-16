#include <climits>
#include <iostream>

// Function for maximum subarray
int maxSubArray(int arr[], int size) {
    int curr_sum = 0;
    int max_sum = INT_MIN;
    for (int i = 0; i < size; i++) {
        curr_sum += arr[i];
        max_sum = std::max(max_sum, curr_sum);
        curr_sum = std::max(curr_sum, 0);
    }
    return max_sum;
}
int main() {
    int n, i;
    std::cout << "Enter the number of elements \n";
    std::cin >> n;
    int a[n];
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int max_sum = maxSubArray(a, n);
    std::cout << "Maximum subarray sum is " << max_sum;
    return 0;
}
