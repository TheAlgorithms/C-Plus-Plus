/**
 *  \addtogroup sorting Sorting Algorithms
 *  @{
 *  \file
 *  \brief [Merege Sort Algorithm
 *  (MEREGE SORT)](https://en.wikipedia.org/wiki/Merge_sort) implementation
 *
 
 *
 *  \details
 *  Merge Sort is an efficient, general purpose, comparison
 *  based sorting algorithm.
 *  Merge Sort is a divide and conquer algorithm
 *
 */

#include<iostream>
using namespace std;

/* Preprocessor */
#define get_size(array) (sizeof((array))/sizeof((array[0])))

template<class t>
class sorting {
	t *list;
	public:
		sorting(t *data, int size) {
			list = data;
			
			/* Sorting data using merge sort algorithm */
			merge(0,size-1);
		}
    /**
 * Merge sort is a divide and conquer algorithm, it divides the
 * input array into two halves and calls itself for the two halves
 * and then calls merge() to merge the two halves
 *
 
 * @param low - left index or start index of array
 * @param high - right index or end index of array
 *
 */

		void merge(int low, int high) {
			int mid;
			if(low < high) {
				mid = (low + high) /2;
				merge(low, mid);
				merge(mid + 1, high);
				merge_sort(low, high, mid);
			}
		}

		void merge_sort(int low, int high, int mid) {
			t temp[10000007];
			int i = low, j, l = low, m = mid + 1;
			while(l <= mid && m <= high) {
				if(list[l] <= list[m]) {
					temp[i] = list[l];
					l++;
				}
				else {
					temp[i] = list[m];
					m++;
				}
				i++;
			}
			if(l > mid) {
				for(j = m; j <= high; j++) {
					temp[i] = list[j];
					i++;
				}
			}
			else {
				for(j = l; j <= mid; j++) {
					temp[i] = list[j];
					i++;
				}
			}
			for(j = low; j <= high; j++)
				list[j] = temp[j];
		}
};

int main() {

	/* Sort integer */
	
	int idata[] = {9,5,1,4,0,3,7,6,2,8};
	sorting<int> isrt(idata, get_size(idata));
	cout << "\nAfter sort:" << endl;
	for(int i = 0; i < get_size(idata); i++)
		cout << idata[i] << endl;

	/* Sort float */
	float fdata[] = {9.5,5.12,1.32,4.4,0.3,3.4,7.8,6.9,2.7,8.9};
	sorting<float> fsrt(fdata, get_size(fdata));
	cout << "\nAfter sort:" << endl;
	for(int i = 0; i < get_size(fdata); i++)
		cout << fdata[i] << endl;

	/* Sort string */
	string sdata[] = {"to","be","add","java","c++","python","sorting","new","search","c"};
	sorting<string> ssrt(sdata, get_size(sdata));
	cout << "\nAfter sort:" << endl;
	for(int i = 0; i < get_size(sdata); i++)
		cout << sdata[i] << endl;

}
