/**
 * @file recursive_bubble_sort.cpp
 * @author Aditya Prakash (adityaprakash.tech)
 * @brief This is an implementation of recursive version of Bubble sort
algorithm
 *
 * @details
 * The working principle of the Bubble sort algorithm:

Bubble sort is a simple sorting algorithm used to rearrange a set of elements in
ascending or descending order. Bubble sort gets its name from the fact that data
"bubbles" to the top of the dataset.

 * What is Swap?

To swap two numbers mean that we interchange their values.
An additional variable is required for this operation. x = 5, y = 10.
We want x = 10, y = 5. Here we create the most variable to do it.

int z;
z = x;
x = y;
y = z;

The above process is a typical displacement process.
When x assigns the value to x, the old value of x is lost.
That's why we created a variable z to create the first value of the value of x,
and finally, we have assigned to y.

 * Recursion

While the recursive method does not necessarily have advantages over iterative
versions, but it is useful to enhance the understanding of the algorithm and
recursion itself. In Recursive Bubble sort algorithm, we firstly call the
function on the entire array, and for every subsequent function call, we exclude
the last element. This fixes the last element for that sub-array.Formally, for
`ith` iteration, we consider elements up to n-i, where n is the number of
elements in the array. Exit condition: n==1; i.e. the sub-array contains only
one element.

 * Complexity
    Time complexity: O(n) best case; O(n²) average case; O(n²) worst case
    Space complexity: O(n)

We need to traverse the array `n * (n-1)` times. However, if the entire array is
already sorted, then we need to traverse it only once. Hence, O(n) is the best case
complexity
*/

#include <iostream>  //for io operations
#include <vector>    //for std::vector

/*
 *   The following function, i.e. swap takes two values by address, and
 *   derefences them so that the changes are reflected outside the scope
 *   of the function. This function employs a third variable, namely
 *   `temp` to swap the values of `x` and `y`
 */

void swap(int *x, int *y) {
    int temp = *x;  //!< dereferencing pointer to `x` and assigning it to `temp`
    *x = *y;
    *y = temp;
}

void recursive_bubble_sort(std::vector<int> *nums, int n) {
    if (n == 1) {  //!< base case; when size of the array is 1
        return;
    }

    for (int i = 0; i < n - 1; i++) {  //!< iterating over the entire array
        //!< if a larger number appears before the smaller one, swap them.
        if ((*nums)[i] > (*nums)[i + 1]) {
            swap(&(*nums)[i], &(*nums)[i + 1]);
        }
    }

    //!< calling the function after we have fixed the last element
    recursive_bubble_sort(nums, n - 1);
}
}

int main() {
    int n = 0;
    bool swap_check = true;
    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> n;  //!< size of the array
    std::vector<int> numbers;
    std::cout << "Enter " << n << " numbers: ";
    int num = 0;

    // Input
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        numbers.push_back(num);
    }
    std::cout << std::endl;

    // Example 2. Creating array of doubles.
    std::cout << "Test 2 using doubles\n";
    std::vector<double> double_arr;

    double_arr.push_back(20.4);
    double_arr.push_back(62.7);
    double_arr.push_back(12.2);
    double_arr.push_back(43.6);
    double_arr.push_back(74.1);
    double_arr.push_back(57.9);

    sorting::recursive_bubble_sort(&double_arr, size);
    assert(std::is_sorted(std::begin(double_arr), std::end(double_arr)));
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;

}

/**
 * @brief main method to run the program
 * 
 * @return int 
 */
int main() { 
    test();
    return 0;
}

