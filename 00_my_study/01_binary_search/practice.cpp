#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
uint64_t binarySearch(const vector<long long>& arr, uint64_t val) {
    uint64_t low = 0;
    uint64_t high = arr.size() - 1;

    while (low <= high) {
        long long m = low + (high - low) / 2;
        if (arr[m] == val) {
            return m;
        } else if (val < arr[m]) {
            high = m - 1;
        } else {
            low = m + 1;
        }
    }
    return -1;
}

int main() {
    vector<long long> v = {1, 2, 3, 4, 5 , 6 , 7};
    sort(v.begin(), v.end());
    int val = 2;
    uint64_t expected_ans = 1;
    uint64_t res = binarySearch(v, val);
    cout << res << " " << expected_ans << "\n";
    assert(res == expected_ans);
    cout << "Pass!\n";
    return 0;
}