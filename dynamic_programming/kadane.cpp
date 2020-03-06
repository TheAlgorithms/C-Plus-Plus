#include<iostream>
#include<climits>

int maxSubArraySum(int a[], int size) {
    int max_so_far = INT_MIN, max_ending_here = 0;

    for (int i = 0; i < size; i++) {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}


int main() {
    int n, i;
    std::cout << "Enter the number of elements \n";
    std::cin >> n;
    int a[n];  // NOLINT
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int max_sum = maxSubArraySum(a, n);
    std::cout << "Maximum contiguous sum is " << max_sum;
    return 0;
}
