#include <iostream>
using namespace std;

/*
Time Complexity

O(1):
Runs in constant time.
The algorithm runs in a fixed number of steps regardless of input size.
Examples: accessing an array element, simple operations.

O(log n):
Number of steps depends on how many times we divide n by 2.
Example: Binary Search.

O(sqrt(n)):
The loop runs until i * i <= n.
Example: checking divisors or prime numbers.

O(n):
The algorithm iterates over all elements once.

O(n log n):
Used in efficient sorting algorithms like Merge Sort and Quick Sort.

O(n^2):
Occurs in nested loops (comparing all pairs).

O(n^3):
Triple nested loops.

Polynomial Time:
O(n^k), where k is constant.

Exponential Time:
O(2^n): subsets, brute force recursion.
O(n!): permutations.

Note:
1 second ≈ 10^8 operations

O(1)       -> ∞
O(log n)   -> ∞
O(n)       -> 1e7
O(n log n) -> 1e6
O(n^2)     -> 2000
O(n^3)     -> 200
O(2^n)     -> 20
O(n!)      -> 10
*/

// Example: O(n^2)
void printPairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i] << " " << arr[j] << endl;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int n = 3;
    printPairs(arr, n);
    return 0;
}