// Linear Search
// Time Complexity: O(n)
// Space Complexity: O(1)

#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int target) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == target)
            return i;
    }
    return -1;
}

int main() {
    int arr[] = {5, 3, 8, 4, 2};
    int n = 5;
    int target = 4;

    int result = linearSearch(arr, n, target);
    if(result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";
}
