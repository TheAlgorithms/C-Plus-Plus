/**
 * @file
 * @brief - Finds Total Number of Subarrays whose net product is less than a given Number = k 
(Source -https://leetcode.com/problems/subarray-product-less-than-k/ )


 * @description :
A C++ (CPP) code to find how many subarrays (contiguous part of an array) are
present in an array whose product is less than a given number 'k' 
e.g.- [ Input array -  arr[5]= {1, 3, 4 ,5 ,2} ] and  [ Input Number k = 5 ]
      Now Subarrays of arr having product less than (k=5) are - {1} , {3} , {4} , {2} , {1 , 3}

// Idea :
 Use Sliding Window Algorithm

// Procedure :
Go in a loop (j=0 to n) and create a sliding window each time starting from the
current element and increase its size (in the second loop) till both of these
conditions are true  (product of all elements in the window < k and iterator <
last_index) Proof - If at any instance, the product of all elements in the
current window (subarray) exceeds k, then all further windows' product > k and
hence we shift to the element to the immediate right and do the same process.

// Complexities  : 
. Time Complexity of Code - O(n^2) since the outer loop -> n times and inner
loop (worst case) -> n times so TC = n * n .
. Space Complexity of Code - O(1) ->  since it does not use any auxiliary space

 * @author - [Aryan Arya] https://github.com/hecker1002

 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

// Implementation

struct Solution {
    /**
     * @brief - Finds Total Number of Subarrays in which the product of elements  present in the subarray is less than a given Number = k
     * @param a the array to be used
     * @param n the size of the array
     * @param k the maximum product allowed for subarrays
     * @return the number of valid subarrays (int)
     *
     */

    // Required function -
    int count_SubArray_Product_Less_Than_K(int a[], int n, int k) {
        // Actual answer
        int ans = 0;

        // loop starts s
        for (int j = 0; j < n; j++) {
            // traverse each element
            int i = j;

            // and with respect to current element of array , initialize the
            // window of size =1.
            long long int product = 1;

            // expanding a window continuously till (product of elements in
            // current window  < k) AND (iterator < last index of array). if any
            // of these above conditions vio,ated , break the loop and count all
            // the valid subarrays till now.
            while (i < n && product < k) {
                product *= a[i];

                // checking if product in current window do NOT excedd k .
                if (product < k) {
                    ans++;  // if NOT , inccrease the no . pf valid subarrays
                    i++;  // expand the window with respect to current element .
                }

            }  // loop ends
        }

        return ans;  // return no. of valid subarrays as the final answer
    }
};

/**
 * @brief Self-test implementation
 */

void test() {
    Solution solution;

    // Test case 1
    int a1[4] = {1, 3, 4, 2};
    int k1 = 5;
    int expected1 = 5;
    int result1 = solution.count_SubArray_Product_Less_Than_K(a1, 4, k1);
    assert(result1 == expected1);

    // Test case 2
    int a2[5] = {1, 2, 3, 4, 5};
    int k2 = 10;
    int expected2 = 8;
    int result2 = solution.count_SubArray_Product_Less_Than_K(a2, 5, k2);
    assert(result2 == expected2);

    // You can add more test cases here.

    std::cout << "All tests passed successfully!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    test();  // runs self-implemented tests

    return 0;
}
