/**
 * @file
 * @brief pancake sort sorts a disordered stack of pancakes by flipping any number of pancakes using a spatula using minimum number of flips.
 *
 * @details
 * Unlike a traditional sorting algorithm, which attempts to sort with the fewest comparisons possible,
 * the goal is to sort the sequence in as few reversals as possible.
 * Overall time complexity of pancake sort is O(n^2)
 * For example: example 1:-
 * Disordered pancake sizes: {2,5,3,7,8} 
 * Sorted: {2,3,5,7,8}
 * For example: example 2:-
 * Disordered pancake sizes: {22,51,37,73,81} 
 * Sorted: {22,37,51,73,81}
 * @author [Divyansh Gupta](https://github.com/divyansh12323)
 * @see more on [Pancake sort](https://en.wikipedia.org/wiki/Pancake_sorting)
 * @see related problem [Leetcode](https://leetcode.com/problems/pancake-sorting/)
*/

#include <iostream>   // for io operations
#include <vector>     // for std::vector
#include <algorithm>  // for std::is_sorted
#include <cassert>     // for std::assert

/**
 * @namespace sorting
 * Sorting algorithms
 */
namespace sorting {
    /**
    * This implementation is for a C-style array input that gets modified in place.
    * @param [in,out] arr our array of elements.
    * @param size size of given array
    */
    template <typename T>
    void reverse(std::vector <T>& arr, int start, int end) { 
	    T temp; 
	    while (start <= end) { 
		    temp = arr[start]; 
		    arr[start] = arr[end]; 
		    arr[end] = temp; 
		    start++; 
		    end--; 
	    } 
    } 

    template <typename T>
    int pancakeSort(std::vector <T>& arr, int n)  {
        for (int i=n; i>1; --i) {
            int mi = 0, j;
            T maxE = 0;
            for(j=0; j<i; j++) {
                if(arr[j] >= maxE) {
                    maxE = arr[j];
	                mi = j;
	            }
	        }
		    if (mi != i-1) { 
			    reverse(arr, 0, mi); 
			    reverse(arr, 0, i-1); 
		    } 
	    } 
    } 
} // namespace sorting

/**
 * Test function
 */
static void test() {
    
    // example 1: int
    const int size1 = 7;
    std::vector <int> arr1 = {23, 10, 20, 11, 12, 6, 7};
    sorting::pancakeSort(arr1, size1);
    assert(std::is_sorted(arr1.begin(), arr1.end()));
    std::cout<<"Passed\n";
    for (int i = 0; i < size1; i++) {
        std::cout<<arr1[i]<<" ";
    }
    std::cout<<std::endl;
    
    // example 2: double
    const int size2 = 7;
    std::vector <double> arr2 = {23.56, 10.62, 200.78, 111.484, 1.2, 61.77, 79.6};
    sorting::pancakeSort(arr2, size2);
    assert(std::is_sorted(arr2.begin(), arr2.end()));
    std::cout<<"Passed\n";
    for (int i = 0; i < size2; i++) {
        std::cout<<arr2[i]<<" ";
    }
    std::cout<<std::endl;
}

/**
 * Our main function with example of sort method.
 */
int main() {
    test();
    return 0;
}
