/**
 * \file
 * \brief [Interpolation
 * search](https://en.wikipedia.org/wiki/Interpolation_search) algorithm
 */
#include <cassert>
#include <iostream>

/** function to search the value in a sorted array using interpolation search
 * \param [in] A sorted array to search in
 * \param [in] n length of array
 * \param [in] x value to search for
 * \returns index where the value is found
 * \returns -1 if not found
 */
int InterpolationSearch(int A[], int n, int x) {
    int low = 0;
    int high = n - 1;
    // x outside of [A[low], A[high]] cannot be in the array, and would give a
    // probe position outside of [low, high]
    while (low <= high && x >= A[low] && x <= A[high]) {
        if (A[high] == A[low]) {  // all the remaining values are equal
            return (A[low] == x) ? low : -1;
        }
        int mid =
            low + static_cast<int>(
                      (static_cast<long long>(high - low) * (x - A[low])) /
                      (static_cast<long long>(A[high]) - A[low]));
        if (x == A[mid])
            return mid;  // Found x, return (exit)
        else if (x < A[mid])
            high = mid - 1;  // X lies before mid
        else
            low = mid + 1;  // x lies after mid
    }

    return -1;
}

/** self-test implementations */
static void test() {
    int A[] = {2, 4, 5, 7, 13, 14, 15, 23};
    for (int i = 0; i < 8; i++) {
        assert(InterpolationSearch(A, 8, A[i]) == i);  // every element
    }
    assert(InterpolationSearch(A, 8, 17) == -1);  // between the elements
    assert(InterpolationSearch(A, 8, 1) == -1);   // below the first element
    assert(InterpolationSearch(A, 8, 24) == -1);  // above the last element
    assert(InterpolationSearch(A, 0, 5) == -1);   // empty array

    int B[] = {3, 3, 3};
    assert(InterpolationSearch(B, 3, 3) != -1);  // equal elements
    assert(InterpolationSearch(B, 3, 4) == -1);
    assert(InterpolationSearch(B, 3, 2) == -1);

    int C[] = {-10, 0, 100000, 2000000000};  // the product does not overflow
    assert(InterpolationSearch(C, 4, 2000000000) == 3);
    assert(InterpolationSearch(C, 4, -10) == 0);
}

/** main function */
int main() {
    test();  // run self-test implementations

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
