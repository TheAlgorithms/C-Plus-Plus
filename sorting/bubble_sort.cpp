/**
 * @file
 * @brief Bubble sort algorithm
 *
 * @details
 * Bubble sort algorithm is the bubble sorting algorithm. The most important reason
 * for calling the bubble is that the largest number is thrown at the end of this
 * algorithm. This is all about the logic. In each iteration, the largest number is
 * expired and when iterations are completed, the sorting takes place.
 * 
 * What is Swap?
 * 
 * Swap in the software means that two variables are displaced.
 * An additional variable is required for this operation. x = 5, y = 10.
 * We want x = 10, y = 5. Here we create the most variable to do it.
 * 
 * ```cpp
 * int z;
 * z = x;
 * x = y;
 * y = z;
 * ```
 * 
 * The above process is a typical displacement process.
 * When x assigns the value to x, the old value of x is lost.
 * That's why we created a variable z to create the first value of the value of x,
 * and finally, we have assigned to y.
 * 
 * ## Bubble Sort Algorithm Analysis (Best Case - Worst Case - Average Case)
 * 
 * ### Best Case
 * Bubble Sort Best Case Performance. \f$O(n)\f$. However, you
 * can't get the best status in the code we shared above. This happens on the
 * optimized bubble sort algorithm. It's right down there.
 * 
 * ### Worst Case
 * Bubble Sort Worst Case Performance is \f$O(n^{2})\f$. Why is that? Because if you
 * remember Big O Notation, we were calculating the complexity of the algorithms in
 * the nested loops. The \f$n * (n - 1)\f$ product gives us \f$O(n^{2})\f$ performance. In the
 * worst case all the steps of the cycle will occur.
 * 
 * ### Average Case
 * Bubble Sort is not an optimal algorithm. In average, \f$O(n^{2})\f$ performance is taken. 
 * 
 * @author [Deepak](https://github.com/Deepak-j-p)
 * @author [Nguyen Phuc Chuong](https://github.com/hollowcrust)
 */

#include <algorithm> /// for std::is_sorted
#include <cassert>   /// for assert
#include <iostream>  /// for IO implementations
#include <string>    /// for std::string
#include <utility>   /// for std::pair, std::swap
#include <vector>    /// for std::vector, std::vector::push_back, std::vector::size

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace bubble_sort
 * @brief Bubble sort algorithm
 */
namespace bubble_sort {
/**
 * @brief Bubble sort algorithm
 * @param array An array to be sorted
 * @return The array sorted in ascending order
 */
template <typename T> 
std::vector<T> bubble_sort(std::vector<T>& array) {
  // swap_check flag to terminate the function early
  // if there is no swap occurs in one iteration.
  bool swap_check = true;
  int size = array.size();
  for (int i = 0; (i < size) && (swap_check); i++) {
    swap_check = false;
    for (int j = 0; j < size - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        swap_check = true;
        std::swap(array[j], array[j + 1]);
      }
    }
  }

  return array;
}
} // namespace bubble_sort
} // namespace sorting

/**
 * @brief Self-test implementation
 * @return void
 */
static void test() {
  std::vector<int> vec_1 = {3, 1, -9, 0};
  std::vector<int> sorted_1 = sorting::bubble_sort::bubble_sort(vec_1);

  std::vector<int> vec_2 = {3};
  std::vector<int> sorted_2 = sorting::bubble_sort::bubble_sort(vec_2);

  std::vector<int> vec_3 = {10, 10, 10, 10, 10};
  std::vector<int> sorted_3 = sorting::bubble_sort::bubble_sort(vec_3);

  std::vector<float> vec_4 = {1234, -273.1, 23, 150, 1234, 1555.55, -2000};
  std::vector<float> sorted_4 = sorting::bubble_sort::bubble_sort(vec_4);

  std::vector<char> vec_5 = {'z', 'Z', 'a', 'B', ' ', 'c', 'a'};
  std::vector<char> sorted_5 = sorting::bubble_sort::bubble_sort(vec_5);

  std::vector<std::string> vec_6 = {"Hello", "hello", "Helo", "Hi", "hehe"};
  std::vector<std::string> sorted_6 = sorting::bubble_sort::bubble_sort(vec_6);

  std::vector<std::pair<int, char>> vec_7 = {{10, 'c'}, {2, 'z'}, {10, 'a'}, {0, 'b'}, {-1, 'z'}};
  std::vector<std::pair<int, char>> sorted_7 = sorting::bubble_sort::bubble_sort(vec_7);

  assert(std::is_sorted(sorted_1.begin(), sorted_1.end()));
  assert(std::is_sorted(sorted_2.begin(), sorted_2.end()));
  assert(std::is_sorted(sorted_3.begin(), sorted_3.end()));
  assert(std::is_sorted(sorted_4.begin(), sorted_4.end()));
  assert(std::is_sorted(sorted_5.begin(), sorted_5.end()));
  assert(std::is_sorted(sorted_6.begin(), sorted_6.end()));
  assert(std::is_sorted(sorted_7.begin(), sorted_7.end()));
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
  test();
  return 0;
}
