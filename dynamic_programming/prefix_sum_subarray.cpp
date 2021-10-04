/*
Prefix Subarray sum approach to find the greatest subarray sum.
This approach has a time complexity of O(n^2)
In this approach we create an array that calculates the cumulative sum at every corresponding index of the given array in input.
For example the input array is 1,2,3,4,-2(arr array in the given code)
The new array that shall store the corresponding cumulative sums at each index will be 1,3,6,10,8 (prefix array in given code)
Now the next step involves 2 nested for loops, that operate in order to find the highest difference between 2 elements of the new array formed(prefix array in code).
*/
#include <array>
#include <climits>
#include <iostream>
using namespace std;
// Prefix Sum Approach O(N^2)
int largestSubarraySum(int arr[], int n) {
    // Prefix Sums
    int prefix[100];//defining the array that shall store the cumulative sums of elements to the corresponding index values
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];//function to find the cumulative sum upto a given index
    }
    // largest sum logic
    int largest_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int subarraySum = i > 0 ? prefix[j] - prefix[i - 1] : prefix[j]; //if i>0 prefix[j]-prefix[i-1] else prefix[j]
            // put a check if subarraySum > largest_sum
            largest_sum = max(largest_sum, subarraySum); // greter of largest_sum and subarraySum is the updated largest_sum
        }
    }
    return largest_sum;
}
int main() {
    int arr[1000], n;
    cin >> n;//Input size of array
    for (int i = 0; i < n; i++) {
        cin >> arr[i];//input array element
    }
    cout << largestSubarraySum(arr, n) << endl;//print largest sum of subarray
    return 0;
}