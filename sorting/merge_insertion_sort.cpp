/**
 * @file
 * @author [@sinkyoungdeok](https://github.com/sinkyoungdeok)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief
 */
#include <array>
#include <ctime>
#include <iostream>
#include <memory>

/**
 * @brief
 *
 */
namespace sorting {
/**
 * @brief
 *
 */
namespace merge_insertion {

/**
 * @brief
 *
 * @tparam T
 * @tparam N
 * @param A
 * @param start
 * @param end
 */
template <typename T, size_t N>
void InsertionSort(std::array<T, N> *A, size_t start, size_t end) {
    size_t i, j;
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
 * @brief
 *
 * @tparam T
 * @tparam N
 * @param array
 * @param min
 * @param max
 * @param mid
 */
template <typename T, size_t N>
void merge(std::array<T, N> *array, size_t min, size_t max, size_t mid) {
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    auto ptr = array->data();
    auto tempArray = std::unique_ptr<T[]>(new T[max + 1]);

    // While there are elements in the left or right runs
    for (size_t index = min; index <= max; index++) {
        // If left run head exists and is <= existing right run head.
        if (firstIndex <= mid &&
            (secondIndex > max || ptr[firstIndex] <= ptr[secondIndex])) {
            tempArray[index] = ptr[firstIndex];
            firstIndex++;
        }

        else {
            tempArray[index] = ptr[secondIndex];
            secondIndex++;
        }
    }

    // transfer to the initial array
    memcpy(ptr + min, tempArray.get() + min, (max - min) * sizeof(T));
    //  for (int index = min; index <= max; index++) ptr[index] =
    //  tempArray[index];
}

/**
 * @brief
 *
 * @tparam T
 * @tparam N
 * @param array
 * @param min
 * @param max
 * @param threshold
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
 * @brief
 *
 */
void test() {
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
}

/**
 * @brief
 *
 * @return int
 */
int main() {
    std::srand(std::time(nullptr));
    test();
    return 0;
}
