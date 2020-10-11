/**
 * @file
 * @author [@sinkyoungdeok](https://github.com/sinkyoungdeok)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Algorithm that combines insertion sort and merge sort. [Wiki
 * link](https://en.wikipedia.org/wiki/Merge-insertion_sort)
 *
 * @see Individual algorithms: insertion_sort.cpp and merge_sort.cpp
 */
#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <iostream>
#include <memory>

/** \namespace sorting
 * \brief Sorting algorithms
 */
namespace sorting {
/** \namespace merge_insertion
 * \brief Combined Intersion-Merge sorting algorithm
 */
namespace merge_insertion {

/**
 * @brief Insertion merge algorithm
 * @see insertion_sort.cpp
 *
 * @tparam T array data type
 * @tparam N length of array
 * @param A pointer to array to sort
 * @param start start index of sorting window
 * @param end end index of sorting window
 */
template <typename T, size_t N>
static void InsertionSort(std::array<T, N> *A, size_t start, size_t end) {
    size_t i = 0, j = 0;
    T *ptr = A->data();

    for (i = start; i < end; i++) {
        T temp = ptr[i];
        j = i;
        while (j > start && temp < ptr[j - 1]) {
            ptr[j] = ptr[j - 1];
            j--;
        }
        //   for (j = i; j > start && temp < ptr[j - 1]; --j) {
        //       ptr[j] = ptr[j - 1];
        //   }

        ptr[j] = temp;
    }
}

/**
 * @brief Perform merge of data in a window
 *
 * @tparam T array data type
 * @tparam N length of array
 * @param A pointer to array to sort
 * @param min start index of window
 * @param max end index of window
 * @param mid mid-point of window
 */
template <typename T, size_t N>
static void merge(std::array<T, N> *array, size_t min, size_t max, size_t mid) {
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    auto ptr = array->data();
    std::array<T, N + 1> tempArray{0};

    // While there are elements in the left or right runs
    for (size_t index = min; index <= max; index++) {
        // If left run head exists and is <= existing right run head.
        if (firstIndex <= mid &&
            (secondIndex > max || ptr[firstIndex] <= ptr[secondIndex])) {
            tempArray[index] = ptr[firstIndex];
            firstIndex++;
        } else {
            tempArray[index] = ptr[secondIndex];
            secondIndex++;
        }
    }

    // transfer to the initial array
    memcpy(ptr + min, tempArray.data() + min, (max - min) * sizeof(T));
    //  for (int index = min; index <= max; index++) ptr[index] =
    //  tempArray[index];
}

/**
 * @brief Final combined algorithm.
 * Algorithm utilizes ::sorting::merge_insertion::InsertionSort if window length
 * is less than threshold, else performs merge sort recursively using
 * ::sorting::merge_insertion::mergeSort
 *
 * @tparam T array data type
 * @tparam N length of array
 * @param A pointer to array to sort
 * @param min start index of sort window
 * @param max end index of sort window
 * @param threshold window length threshold
 */
template <typename T, size_t N>
void mergeSort(std::array<T, N> *array, size_t min, size_t max,
               size_t threshold) {
    // prerequisite
    if ((max - min) <= threshold) {
        InsertionSort(array, min, max);
    } else {
        // get the middle point
        size_t mid = (max + min) >> 1;

        // apply merge sort to both parts of this
        mergeSort(array, min, mid, threshold);
        mergeSort(array, mid, max, threshold);

        // and finally merge all that sorted stuff
        merge(array, min, max, mid);
    }
}

}  // namespace merge_insertion
}  // namespace sorting

/**
 * @brief Function to test code using random arrays
 * @returns none
 */
static void test() {
    constexpr size_t size = 30;
    std::array<int, size> array{0};
    // input
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 100 - 50;
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    sorting::merge_insertion::InsertionSort(&array, 0, size);
    //  sorting::merge_insertion::mergeSort(&array, 0, size, 10);

    // output
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    assert(std::is_sorted(std::begin(array), std::end(array)));
    std::cout << "Test passed\n";
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    std::srand(std::time(nullptr));
    test();
    return 0;
}
