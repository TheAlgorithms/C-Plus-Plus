/**
 * @file
 * @brief Efficient implemention for maximum contiguos subarray sum by kadane's algorithm.
 * @details
 * Our task is to take length of array and then the whole array as input from
 * the user and then calculate the maximum contiguos subarray sum for the 
 * input array, using the kadane's algorithm. 
 * 
 * reference article : https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
 * 
 * There can be a case that all the elements in the input array are negative. 
 * In that case, the least value among all elements is the maximum sum with subarray 
 * length = 1.
 * @author [Abhijeet Tiwari](https://github.com/thisabhijeet)
 */

#include <cassert>  // for assert
#include <iostream> // for io operations
#include <climits>  // for INT_MIN value
using namespace std;

/** max_subarray_sum function
 * \param arr input array 
 * \param length length of the input array
 * \returns maximum contiguous subarray sum
 */

int max_subarray_sum(int arr[], int length)
{
    int current_max = INT_MIN, current_sum = 0;
    for (int i = 0; i < length; i++)
    {
        current_sum = current_sum + arr[i];
        if (current_max < current_sum)
        {
            current_max = current_sum;
        }

        if (current_sum < 0)
        {
            current_sum = 0;
        }
    }
    return current_max;
}

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test()
{
    int arr[4] = {1, 2, 3, 4};
    int arr1[5] = {-1, -2, -4, -6, 7};
    assert(max_subarray_sum(arr, 4) == 10);
    assert(max_subarray_sum(arr1, 5) == 7);
    cout << "all test cases passed!";
}

/** main function */
int main()
{ // Below is the code for accepting array from user and then calling
    // the function for the required output.
    // It has been commented for now so that the test() function can run
    // and test cases can be verified.
    // code for accepting array from user starts

    // int n; // variable for length of input array
    // cout << "Enter length of the array: ";
    // cin >> n;
    // int arr[n];
    // for (int i = 0; i < n; i++) // taking input of each element of the array
    // {
    //     cin >> arr[i];
    // }
    // int max_sum = max_subarray_sum(arr, n);
    // cout << "Maximum contiguous sum for this array is : " << max_sum << endl;

    // code for accepting array from user ends
    test();
    return 0;
}