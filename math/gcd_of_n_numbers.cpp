/**
 * @file
 * @brief This program aims at calculating the GCD of n numbers
 *
 * @details
 * The GCD of n numbers can be calculated by
 * repeatedly calculating the GCDs of pairs of numbers
 * i.e. \f$\gcd(a, b, c)\f$ = \f$\gcd(\gcd(a, b), c)\f$
 * Euclidean algorithm helps calculate the GCD of each pair of numbers
 * efficiently
 *
 * @see gcd_iterative_euclidean.cpp, gcd_recursive_euclidean.cpp
 */
#include <algorithm> /// for std::abs
#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

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
  if (y == 0)
    return x;
  if (x == 0)
    return y;
  return gcd_two(y, x % y); // Euclidean method
}
/**
 * @brief Function to check if all elements in array are 0
 * @param a Array of numbers
 * @param n Number of elements in array
 * @return 'True' if all elements are 0
 * @return 'False' if not all elements are 0
 */
template <size_t n> bool check_all_zeros(std::array<int, n> a) {
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
 * @brief Main program to compute GCD by repeatedly use Euclidean algorithm
 * @param a Array of integers to compute GCD for
 * @param n Number of integers in the array
 * @return GCD of the numbers in the array
 */
template <size_t n> int gcd(std::array<int, n> a) {
  // GCD is undefined if all elements in the array are 0
  if (check_all_zeros(a))
    return -1; // since gcd is positive, use -1 to mark undefined gcd

  int gcd = a[0];
  for (int i = 1; i < n; i++) {
    gcd = gcd_two(gcd, a[i]);
    if (std::abs(gcd) == 1)
      break; // gcd is already 1, further computations still result in gcd of 1
  }

  return std::abs(gcd); // divisors can be negative, we only want positive value
}
} // namespace gcd_of_n_numbers
} // namespace math

/**
 * @brief Self-test implementation
 * @return void
 */
static void test() {
  std::array<int, 1> array_1 = {0};
  std::array<int, 1> array_2 = {1};
  std::array<int, 2> array_3 = {0, 2};
  std::array<int, 3> array_4 = {-60, 24, 18};
  std::array<int, 4> array_5 = {100, -100, -100, 200};
  std::array<int, 5> array_6 = {0, 0, 0, 0, 0};
  std::array<int, 7> array_7 = {10350, -24150, 0, 17250, 37950, -127650, 51750};
  std::array<int, 7> array_8 = {9500000, -12121200, 0, 4444, 0, 0, 123456789};

  assert(math::gcd_of_n_numbers::gcd(array_1) == -1);
  assert(math::gcd_of_n_numbers::gcd(array_2) == 1);
  assert(math::gcd_of_n_numbers::gcd(array_3) == 2);
  assert(math::gcd_of_n_numbers::gcd(array_4) == 6);
  assert(math::gcd_of_n_numbers::gcd(array_5) == 100);
  assert(math::gcd_of_n_numbers::gcd(array_6) == -1);
  assert(math::gcd_of_n_numbers::gcd(array_7) == 3450);
  assert(math::gcd_of_n_numbers::gcd(array_8) == 1);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
  test(); // run self-test implementation
  return 0;
}
