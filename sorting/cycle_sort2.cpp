/**
 * @file
 * @brief Cycle sort  is based on the idea that array to be sorted can be divided into cycles,
 * which can individually be rotated to give a sorted result.
 *
 * @details
 * It is an in-place, unstable sorting algorithm, a comparison sort that is theoretically
 * optimal in terms of the total number of memory writes to the original array.
 * Each value is either written zero times, if it’s already in its correct position,
 * or written one time to its correct position.
 *
 * The array is divided into cycles. We begin with the cycle containing the first element.
 * Find the correct position of first element and place it at its correct position, say j.
 * Now we consider the old value of arr[j] and find its correct position.
 * This process is continued until all the elements of the current cycle are placed at their correct position,
 * i.e.  until the starting point of the cycle is reached.
 *
 * @author [Vasu Sehgal](https://www.github.com/VasuSehgal123)
 * @see more on [Cycle sort](https://en.wikipedia.org/wiki/Cycle_sort)
 */

#include <iostream>   // for io operations
#include <vector>     // for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
    /**
    * @namespace cycle_sort
    * @brief Function to sort the array using cycle sort
    */
    namespace cycle_sort {

        /**
         * @brief Function to perform swapping
         * @param a element
         * @param b element
         * @returns void
         */
        template<typename T>
        void swap(T& a, T& b) {
            T temp = a;
            a = b;
            b = temp;
        }

        /**
        * @brief Function to perform cycle sort.
        * @param arr  vector of elements.
        * @param n size of the vector
        * @returns void
        */
    	template<typename T>
		void cycleSort(std::vector < T> &arr, int  n)
				{

		    int writes = 0; // count number of memory writes

		    // traverse array elements and put it at it's correct positon

		    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {

		        T item = arr[cycle_start];  // initialize item as starting point

		         int pos = cycle_start;     // Find position where we put the item.
		        for (int i = cycle_start + 1; i < n; i++)  //  we basically count all smaller elements
		            if (arr[i] < item)                               // on the right side of the item.
		                pos++;

		        if (pos == cycle_start)
		            continue;  // If item is already in correct position

		         while (item == arr[pos])
		            pos += 1; // ignore all duplicate  elements


		        if (pos != cycle_start) {
		            swap(item, arr[pos]);   // place the item at it's correct position
		            writes++;
		        }

		          while (pos != cycle_start) {  // Rotate rest of the cycle
		            pos = cycle_start;

		          for (int i = cycle_start + 1; i < n; i++) // Find position where we put the element
		                if (arr[i] < item)
		                    pos += 1;

		          while (item == arr[pos])
		                pos += 1;    // ignore all duplicate  elements


		            if (item != arr[pos]) {
		                swap(item, arr[pos]); // place the item at it's correct position
		                writes++;
		            }
		        }
		    }

		    // Number of memory writes or swaps
		    // cout << writes << endl ;
		}

	}  // namespace cycle_sort

}  // namespace sorting

/**
 * @brief Test implementations
 * @returns void
 */
 static void test() {

    // example 1: vector of int
    const int size1 = 8;
    std::cout << "Test 1: After sort-\n";
    std::vector<int> arr1 = { 1, 8, 3, 9, 10, 10, 2, 4 };
    sorting::cycle_sort::cycleSort(arr1, size1);
    for (int i = 0; i < size1; i++)
        std::cout << arr1[i] << "   ";
    std::cout<<"\n";

   // example 2: vector of double
    const int size2 = 8;
     std::cout << "Test 2: After sort-\n";
    std::vector<double> arr2 = {11.82, 45.10, 33.22, 33.18, 1.9, 1.2, 61.77, 79.6};
     sorting::cycle_sort::cycleSort(arr2, size2);

    for (int i = 0; i < size2; i++)
        std::cout << arr2[i] << "  ";
     std::cout<<"\n";


}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
   test();  // execute the tests
   return 0;
}
