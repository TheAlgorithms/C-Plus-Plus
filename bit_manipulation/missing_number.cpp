/**
 * @file
 * @brief [Find missing number in given numbers]
 * (https://leetcode.com/problems/missing-number/description/)
 * implementation
 *
 * @details
 * We are given an array of numbers [0,n]. Where n is the length of array.
 *  We need to find the missing number in the above array in given range.
 *
 * lets say we have an array of [0,1,2]. Now we know that length of array is 3.
 * We need to find missing number in range[0,3]. We can identify it's the number
 * 3 that is missing in our example.
 *
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)
 * @author [Praful Katare](https://github.com/Kpraful)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */

namespace bit_manipulation {
/**
 * @brief The main function implements check for power of 2
 * @param n is the number who will be checked
 * @returns either true or false
 */
std::int64_t missingNumber(
    std ::int64_t *array,
    std ::int64_t size) {  // int64_t is preferred over int so that
                           // no Overflow can be there.
    std::int64_t xor_total = 0;
    // Intution Behind this algorithm

    // The main intution is that xor of number with itself will negate it.
    // lets say we have 1,2,3 if we xor 1^2^3^1^2^3 then the result will be
    // zero. In this order doesn't matter.

    // The algorithm works as follows:
    //
    // - We iterate through the array and perform a bitwise XOR operation on all
    // the elements.
    //   This results in a value that combines all the elements in the array.
    // lets say we have an array of [0,1,2] so we have value of 0^1^2 in our
    // xor_total
    for (std::int64_t i = 0; i < size; i++) {
        xor_total ^= array[i];  // 0^1^2
    }

    // - Next, we XOR all the numbers from 1 to 'size+1' (inclusive).
    //   This is done to create an XOR result that represents the expected XOR
    //   of all the numbers in that range.
    // so: 0^1^2^3^0^1^2 => this will leave only 3 as all other xor will negated
    // themself.
    for (std::int64_t i = 1; i <= size + 1; i++) {
        xor_total ^= i;  // 0^1^2^3
    }
    // - By XORing these two results, we obtain the missing number because
    // XORing the same number twice results in zero,
    //   leaving only the missing number in the final result.

    return xor_total;  // 3
    // - This approach is efficient with a time complexity of O(n), where 'n' is
    // the size of the array.
}
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::int64_t arr1[] = {1, 2, 3, 4, 5};
    std::int64_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    assert(bit_manipulation::missingNumber(arr1, size1) == 6);

    std::int64_t arr2[] = {2, 3, 4, 5, 6};
    std::int64_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    assert(bit_manipulation::missingNumber(arr2, size2) == 1);

    std::int64_t arr3[] = {1, 2, 3, 5, 6};
    std::int64_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    assert(bit_manipulation::missingNumber(arr3, size3) == 4);

    std::int64_t arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    std::int64_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    assert(bit_manipulation::missingNumber(arr4, size4) == 10);

    std::int64_t arr5[] = {1};
    std::int64_t size5 = sizeof(arr5) / sizeof(arr5[0]);
    assert(bit_manipulation::missingNumber(arr5, size5) == 2);

    std::int64_t arr6[] = {2};
    std::int64_t size6 = sizeof(arr6) / sizeof(arr6[0]);
    assert(bit_manipulation::missingNumber(arr6, size6) == 1);

    std::int64_t arr7[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::int64_t size7 = sizeof(arr7) / sizeof(arr7[0]);
    assert(bit_manipulation::missingNumber(arr7, size7) == 12);

    std::cout << "All test cases successfully passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
