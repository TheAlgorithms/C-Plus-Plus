/**
 * @file
 * @brief Algorithm of [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
 * @author [Suyash Jaiswal](https://github.com/Suyashjaiswal)
 * @details
 * Sort the vector of unsigned integers using radix sort i.e. sorting digit by
 * digit using [Counting Sort](https://en.wikipedia.org/wiki/Counting_sort) as
 * subroutine. Running time of radix sort is O(d*(n+b)) where b is the base for
 * representing numbers and d in the max digits in input integers and n is
 * number of unsigned integers. consider example for n = 5, aray elements =
 * 432,234,143,332,123 sorting digit by digit sorting according to 1) 1st digit
 * place
 * => 432, 332, 143, 123, 234
 *
 * 2) 2nd digit place
 * => 123, 432, 332, 234, 143
 *
 * 3) 3rd digit place
 * => 123, 143, 234, 332, 432
 *
 * using count sort at each step, which is stable.
 * stable => already sorted according to previous digits.
 */

/// header files
#include <algorithm>  /// for collection of functions
#include <cassert>  /// for a macro called assert which can be used to verify assumptions
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace radix_sort
 * @brief Functions for [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
 * algorithm
 */
namespace radix_sort {
/**
 * @brief Function to sort vector according to current digit using stable
 * sorting.
 * @param cur_digit - sort according to the cur_digit
 * @param ar - vector to be sorted
 * @returns std::vector sorted till ith digit
 */
std::vector<uint64_t> step_ith(
    uint16_t cur_digit,
    const std::vector<uint64_t>& ar) {  // sorting according to current digit.
    int n = ar.size();
    std::vector<uint32_t> position(10, 0);
    for (int i = 0; i < n; ++i) {
        position[(ar[i] / cur_digit) %
                 10]++;  // counting frequency of 0-9 at cur_digit.
    }
    int cur = 0;
    for (int i = 0; i < 10; ++i) {
        int a = position[i];
        position[i] = cur;  // assingning starting position of 0-9.
        cur += a;
    }
    std::vector<uint64_t> temp(n);
    for (int i = 0; i < n; ++i) {
        temp[position[(ar[i] / cur_digit) % 10]] =
            ar[i];  // storing ar[i] in ar[i]'s cur_digit expected position of
                    // this step.
        position[(ar[i] / cur_digit) %
                 10]++;  // incrementing ar[i]'s cur_digit position by 1, as
                         // current place used by ar[i].
    }
    return temp;
}
/**
 * @brief Function to sort vector digit by digit.
 * @param ar - vector to be sorted
 * @returns sorted vector
 */
std::vector<uint64_t> radix(const std::vector<uint64_t>& ar) {
    uint64_t max_ele =
        *max_element(ar.begin(), ar.end());  // returns the max element.
    std::vector<uint64_t> temp = ar;
    for (int i = 1; max_ele / i > 0;
         i *= 10) {  // loop breaks when i > max_ele because no further digits
                     // left to makes changes in aray.
        temp = step_ith(i, temp);
    }
    for (uint64_t i : temp) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return temp;
}
}  // namespace radix_sort
}  // namespace sorting

/**
 * @brief Function to test the above algorithm
 * @returns none
 */
static void tests() {
    /// Test 1
    std::vector<uint64_t> ar1 = {432, 234, 143, 332, 123};
    ar1 = sorting::radix_sort::radix(ar1);
    assert(std::is_sorted(ar1.begin(), ar1.end()));
    /// Test 2
    std::vector<uint64_t> ar2 = {213, 3214, 123, 111, 112, 142,
                                 133, 132,  32,  12,  113};
    ar2 = sorting::radix_sort::radix(ar2);
    assert(std::is_sorted(ar2.begin(), ar2.end()));
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // execute the tests
    return 0;
}
