#include <climits>
#include <iostream>
using namespace std;
// Function for maximum subarray
int maxSubArray(int arr[], int size) {
    int curr_sum = 0;
    int max_sum = INT_MIN;
    for (int i = 0; i < size; i++) {
        curr_sum += arr[i];
        max_sum = max(max_sum, curr_sum);
        curr_sum = max(curr_sum, 0);
    }
    return max_sum;
}
int main() {
    int n, i;
    cout << "Enter the number of elements \n";
    cin >> n;
    int a[n];
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    int max_sum = maxSubArray(a, n);
    cout << "Maximum subarray sum is " << max_sum;
    return 0;
}
