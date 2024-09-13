/**
 * @file
 * @brief Implementation of the [Random Pivot Quick
 * Sort](https://www.sanfoundry.com/cpp-program-implement-quick-sort-using-randomisation)
 * algorithm.
 * @details
 *          * A random pivot quick sort algorithm is pretty much same as quick
 * sort with a difference of having a logic of selecting next pivot element from
 * the input array.
 *          * Where in quick sort is fast, but still can give you the time
 * complexity of O(n^2) in worst case.
 *          * To avoid hitting the time complexity of O(n^2), we use the logic
 * of randomize the selection process of pivot element.
 *
 *          ### Logic
 *              * The logic is pretty simple, the only change is in the
 * partitioning algorithm, which is selecting the pivot element.
 *              * Instead of selecting the last or the first element from array
 * for pivot we use a random index to select pivot element.
 *              * This avoids hitting the O(n^2) time complexity in practical
 * use cases.
 *
 *       ### Partition Logic
 *           * Partitions are done such as numbers lower than the "pivot"
 * element is arranged on the left side of the "pivot", and number larger than
 * the "pivot" element are arranged on the right part of the array.
 *
 *       ### Algorithm
 *           * Select the pivot element randomly using getRandomIndex() function
 * from this namespace.
 *           * Initialize the pInd (partition index) from the start of the
 * array.
 *           * Loop through the array from start to less than end. (from start
 * to < end). (Inside the loop) :-
 *                   * Check if the current element (arr[i]) is less than the
 * pivot element in each iteration.
 *                   * If current element in the iteration is less than the
 * pivot element, then swap the elements at current index (i) and partition
 * index (pInd) and increment the partition index by one.
 *           * At the end of the loop, swap the pivot element with partition
 * index element.
 *           * Return the partition index from the function.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 */

#include <algorithm>  /// for std::is_sorted(), std::swap()
#include <array>      /// for std::array
#include <cassert>    /// for assert
#include <ctime>      /// for initializing random number generator
#include <iostream>   /// for IO operations
#include <tuple>      /// for returning multiple values form a function at once

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @brief Functions for the [Random Pivot Quick
 * Sort](https://www.sanfoundry.com/cpp-program-implement-quick-sort-using-randomisation)
 * implementation
 * @namespace random_pivot_quick_sort
 */
namespace random_pivot_quick_sort {
/**
 * @brief Utility function to print the array
 * @tparam T size of the array
 * @param arr array used to print its content
 * @returns void
 * */
template <size_t T>
void showArray(std::array<int64_t, T> arr) {
    for (int64_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Takes the start and end indices of an array and returns a random
 * int64_teger between the range of those two for selecting pivot element.
 *
 * @param start The starting index.
 * @param end The ending index.
 * @returns int64_t A random number between start and end index.
 * */
int64_t getRandomIndex(int64_t start, int64_t end) {
    srand(time(nullptr));  // Initialize random number generator.
    int64_t randomPivotIndex = start + rand() % (end - start + 1);
    return randomPivotIndex;
}

/**
 * @brief A partition function which handles the partition logic of quick sort.
 * @tparam size size of the array to be passed as argument.
 * @param start The start index of the passed array
 * @param end The ending index of the passed array
 * @returns std::tuple<int64_t , std::array<int64_t , size>> A tuple of pivot
 * index and pivot sorted array.
 */
template <size_t size>
std::tuple<int64_t, std::array<int64_t, size>> partition(
    std::array<int64_t, size> arr, int64_t start, int64_t end) {
    int64_t pivot = arr[end];  // Randomly selected element will be here from
                               // caller function (quickSortRP()).
    int64_t pInd = start;

    for (int64_t i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            std::swap(arr[i], arr[pInd]);  // swapping the elements from current
                                           // index to pInd.
            pInd++;
        }
    }
    std::swap(arr[pInd],
              arr[end]);  // swapping the pivot element to its sorted position
    return std::make_tuple(pInd, arr);
}

/**
 * @brief Random pivot quick sort function. This function is the starting point
 * of the algorithm.
 * @tparam size size of the array to be passed as argument.
 * @param start The start index of the passed array
 * @param end The ending index of the passed array
 * @returns std::array<int64_t , size> A fully sorted array in ascending order.
 */
template <size_t size>
std::array<int64_t, size> quickSortRP(std::array<int64_t, size> arr,
                                      int64_t start, int64_t end) {
    if (start < end) {
        int64_t randomIndex = getRandomIndex(start, end);

        // switching the pivot with right most bound.
        std::swap(arr[end], arr[randomIndex]);

        int64_t pivotIndex = 0;
        // getting pivot index and pivot sorted array.
        std::tie(pivotIndex, arr) = partition(arr, start, end);

        // Recursively calling
        std::array<int64_t, arr.size()> rightSortingLeft =
            quickSortRP(arr, start, pivotIndex - 1);
        std::array<int64_t, arr.size()> full_sorted =
            quickSortRP(rightSortingLeft, pivotIndex + 1, end);
        arr = full_sorted;
    }
    return arr;
}

/**
 * @brief A function utility to generate unsorted array of given size and range.
 * @tparam size Size of the output array.
 * @param from Stating of the range.
 * @param to Ending of the range.
 * @returns std::array<int64_t , size> Unsorted array of specified size.
 * */
template <size_t size>
std::array<int64_t, size> generateUnsortedArray(int64_t from, int64_t to) {
    srand(time(nullptr));
    std::array<int64_t, size> unsortedArray{};
    assert(from < to);
    int64_t i = 0;
    while (i < size) {
        int64_t randomNum = from + rand() % (to - from + 1);
        if (randomNum) {
            unsortedArray[i] = randomNum;
            i++;
        }
    }
    return unsortedArray;
}

}  // namespace random_pivot_quick_sort
}  // namespace sorting

/**
 * @brief a class containing the necessary test cases
 */
class TestCases {
 private:
    /**
     * @brief A function to print64_t given message on console.
     * @tparam T Type of the given message.
     * @returns void
     * */
    template <typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief Executes test cases
     * @returns void
     * */
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    /**
     * @brief A test case with single input
     * @returns void
     * */
    void testCase_1() {
        const int64_t inputSize = 1;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 1 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   EDGE CASE : Only contains one element");
        std::array<int64_t, inputSize> unsorted_arr{2};

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;  // length - 1

        log("Running algorithm of data of length 50 ...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     * @brief A test case with input array of length 500
     * @returns void
     * */
    void testCase_2() {
        const int64_t inputSize = 500;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("Description:");
        log("   BIG INPUT : Contains 500 elements and repeated elements");
        log("This is test case 2 for Random Pivot Quick Sort Algorithm : ");
        std::array<int64_t, inputSize> unsorted_arr =
            sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
                1, 10000);

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;  // length - 1

        log("Running algorithm of data of length 500 ...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     * @brief A test case with array of length 1000.
     * @returns void
     * */
    void testCase_3() {
        const int64_t inputSize = 1000;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 3 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   LARGE INPUT : Contains 1000 elements and repeated elements");
        std::array<int64_t, inputSize> unsorted_arr =
            sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
                1, 10000);

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;  // length - 1

        log("Running algorithm...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    TestCases tc = TestCases();
    tc.runTests();
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // Executes various test cases.

    const int64_t inputSize = 10;
    std::array<int64_t, inputSize> unsorted_array =
        sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
            50, 1000);
    std::cout << "Unsorted array is : " << std::endl;
    sorting::random_pivot_quick_sort::showArray(unsorted_array);

    std::array<int64_t, inputSize> sorted_array =
        sorting::random_pivot_quick_sort::quickSortRP(
            unsorted_array, 0, unsorted_array.size() - 1);
    std::cout << "Sorted array is : " << std::endl;
    sorting::random_pivot_quick_sort::showArray(sorted_array);
    return 0;
}
