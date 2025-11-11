#include <bits/stdc++.h>
using namespace std;

/*
Kadane's Algorithm (with index tracking)
Time Complexity: O(n)
*/

pair<int, pair<int, int>> kadane_with_indices(const vector<int>& arr) {
    int max_sum = INT_MIN;
    int current_sum = 0;
    int start = 0, temp_start = 0, end = 0;

    for (int i = 0; i < arr.size(); i++) {
        current_sum += arr[i];

        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }

        if (current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
    return {max_sum, {start, end}};
}

int main() {
    vector<int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};

    auto result = kadane_with_indices(arr);
    cout << "Maximum Subarray Sum: " << result.first << "\n";
    cout << "Start Index: " << result.second.first << "\n";
    cout << "End Index: " << result.second.second << "\n";

    return 0;
}
