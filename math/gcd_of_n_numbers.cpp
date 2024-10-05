/**
 * @file
 * @brief This program aims at calculating the GCD of n numbers
 *
 * @details
 * The GCD of n numbers can be calculated by
 * repeatedly calculating the GCDs of pairs of numbers
 * i.e. gcd(a, b, c) = gcd(gcd(a, b), c)
 * Euclidean algorithm helps calculate the GCD of each pair of numbers efficiently
 * 
 * @see gcd_iterative_euclidean.cpp, gcd_recursive_euclidean.cpp
 */
#include <iostream>  /// for IO operations
#include <cassert>  /// for assert
#include <algorithm>  /// for std::abs

/**
 * @namespace math
 * @brief Maths algorithms
 */
namespace math {
/**
 * @namespace gcd_of_n_numbers
 * @brief Compute GCD of numbers in an array
 */
namespace gcd_of_n_numbers {
/**
 * @brief Function to compute GCD of 2 numbers x and y
 * @param x First number
 * @param y Second number
 * @return GCD of x and y via recursion
 */
int gcd_two(int x, int y) {
    // base cases
    if (y == 0) return x;
    if (x == 0) return y;
    return gcd_two(y, x % y);  // Euclidean method
}
/**
 * @brief Function to check if all elements in array are 0
 * @param a Array of numbers
 * @param n Number of elements in array
 * @return 'True' if all elements are 0
 * @return 'False' if not all elements are 0
 */
bool check_all_zeros(int a[], size_t n) {
    // Check for the undefined GCD cases
    int zero_count = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) {
            ++zero_count;
        }
    }

    // return whether all elements in array are 0
    return zero_count == n;
}
/** 
 * @brief Main program to compute GCD using division algorithm
 * @param a Array of integers to compute GCD for
 * @param n number of integers in the array
 * @return GCD of the numbers in the array
 */
int gcd(int a[], size_t n) {
    // GCD is undefined if all elements in the array are 0
    if (check_all_zeros(a, n))
        return -1;  // since gcd is positive, use -1 to mark undefined gcd

    int gcd = a[0];
    for(int i = 1; i < n; i++) {
        gcd = gcd_two(gcd, a[i]);
        if (std::abs(gcd) == 1) 
            break;  // if gcd is already 1, further computations still result in gcd of 1
    }

    return std::abs(gcd);  // divisors can be negative, and we only want positive value
}
} // namespace gcd_of_n_numbers
} // namespace math

/**
 * @brief Self-test implementation
 * @return void
 */
static void test() { 
    int array_1[1] = {0};
    int array_2[1] = {1};
    int array_3[2] = {0, 2};
    int array_4[3] = {-60, 24, 18};
    int array_5[4] = {100, -100, -100, 200};
    int array_6[5] = {0, 0, 0, 0, 0};
    int array_7[7] = {90, -120, 0, 135, 660, -280, 900}; 
    int array_8[7] = {90, -120, 0, 4000, 0, 0, 111};

    assert(math::gcd_of_n_numbers::gcd(array_1, 1) == -1);
    assert(math::gcd_of_n_numbers::gcd(array_2, 1) == 1); 
    assert(math::gcd_of_n_numbers::gcd(array_3, 2) == 2);
    assert(math::gcd_of_n_numbers::gcd(array_4, 3) == 6);
    assert(math::gcd_of_n_numbers::gcd(array_5, 4) == 100);
    assert(math::gcd_of_n_numbers::gcd(array_6, 5) == -1);
    assert(math::gcd_of_n_numbers::gcd(array_7, 7) == 5);
    assert(math::gcd_of_n_numbers::gcd(array_8, 7) == 1);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();  // run self-test implementation
    return 0;
}
