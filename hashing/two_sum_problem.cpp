// C++ program to check if given array
// has 2 elements whose sum is equal
// to the given value using hashing technique
#include <bits/stdc++.h>
 
using namespace std;
 
void print_pairs(int arr[], int arr_size, int sum)
{
    unordered_set<int> s;
    for (int i = 0; i < arr_size; i++) {
        int temp = sum - arr[i];
 
        if (s.find(temp) != s.end()) {
            cout << "Yes" << endl;
            return;
        }
        s.insert(arr[i]);
    }
    cout << "No" << endl;
}
 
/* Driver Code */
int main()
{
    int A[] = { 1, 4, 45, 6, 10, 8 };
    int n = 16;
    int arr_size = sizeof(A) / sizeof(A[0]);
 
    // Function calling
    print_pairs(A, arr_size, n);
 
    return 0;
}

// Input: arr[] = {1, -2, 1, 0, 5}, x = 0
// Output: No
