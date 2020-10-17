
/* The Stooge sort is a recursive sorting algorithm. It is defined as below (for ascending order sorting):

Step 1 : If value at index 0 is greater than
         value at last index, swap them.
Step 2:  Recursively,
       a) Stooge sort the initial 2/3rd of the array.
       b) Stooge sort the last 2/3rd of the array.
       c) Stooge sort the initial 2/3rd again to confirm.

 **Always take the ceil of ((2/3)*N) for selecting elements.**

 Time Complexity:
 The running time complexity of stooge sort can be written as,
 T(n) = 3T(3n/2) + ?(1)
 Solution of above recurrence is O(n^(log3/log1.5)) = O(n^2.709)

 Space Complexity:
 O(1)
 */


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void stoogesort(int A[], int l, int h)
{
    if (l >= h)
        return;

    // If first element is smaller than last,
    // swap them
    if (A[l] > A[h])
        swap(A[l], A[h]);

    // If there are more than 2 elements in
    // the array
    if (h - l + 1 > 2) {
        int t = (h - l + 1) / 3;

        // Recursively sort first 2/3 elements
        stoogesort(A, l, h - t);

        // Recursively sort last 2/3 elements
        stoogesort(A, l + t, h);

        // Recursively sort first 2/3 elements
        // again to confirm
        stoogesort(A, l, h - t);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n; //Size of array

    int A[n];
    for (int i = 0; i < n; i++)
        cin >> A[i] ;

    // Calling Stooge Sort function to sort
    // the array
    stoogesort(A, 0, n - 1);

    // Display the sorted array
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";

    return 0;


}

/*
Sample input: 5
              3 2 1 5 4
Sample output: 1 2 3 4 5
*/