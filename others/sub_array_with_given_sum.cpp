/**
 * Copyright 2020 @author omkarlanghe
 *
 * @file
 * Given an unsorted array A of size N of non-negative integers,
 * find a continuous sub-array which adds to a given number S, If not found print -1.
 *
 * Sample Test casees input:
    5 12                        where 5 is the size of an array and 12 is the given number which is equal to total elements found in sub array.
    1 2 3 7 5                   space seperated integers representing elements of an array.
    5 123                       where 5 is the size of an array and 123 is the given number which is equal to total elements found in sub array.
    1 2 3 7 5                   space seperated integers representing elements of an array.
    10 15                       where 10 is the size of an array and 15 is the given number which is equal to total elements found in sub array.
    1 2 3 4 5 6 7 8 9 10        space seperated integers representing elements of an array.
* Sample Test cases output:
    2 4                         sum of elements from 2nd position to 4th position is 12 (consider 1 based indexing).
    -1                          no subarray found whose sum equals to the given sum, hence print -1.
    1 5                         sum of elements from 1st position to 5th position is 15 (consider 1 based indexing).

* Explanation :
    Testcase1: sum of elements from 2nd position to 4th position is 12 (consider 1 based indexing).
    Testcase2: no subarray found whose sum equals to the given sum, hence print -1.
    Testcase3: sum of elements from 1st position to 5th position is 15 (consider 1 based indexing).
*/

#include <iostream>
#include <cassert>
#include <vector>
/**
 * Function to print the index range of subarray equal to the given sum. If no
 * such subarray found, print -1.
 * @param arr array to check
 * @param size size of an array
 * @param original_sum sum to match with the sum of all elements of a sub array.
 * @return void and prints index ranges if sum of sub array equal to the given
 * sum, else prints -1.
 */
int contiguous_sub_array(int *arr, int size, int orignal_sum) {
    int current_sum = 0, match = 0;
    std::vector<int> ivec;
    for (int i = 0; i < size; i++) {
        current_sum = 0;
        for (int j = i; j < size; j++) {
            current_sum += arr[j];
            if (current_sum == orignal_sum) {
                match = 1;
                ivec.push_back((i + 1));
                ivec.push_back((j + 1));
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
        ivec.push_back(-1);
    } else {
        match = 0;
    }
    assert(ivec.size() > 1);
    for (int i = 0; i < ivec.size(); i++) {
        std::cout << ivec[i] << " ";
    }
    std::cout << std::endl;
    return (current_sum);
}

/**
 * Test cases to test the program
*/
void test() {
    std::cout << "Test 1" << std::endl;
    int arr1[] = {1, 2, 3, 7, 5};
    int original_sum = 12;
    int size = sizeof(arr1) / sizeof(arr1[0]);
    int result = contiguous_sub_array(arr1, size, original_sum);
    std::cout << "Test 1 passed\n ===================== \n";

    std::cout << "Test 2" << std::endl;
    int arr2[] = {5, 7, 2, 88, 266, 437};
    original_sum = 12;
    size = sizeof(arr2) / sizeof(arr2[0]);
    result = contiguous_sub_array(arr2, size, original_sum);
    std::cout << "Test 2 passed\n ===================== \n";

    std::cout << "Test 3" << std::endl;
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    original_sum = 15;
    size = sizeof(arr3) / sizeof(arr3[0]);
    result = contiguous_sub_array(arr3, size, original_sum);
    std::cout << "Test 3 passed\n ===================== \n";

    std::cout << "Test 4" << std::endl;
    int arr4[] = {15, 543, 2, 97, 43, 66, 87, 100, 298};
    original_sum = 208;
    size = sizeof(arr4) / sizeof(arr4[0]);
    result = contiguous_sub_array(arr4, size, original_sum);
    std::cout << "Test 4 passed\n ===================== \n";
}

/** Main function */
int main() {
    test();
    return 0;
}
