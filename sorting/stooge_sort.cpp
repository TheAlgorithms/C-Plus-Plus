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
#include <iostream> /// for cout

/**
 * The stoogeSort() function is used for sorting the array.
 *
 * @param L - vector of values (int) to be sorted in in place (ascending order)
 * @param i - the first index of the array (0)
 * @param j - the last index of the array (L.size() - 1)
 */
void stoogeSort(std::vector<int> *L, int i, int j) {
	if (i < j) {
		if ((*L)[i] > (*L)[j]) {	
			std::swap((*L)[i], (*L)[j]);
		}
		if (j - i > 1) {
			int third = (j - i + 1) / 3;
			stoogeSort(L, i, j - third);
			stoogeSort(L, i + third, j);
			stoogeSort(L, i, j - third);
		}
	}
	return;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main() {
	std::vector<int> L = { 8, 9, 10, 4, 3, 5, 1 };
	stoogeSort(&L, 0, L.size() - 1);
	std::cout << "Sorted array:" << std::endl;
	for (int i = 0; i < L.size(); i++) {
		std::cout << L[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
