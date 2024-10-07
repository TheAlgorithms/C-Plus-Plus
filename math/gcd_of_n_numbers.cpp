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
  if (y == 0) {
    return x;
  }
  if (x == 0) {
    return y;
  }
  return gcd_two(y, x % y); // Euclidean method
}

/**
 * @brief Function to check if all elements in the array are 0
 * @param a Array of numbers
 * @return 'True' if all elements are 0
 * @return 'False' if not all elements are 0
 */
template <std::size_t n>
bool check_all_zeros(const std::array<int, n> &a) {
  // Use std::all_of to simplify zero-checking
  return std::all_of(a.begin(), a.end(), [](int x) { return x == 0; });
}

/**
 * @brief Main program to compute GCD using the Euclidean algorithm
 * @param a Array of integers to compute GCD for
 * @return GCD of the numbers in the array or std::nullopt if undefined
 */
template <std::size_t n>
int gcd(const std::array<int, n> &a) {
  // GCD is undefined if all elements in the array are 0
  if (check_all_zeros(a)) {
    return -1; // Use std::optional to represent undefined GCD
  }

  // divisors can be negative, we only want the positive value
  int result = std::abs(a[0]);
  for (std::size_t i = 1; i < n; ++i) {
    result = gcd_two(result, std::abs(a[i]));
    if (result == 1) {
      break; // Further computations still result in gcd of 1
    }
  }
  return result;
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
