/**
 * \file
 * \brief [Ternary search](https://en.wikipedia.org/wiki/Ternary_search)
 * algorithm
 *
 * This is a divide and conquer algorithm.
 * It does this by dividing the search space by 3 parts and
 * using its property (usually monotonic property) to find
 * the desired index.
 *
 * * Time Complexity : O(log3 n)
 * * Space Complexity : O(1) (without the array)
 */

#include <iostream>

/**
 * The absolutePrecision can be modified to fit preference but
 * it is recommended to not go lower than 10 due to errors that
 * may occur.
 */
#define absolutePrecision 10
/**
 * The value of _target should be decided or can be decided later
 * by using the variable of the function.
 */
#define _target 10

#define MAX 10000000  ///< Maximum length of array

/**
 * get_input function is to receive input from standard IO
 * @todo @christianbender Get input from STDIO or write input to memory as done
 * above.
 */
void get_input() {}

/**
 * This is the iterative method of the ternary search which returns the index of
 * the element.
 * \param[in] left lower interval limit
 * \param[in] right upper interval limit
 * \param[in] A array to search in
 * \param[in] target value to search for
 * \returns index where the target value was found
 * \returns -1 if target value not found
 */
int it_ternary_search(int left, int right, int A[], int target) {
    while (1) {
        if (left < right) {
            if (right - left < absolutePrecision) {
                for (int i = left; i <= right; i++)
                    if (A[i] == target)
                        return i;

                return -1;
            }

            int oneThird = (left + right) / 3 + 1;
            int twoThird = (left + right) * 2 / 3 + 1;

            if (A[oneThird] == target)
                return oneThird;
            else if (A[twoThird] == target)
                return twoThird;

            else if (target > A[twoThird])
                left = twoThird + 1;
            else if (target < A[oneThird])
                right = oneThird - 1;

            else
                left = oneThird + 1, right = twoThird - 1;
        } else {
            return -1;
        }
    }
}

/**
 * This is the recursive method of the ternary search which returns the index of
 * the element.
 * \param[in] left lower interval limit
 * \param[in] right upper interval limit
 * \param[in] A array to search in
 * \param[in] target value to search for
 * \returns index where the target value was found
 * \returns -1 if target value not found
 */
int rec_ternary_search(int left, int right, int A[], int target) {
    if (left < right) {
        if (right - left < absolutePrecision) {
            for (int i = left; i <= right; i++)
                if (A[i] == target)
                    return i;

            return -1;
        }

        int oneThird = (left + right) / 3 + 1;
        int twoThird = (left + right) * 2 / 3 + 1;

        if (A[oneThird] == target)
            return oneThird;
        if (A[twoThird] == target)
            return twoThird;

        if (target < A[oneThird])
            return rec_ternary_search(left, oneThird - 1, A, target);
        if (target > A[twoThird])
            return rec_ternary_search(twoThird + 1, right, A, target);

        return rec_ternary_search(oneThird + 1, twoThird - 1, A, target);
    } else {
        return -1;
    }
}

/**
 * ternary_search is a template function
 * You could either use it_ternary_search or rec_ternary_search according to
 * preference.
 * \param [in] N length of array
 * \param[in] A array to search in
 * \param[in] target value to search for
 */
void ternary_search(int N, int A[], int target) {
    std::cout << it_ternary_search(0, N - 1, A, target) << '\t';
    std::cout << rec_ternary_search(0, N - 1, A, target) << '\t';
    std::cout << std::endl;
}

/** Main function */
int main() {
    int N = 21;
    int A[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 10};
    get_input();
    ternary_search(N, A, _target);
    return 0;
}
