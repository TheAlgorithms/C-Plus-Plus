/**
 *  \addtogroup sorting Sorting Algorithms
 *  @{
 *  \file
 *  \brief Wiggle Sort Algorithm Implmentation
 *
 *  \author [Roshan Kanwar](http://github.com/roshan0708)
 *
 *  \details
 *  Wiggle Sort sorts the array into a wave like array.
 *  An array ‘arr[0..n-1]’ is sorted in wave form,
 *  if arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= …..
 *
 *  \example
 *  vec = [1,1,5,6,1,4], after wiggle sort vec will become equal to [1,1,6,1,5,4]
 *  vec = [2,8,9,1,7], after wiggle sort vec will become equal to [8,2,9,1,7]
 */

#include <iostream>
#include <vector>

/**
 *
 *  The swap() function is used for swapping two numbers.
 *
 *  @param x - first number
 *  @param y - second number
 *  @param temp - temporary variable
 *
 */

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 *
 *  The displayElements() function is used for printing the elements.
 *  Prints elements of the vector after they're sorted using wiggle sort algorithm.
 *
 *  @param vec - vector containing the sorted elements
 *
 */

void displayElements(std::vector<int> vec) {

    std::cout << "Sorted elements are as follows: \n";

    std::cout << "[";

    for(int i = 0 ; i < vec.size() ; i++ ) {

        std::cout << vec[i] ;
        if(i != vec.size() - 1) {
            std::cout << ", " ;
        }

    }

    std::cout << "]"<<std::endl;

}

/**
 *
 *  The wiggleSort() function is used for sorting the elements in wave form.
 *  Checking whether the even indexed elements are greater than
 *  their adjacent odd elements.
 *  Traversing all even indexed elements of the input vector.
 *  If current element is smaller than the previous odd element, swap them.
 *  If current element is smaller than the next odd element, swap them.
 *
 *  @param vec - input vector (unsorted elements)
 *
 */

class Algorithm {

   public:

   void wiggleSort(std::vector <int>& vec) {

       for(int i = 0; i < vec.size() ; i +=2) {

           if(i > 0 && vec[i-1] > vec[i]) {
               swap(&vec[i],&vec[i-1]);
           }

           if(i < vec.size() - 1 && vec[i] < vec[i+1]) {
               swap(&vec[i],&vec[i+1]);
           }

       }

   }
};

/** Driver program to test above functions */
int main() {

    int size;

    std::cout << "\nEnter the number of elements : ";

    std::cin >> size;

    std::vector<int> v(size);

    std::cout << "\nEnter the unsorted elements : ";

    for (int i = 0; i < size; ++i) {
        std::cout << "\n";
        std::cin >> v[i];
    }

    Algorithm ob;
    (ob.wiggleSort(v));
    displayElements(v);
}
