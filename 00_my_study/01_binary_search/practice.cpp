#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
uint64_t binarySearch(vector<long long>& arr, long long val) {
    uint64_t low = 0;
    uint64_t high = arr.size() - 1;

    while (low <= high) {
        
        uint64_t m = low + (high - low) / 2;
        if (val == arr[m]) {
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
    vector<long long> v = {1, 2, 3, 4, 5};
    int val = 2;
    int expected_ans = 1;
    uint64_t res = binarySearch(v, val);
    assert(res == expected_ans);
    cout << "Pass!\n";
    return 0;
}