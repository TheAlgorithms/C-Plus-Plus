/*Kadane's algorithm is used to find the largest subarray sum in any given array.
Time Complexity-O(n)
Functioning- Initially the largest_sum and current_sum are initialized to 0,
then we basically calculate running sum from left to right
and at any point if the current sum is negative we assume it to be zero,
with every maximum achieved in current_sum the maximum_sum gets updated*/
#include <array>
#include <climits>
#include <iostream>
using namespace std;

int max_subarray_sum(int arr[], int n) {
    int current_sum = 0;//initializing current_sum to 0
    int largest_sum = 0;//initializing largest_sum to 0

    for (int i = 0; i < n; i++) {
        current_sum = current_sum + arr[i];
        if (current_sum < 0) {
            current_sum = 0;
        }
        largest_sum = max(largest_sum, current_sum);//the greater of largest_sum, current_sum is assigned as the largest_sum
    }

    return largest_sum;
}

int main() {
    int arr[20],n; //array initialization, number of elements initialization  
    cin >> n; //number of elements in array input from user
    for (int i = 0; i < n;i++){ //array elements input from user
        cin >> arr[i];
    }
    cout << max_subarray_sum(arr, n) << endl;//print output

    return 0;
}