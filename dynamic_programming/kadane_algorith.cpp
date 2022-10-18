#include <bits/stdc++.h>
using namespace std;

int kadane(vector<int>& arr, int n) {
    int sum = 0, maxSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
        maxSum = max(sum, maxSum);
        if (sum < 0)
            sum = 0;
    }
    return maxSum;
}
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Maximum Subarray sum: " << kadane(arr, n);
}