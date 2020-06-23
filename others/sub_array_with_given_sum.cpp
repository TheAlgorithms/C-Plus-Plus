/**
 * Copyright 2020 @author omkarlanghe
 *
 * @file
 * Given an unsorted array A of size N of non-negative integers,
 * find a continuous sub-array which adds to a given number S, If not found print -1.
 *
 * Input:
    3
    5 12
    1 2 3 7 5
    5 123
    1 2 3 7 5
    10 15
    1 2 3 4 5 6 7 8 9 10
* Output:
    2 4
    -1
    1 5
* Explanation :
    Testcase1: sum of elements from 2nd position to 4th position is 12. (consider 1 based indexing)
    Testcase2: no subarray found whose sum equals to the given sum, hence print -1.
    Testcase3: sum of elements from 1st position to 5th position is 15. (consider 1 based indexing)
*/

#include <iostream>

/**
 * Function to print the index range of subarray equal to the given sum. If no
 * such subarray found, print -1.
 * @param arr array to check
 * @param size size of an array
 * @param original_sum sum to match with the sum of all elements of a sub array.
 * @return void and prints index ranges if sum of sub array equal to the given
 * sum, else prints -1.
 */
template<typename T>
void contiguous_sub_array(T *arr, T size, T orignal_sum) {
    int current_sum = 0, match = 0;

    for (T i = 0; i < size; i++) {
        current_sum = 0;
        for (T j = i; j < size; j++) {
            current_sum += arr[j];
            if (current_sum == orignal_sum) {
                match = 1;
                std::cout << (i + 1) << " " << (j + 1) << " ";
                break;
            } else if (current_sum > orignal_sum) {
                current_sum = 0;
                break;
            }
        }
        if (match) {
            break;
        }
    }
    if (match == 0) {
        std::cout << -1 << " ";
    } else {
        match = 0;
    }
}

/**
 * Main function
 */
int main() {
    int test_cases, size, orignal_sum;

    std::cout << "Enter test cases : " << std::endl;
    std::cin >> test_cases;

    while (test_cases--) {
        std::cout << "Enter size of an array : " << std::endl;
        std::cin >> size;

        std::cout << "Enter the sum to check : " << std::endl;
        std::cin >> orignal_sum;

        // dynamic memory allocation.
        int *arr = new int[size];

        std::cout << "Enter the elements in an array : " << std::endl;
        for (int i = 0; i < size; i++) {
            std::cin >> arr[i];
        }

        contiguous_sub_array(arr, size, orignal_sum);

        std::cout << std::endl;
        // free memory of an array once used.
        delete[] arr;
    }
    return 0;
}
