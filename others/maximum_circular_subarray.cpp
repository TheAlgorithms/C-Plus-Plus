// C++ program for maximum contiguous circular sum problem
#include <iostream>
using namespace std;
  
// The function returns maximum circular contiguous sum in a[]

int maxCircularSum(int a[], int n)
{
    // Edge Case
    if (n == 1)
        return a[0];
  
    // Sum variable which store total sum of the array.
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
  
    // Every variable stores first value of the array.
    int current_max = a[0], max_so_far = a[0], current_min = a[0], min_so_far = a[0];
  
    // Concept of Kadane's Algorithm
    for (int i = 1; i < n; i++) {
        // Kadane's Algorithm to find Maximum subarray sum.
        current_max = max(current_max + a[i], a[i]);
        max_so_far = max(max_so_far, current_max);
  
        // Kadane's Algorithm to find Minimum subarray sum.
        current_min = min(current_min + a[i], a[i]);
        min_so_far = min(min_so_far, current_min);
    }
  
    if (min_so_far == sum)
        return max_so_far;
  
    // returning the maximum value
    return max(max_so_far, sum - min_so_far);
}
  
int main()
{
    int size;
    cout << "Enter size of array: ";
    cin >> size;
    int a[size];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
      cin >> a[i];
    }
    cout << "Maximum circular sum is " << maxCircularSum(a, size) << endl;
    return 0;
}
