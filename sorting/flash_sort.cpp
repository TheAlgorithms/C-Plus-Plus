/**
 * @file
 * @brief Flash sort algorithm
 *
 * @details
 * Flash Sort is a distribution-based sorting algorithm. It is particularly 
 * efficient on large datasets with uniformly distributed elements, outperforming 
 * algorithms like quicksort. The algorithm categorizes elements into predefined 
 * buckets and then sorts each bucket using another algorithm (like insertion sort).
 * 
 * ## Flash Sort Algorithm Analysis
 *
 * ### Best Case
 * The best-case time complexity is \f$O(n)\f$, which occurs when elements are evenly 
 * distributed among buckets.
 * 
 * ### Worst Case
 * The worst-case time complexity is \f$O(n^{2})\f$, though it's rare and happens if all 
 * elements are placed into a single bucket.
 * 
 * ### Average Case
 * The average time complexity is \f$O(n + m)\f$, where \f$m\f$ is the number of buckets.
 * 
 * @note Flash Sort is ideal for datasets with many unique values and large sizes.
 *
 * @author [Akshat Pandey](https://github.com/AkshatPandey2006)
 */

#include <algorithm> /// for std::is_sorted
#include <cassert>   /// for assert
#include <iostream>  /// for IO implementations
#include <vector>    /// for std::vector, std::vector::size

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace flash_sort
 * @brief Flash sort algorithm
 */
namespace flash_sort {

/**
 * @brief Flash Sort algorithm
 * @param array An array to be sorted
 * @return The sorted array in ascending order
 */
template <typename T>
std::vector<T> flash_sort(std::vector<T>& array) {
    if (array.size() <= 1) return array;

    int size = array.size();
    int bucket_count = std::max(1, size / 10); // Choose bucket count proportional to input size

    // Step 1: Find the min and max elements
    T min_elem = *std::min_element(array.begin(), array.end());
    T max_elem = *std::max_element(array.begin(), array.end());

    // If all elements are identical, the array is already sorted
    if (min_elem == max_elem) return array;

    // Step 2: Create and initialize buckets
    std::vector<int> buckets(bucket_count, 0);
    std::vector<int> positions(bucket_count + 1, 0); // To track bucket ranges

    // Step 3: Distribute elements into buckets based on their value
    for (const T& elem : array) {
        int bucket_index = (bucket_count - 1) * (elem - min_elem) / (max_elem - min_elem);
        ++buckets[bucket_index];
    }

    // Step 4: Compute the starting index of each bucket
    for (int i = 1; i < bucket_count; ++i) {
        positions[i] = positions[i - 1] + buckets[i - 1];
    }

    // Step 5: Rearrange elements based on computed positions
    for (int i = 0; i < size;) {
        int bucket_index = (bucket_count - 1) * (array[i] - min_elem) / (max_elem - min_elem);
        if (i >= positions[bucket_index] && i < positions[bucket_index + 1]) {
            ++i;
        } else {
            std::swap(array[i], array[positions[bucket_index]++]);
        }
    }

    // Step 6: Apply insertion sort within each bucket (for better performance)
    for (int i = 0; i < bucket_count; ++i) {
        int start = (i == 0) ? 0 : positions[i];
        int end = positions[i + 1];
        std::sort(array.begin() + start, array.begin() + end);
    }

    return array;
}
} // namespace flash_sort
} // namespace sorting

/**
 * @brief Self-test implementation
 * @return void
 */
static void test() {
    std::vector<int> vec_1 = {3, 1, -9, 0};
    std::vector<int> sorted_1 = sorting::flash_sort::flash_sort(vec_1);

    std::vector<int> vec_2 = {3};
    std::vector<int> sorted_2 = sorting::flash_sort::flash_sort(vec_2);

    std::vector<int> vec_3 = {10, 10, 10, 10, 10};
    std::vector<int> sorted_3 = sorting::flash_sort::flash_sort(vec_3);

    std::vector<float> vec_4 = {1234, -273.1, 23, 150, 1234, 1555.55, -2000};
    std::vector<float> sorted_4 = sorting::flash_sort::flash_sort(vec_4);

    std::vector<char> vec_5 = {'z', 'Z', 'a', 'B', ' ', 'c', 'a'};
    std::vector<char> sorted_5 = sorting::flash_sort::flash_sort(vec_5);

    std::vector<std::string> vec_6 = {"Hello", "hello", "Helo", "Hi", "hehe"};
    std::vector<std::string> sorted_6 = sorting::flash_sort::flash_sort(vec_6);

    assert(std::is_sorted(sorted_1.begin(), sorted_1.end()));
    assert(std::is_sorted(sorted_2.begin(), sorted_2.end()));
    assert(std::is_sorted(sorted_3.begin(), sorted_3.end()));
    assert(std::is_sorted(sorted_4.begin(), sorted_4.end()));
    assert(std::is_sorted(sorted_5.begin(), sorted_5.end()));
    assert(std::is_sorted(sorted_6.begin(), sorted_6.end()));
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
