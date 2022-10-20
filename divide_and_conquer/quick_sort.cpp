/**
 * @file QuickSort.cpp
 * @brief Implementation of [Quick Sort] using two different partitioning algorithms
 * (https://en.wikipedia.org/wiki/Quicksort)
 *
 * @details
 * Given n integers, you need to sort these n integers in non-decreasing order. Equal array
 * elements in the sorted array need not be in the same order as they appear in the
 * original array. In other words, stability of the algorithm is not required.
 *
 * ### Algorithm
 * It works by selecting a 'pivot' element from the array and partitioning the other elements
 * into two sub-arrays, according to whether they are less than or greater than the pivot.
 * The sub-arrays are then sorted recursively.
 * This can be done in-place, requiring small additional amounts of memory to perform the sorting.
 *
 * @author [Shivanshu](https://github.com/ShivanshuKGupta)
 */

#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Prints values stored in a vector separated by spaces
 *
 * @tparam LL type of elements in the vector for example, int, long
 * @param out refrence to an object of ostream (std::cout in our case)
 * @param arr array of elements of type LL (integers in our case)
 * @return std::ostream& for cascading of extraction operator
 */
template <typename LL>
std::ostream &operator<<(std::ostream &out, std::vector<LL> &arr)
{
    for (auto &x : arr)
        out << x << ' ';
    return out;
}

/**
 * @brief Takes input integer from stdin for every element in the std::vector
 *
 * @tparam LL type of elements in the vector
 * @param in refrence to an object of istream (std::cin in our case)
 * @param arr array of elements of type LL (integer in our case)
 * @return std::istream& for cascading of insertion operator
 */
template <typename LL>
std::istream &operator>>(std::istream &in, std::vector<LL> &arr)
{
    for (auto &x : arr)
        in >> x;
    return in;
}

/**
 * @brief Hoare Partition Scheme
 * (https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme)
 *
 * @details uses two pointers (indices into the range) that start at both ends of the sub-array being partitioned,
 * then move toward each other, until they detect an inversion: a pair of elements, one greater than the bound
 * at the first pointer, and one less than the bound at the second pointer, then they are exchanged. After
 * this the pointers are moved inwards, and the search for an inversion is repeated; eventually the pointers
 * cross (the first points after the second) and the partitioning algorithm stops.
 * @param arr array of integers
 * @param l lower pointer/index from where the partitioning algorithm should start (inclusive)
 * @param h upper pointer/index till where the partitioning algorithm should do the partitioning (inclusive)
 * @return the index of the boundary of the partition
 */
int hoarePartition(std::vector<int> &arr, int l, int h)
{
    int pivot = arr[l], i = l - 1, j = h + 1;
    while (1)
    {
        while (arr[++i] < pivot)
            ;
        while (arr[--j] > pivot)
            ;
        if (i >= j)
            break;
        std::swap(arr[i], arr[j]);
    }
    return j;
}

/**
 * @brief Lomuto Partition Scheme
 * (https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme)
 *
 * @details This scheme chooses as the pivot the last element in the array. The algorithm maintains index k
 * as it scans the array using another index i such that the elements at l(low) through k-1 (inclusive) are
 * less than the pivot, and the elements at k through i (inclusive) are equal to or greater than the pivot.
 * @param arr array of integers
 * @param l lower pointer/index from where the partitioning algorithm should start (inclusive)
 * @param h upper pointer/index till where the partitioning algorithm should do the partitioning (inclusive)
 * @return k After the partitioning the elements at l through k-1 (inclusive) are smaller than the pivot.
 */
int lomutoPartition(std::vector<int> &arr, int l, int h)
{
    int pivot = arr[h], k = l;
    for (int i = l; i <= h; i++)
        if (arr[i] < pivot)
            std::swap(arr[i], arr[k++]);
    std::swap(arr[k], arr[h]);
    return k;
}

// Does Quick Sort using Lomuto's Parition
void quickSortLomuto(std::vector<int> &arr, int low, int high)
{
    while (low < high)
    {
        int pi = lomutoPartition(arr, low, high);
        quickSortLomuto(arr, low, pi - 1);
        low = pi + 1;
        // Instead of calling the QuickSort Function Again,
        // we use the same function but now with a different lower index
    }
}

// Does Quick Sort using Hoare's Partition
void quickSortHoare(std::vector<int> &arr, int low, int high)
{
    while (low < high)
    {
        int pi = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pi); // the pivot is now included
        low = pi + 1;
        // Instead of calling the QuickSort Function Again,
        // we use the same function but now with a different lower index
    }
}

std::vector<int> testLomuto(std::vector<int> arr)
{
    quickSortLomuto(arr, 0, arr.size() - 1);
    std::cout << "Array sorted with lomuto Partition: " << arr << std::endl;
    return arr;
}

std::vector<int> testHoare(std::vector<int> arr)
{
    quickSortHoare(arr, 0, arr.size() - 1);
    std::cout << "Array sorted with Hoare Partition : " << arr << std::endl;
    return arr;
}

int main()
{
    // Test Set 1
    std::vector<int> arr = {5, 3, 6, 4, 7, 3, 1};
    std::vector<int> sortedArr = {1, 3, 3, 4, 5, 6, 7};
    std::cout << "Original Array: " << arr << std::endl;
    assert(sortedArr == testLomuto(arr));
    assert(sortedArr == testHoare(arr));

    // Test Set 2
    arr = {4, 2, 6, 5, 3, 9};
    sortedArr = {2, 3, 4, 5, 6, 9};
    std::cout << "\nOriginal Array: " << arr << std::endl;
    assert(sortedArr == testLomuto(arr));
    assert(sortedArr == testHoare(arr));

    return 0;
}