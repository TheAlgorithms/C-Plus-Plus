/*
A C++ (CPP) code to find how many subarrays ( contiguous part of an array) are present in an array whose product is less than a
 given number 'k'
 e.g.-
  Input array -  arr[5]= {1, 3, 4 ,5 ,2}
  Input No.   -   k = 5
  Subarrays of arr having product less than (k=5) are - {1} , {3} , {4} , {2} , {1 , 3}
*/

/*
Idea - Use Sliding Window Algorithm
Procedure -
Go in a loop ( j=0 to n) and create a sliding window each time starting from current element and increase its size (in second loop)
till both of these  conditions are true  ( product of all elemnts in the window < k and iterator < last_index )
Proof -
 If at any instance , the product of all elements in the current window (subarray) exceeds k , then all further windows's product>k
 and hence we shift to the element to immediate right and do the same process .
*/

// Time Complexity of Code - O (n ^2 )  since outer loop -> n times and inner loop (worst case ) -> n times so TC = n * n 
// Space Complexity of Code - O (1)  since does not use any auxillary space 

// Implementation

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Solution {

    // required function
    // Arguments = a[] -> array , n -> size of array , k -> given counter(number)
    int count_SubArray_Product_Less_Than_K(int a[], int n , int k ) {
        // Actual answer
    int ans = 0;
    
    for (int j = 0; j < n; j++)
    {
        // traverse  each element
        int i = j;

        // initialize the product as 1 for current window .

        long long int product = 1;

        // making  a window that is expanding continuously till (product < k) AND (counter variable < size of array) .
        while (i < n && product < k)
        {
            product *= a[i];
            if (product < k)
            {
                ans++;
                i++;
            }
        }
    }

    return ans;
    }
};

void test() {
    Solution solution;
    
    // Test case 1
    int a1[4] = {1, 3, 4, 2};
    int k1 = 5;
    int expected1 = 5;
    int result1 = solution.count_SubArray_Product_Less_Than_K(a1,4, k1);
    assert(result1 == expected1);

    // Test case 2
    int a2[5] = {1, 2, 3, 4, 5};
    int k2 = 10;
    int expected2 = 8;
    int result2 = solution.count_SubArray_Product_Less_Than_K(a2,5, k2);
    assert(result2 == expected2);
    // Add more test cases here
    
    cout << "All tests passed successfully!" << endl;
}

int main() {
    test();
    
    return 0;
}

