#include <iostream>
using namespace std;

// Binary search function
int bs(int arr[], int s, int e, int t)
{
    // Base case: If the start index is greater than the end index, the element is not in the array
    if (s > e) 
        return -1; // Return -1 to indicate that the element was not found
    
    // Calculate the middle index
    int mid = s + (e - s) / 2;

    // If the middle element is equal to the target element, return its index
    if (arr[mid] == t)
        return mid;
    
    // If the middle element is greater than the target element, search in the left half
    else if (arr[mid] > t)
        return bs(arr, s, mid - 1, t);
    
    // If the middle element is less than the target element, search in the right half
    else // arr[mid] < t
        return bs(arr, mid + 1, e, t);
}

// Function to test binary search
void testBinarySearch(int arr[], int n, int target)
{
    int s = 0, e = n - 1; // Initialize the start and end indices

    int result = bs(arr, s, e, target);

    if (result != -1)
        cout << "Element " << target << " found at index " << result << endl;
    else
        cout << "Element " << target << " not found\n";
}

int main()
{
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 21};
    int n = sizeof(arr) / sizeof(arr[0]); // Calculate the number of elements in the array
    
    // Test cases
    int target1 = 12;
    int target2 = 6;
    int target3 = 9;
    
    cout << "Test Case 1: Searching for 12\n";
    testBinarySearch(arr, n, target1);
    
    cout << "Test Case 2: Searching for 6\n";
    testBinarySearch(arr, n, target2);
    
    cout << "Test Case 3: Searching for 9\n";
    testBinarySearch(arr, n, target3);
    
    return 0;
}
