/**
 * @file
 * @brief [Stooge sort implementation](https://en.wikipedia.org/wiki/Stooge_sort)
 * in C++
 * @details
 * Stooge sort is a recursive sorting algorithm.
 * It divides the array into 3 parts and proceeds to:
 *	- sort first two thirds of the array
 *	- sort last two thirds of the array
 *  - sort first two thirds of the array
 * It's time complexity is O(n^(log3/log1.5)), which is about O(n^2.7),
 * which makes it to be not the most efficient sorting algorithm
 * on the street on average. Space complexity is O(1).
 */

#include <vector> /// for vector
#include <cassert> /// for assert
#include <algorithm>  /// for std::is_sorted
#include <iostream>   /// for IO operations

 /**
  * @brief The stoogeSort() function is used for sorting the array.
  * @param L - vector of values (int) to be sorted in in place (ascending order)
  * @param i - the first index of the array (0)
  * @param j - the last index of the array (L.size() - 1)
  * @returns void
  */
void stoogeSort(std::vector<int>* L, size_t i, size_t j) {
    if (i >= j) {
        return;
    }
    if ((*L)[i] > (*L)[j]) {
        std::swap((*L)[i], (*L)[j]);
    }
    if (j - i > 1) {
        size_t third = (j - i + 1) / 3;
        stoogeSort(L, i, j - third);
        stoogeSort(L, i + third, j);
        stoogeSort(L, i, j - third);
    }
}

/**
 * @brief Function to test sorting algorithm
 * @returns void
 */
void test1() {
	std::vector<int> L = { 8, 9, 10, 4, 3, 5, 1 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Function to test sorting algorithm, one element
 * @returns void
 */
void test2() {
	std::vector<int> L = { -1 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Function to test sorting algorithm, repeating elements
 * @returns void
 */
void test3() {
	std::vector<int> L = { 1, 2, 5, 4, 1, 5 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main() {
	test1();
	test2();
	test3();
    
    std::cout << "All tests have successfully passed!\n";
	return 0;
}
