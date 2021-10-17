/**
 * \file
 * \brief [Interpolation
 * search](https://en.wikipedia.org/wiki/Interpolation_search) algorithm
 */
#include <iostream>

/** function to search the value in an array using interpolation search
 * \param [in] arr array to search in
 * \param [in] value value to search for
 * \param [in] len length of array
 * \returns index where the value is found
 * \returns -1 if not found
 */
int InterpolationSearch(int A[], int n, int x) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (((high - 1) * (x - A[low])) / (A[high] - A[low]));
        if (x == A[mid])
            return mid;  // Found x, return (exit)
        else if (x < A[mid])
            high = mid - 1;  // X lies before mid
        else
            low = mid + 1;  // x lies after mid
    }

    return -1;
}

/** main function */
int main() {
    int A[] = {2, 4, 5, 7, 13, 14, 15, 23};
    int x = 17;

    ///< passed array A inside the InterpolationSearch function
    int index = InterpolationSearch(A, 8, x);
    if (index < 0)
        std::cout << "Number " << x << " not found" << std::endl;
    else
        std::cout << "Number " << x << " is at " << index << std::endl;
}

// randomly set x bcoz array was defined by us , therefore not reasonable for
// asking input. We could have asked for input if array elements were inputed by
// the user.
