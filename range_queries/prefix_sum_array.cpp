/**
 * @file prefix_sum_array.cpp
 * @brief Implementation of [Prefix Sum Array] data structure
 *
 * @details
 * Prefix Sum Array is a data structure, that allows answering sum in some range
 * queries. It can answer most sum range queries in O(1), with a build time
 * complexity of O(N). But it hasn't an update querie.
 *
 * * Running Time Complexity \n
 * * Build : O(N) \n
 * * Range Query : O(1) \n
 */

#include <cassert>
#include <iostream>
#include <vector>

/* Macros */

constexpr int ARRAY_LENGHT = 10;

/* Global Declarations */

std::vector<int> PSA(ARRAY_LENGHT + 1,
                     0);  // PSA structure, initialized with 0's. Plus one in
                          // lenght for the leading zero.

/**
 * Main function
 */

int main() {
    std::vector<int> values{0,  123, 0,  2,  -2, 5,
                            24, 0,   23, -1, -1};  // original array

    for (int i = 1; i <= ARRAY_LENGHT;
         i++) {  // building the sctructure 1-indexed
        PSA[i] = PSA[i - 1] +
                 values[i];  // sums the previous sum with the current value
    }

    // queries are of the type: sum of the range [a, b] = psa[b] - psa[a-1]

    assert(PSA[10] == 173);         // sum of the entire array
    assert(PSA[6] - PSA[3] == 27);  // the sum of the interval [4, 6]
    assert(PSA[9] - PSA[4] == 51);  // the sum of the interval [5, 9]

    return 0;
}
