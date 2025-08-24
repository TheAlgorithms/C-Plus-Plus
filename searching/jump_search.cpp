#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
 * @brief Performs Jump Search on a sorted vector.
 * 
 * @param arr The sorted vector to search in.
 * @param target The value to search for.
 * @return Index of target if found, else -1.
 */
int jump_search(const vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == target) return i;
    }

    return -1;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 13, 17, 21};
    int target = 13;
    int result = jump_search(arr, target);
    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found" << endl;
    return 0;
}
