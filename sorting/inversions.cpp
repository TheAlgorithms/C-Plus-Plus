/**
 * @file
 * @brief [https://www.hackerrank.com/challenges/ctci-merge-sort/problem]
 * 
 * @details
 * An inversion_count indicates how far or close an array is from being sorted.
 * If array is already sorted then inversion count is 0. If array is sorted in reverse order 
 * then inversion count is the maximum. Two elements a[i] and a[j] form an inversion if a[i] > a[j]
 * and i < j
 * 
 * Example 1:
 * Input: arr[] = {9, 5, 3, 2}
 * Output: 6
 * Explanation: Given array has six inversions:
 * (9, 5), (5, 3), (9, 3), (9, 2), (5, 2), (3, 2).
 *
 * Example 2:
 * 
 * Input: arr[] = {4, 2, 3}
 * Output: 2
 * Explanation: Given array has two inversions:
 * (4, 2), (4, 3) 
 * @author [Amit Padaliya](https://github.com/amitqy)
 * 
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Function that takes array as a parameter, finds the mid index of 
 * the array and divides the array into two halves, it takes inspiration from 
 * the merge procedure of the merge sort algorithm. Merges two halves of the array
 * and while merging alsp counts the number of inversions.
 * @param *arr is a pointer to the array in which inversions are to be counted
 * @param start is the starting index of the array
 * @param end is the ending index of the array
 * @returns total number of inversions in the array and also sorts the array
 */

int merge(std ::vector<int> *arr, int start, int end)
{ // mid point of the array
    int mid = start + (end - start) / 2;
    // start of the first half of array
    int i = start;
    // start of the second half of array
    int j = mid + 1;
    int k = start;
    // making a temporary array for merging
    std ::vector<int> temp(1000000);
    // varible to store the inversion count
    int cnt = 0;
    //merging two haves
    while ((i <= mid) && (j <= end))
    {
        if (arr->at(i) <= arr->at(j))
        {
            temp[k] = arr->at(i);
            k++;
            i++;
        }
        // there is an inversion
        else
        {
            temp[k++] = arr->at(j++);
            cnt += mid - i + 1;
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr->at(i++);
    }

    while (j <= end)
    {
        temp[k++] = arr->at(j++);
    }
    for (int i = start; i <= end; i++)
    {
        // copy the elements back to the original array
        arr->at(i) = temp[i];
    }
    return cnt;
}

/**
 * @brief Function that takes array as a parameter, finds the mid point
 * and divides the array into two halves,Sorts two halves of the array recursively and also
 * counts the number of inversions during the process.
 * @param *arr is a pointer to the array in which inversions are to be counted
 * @param start is the starting index of the array
 * @param end is the ending index of the array
 * @returns total number of inversions in th array and also sorts the array
 */

int inversion_count(std ::vector<int> *arr, int start, int end)
{

    if (start >= end)
    {
        return 0;
    }
    // initialize the inverision count.
    int inv_count = 0; 
    int mid = start + (end - start) / 2;
    // count number of inverisons while sorting left half recursively
    inv_count += inversion_count(arr, start, mid);  
    // count number of inverisons while sorting right half recursively
    inv_count += inversion_count(arr, mid + 1, end);
    // merge both halves together and add the inversion count
    inv_count += merge(arr, start, end);            
    return inv_count;
}

/**
 * @brief Test implementations
 * @returns void
 */

static void test()
{
    std::vector<int> arr = {9, 5, 3, 2};
    // should return 6 as number of inversions are (9, 5), (5, 3), (9, 3), (9, 2), (5, 2), (3, 2)
    assert((inversion_count(&arr, 0, 3) == 6));
    // as the inversion algorithm also sorts the array, setting the array to its prev form.
    arr = {9, 5, 3, 2};
    std ::cout << inversion_count(&arr, 0, 3) << std::endl;
    std::cout << "Test implementation passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main()
{
    test(); // call the test function :)
    //input array
    std::vector<int> arr = {9, 5, 3, 2};
    // should return and output 6 a as number of inversions are (9, 5), (5, 3), (9, 3), (9, 2), (5, 2), (3, 2)
    std ::cout << inversion_count(&arr, 0, 3) << std::endl;
    return 0;
}
