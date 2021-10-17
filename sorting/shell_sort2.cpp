/**
 * \file
 * \brief [Shell sort](https://en.wikipedia.org/wiki/Shell_sort) algorithm
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>  // for std::swap
#include <vector>

/** pretty print array
 * \param[in] arr array to print
 * \param[in] LEN length of array to print
 */
template <class T>
void show_data(T *arr, size_t LEN) {
    size_t i;

    for (i = 0; i < LEN; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

/** pretty print array
 * \param[in] arr array to print
 * \param[in] N length of array to print
 */
template <typename T, size_t N>
void show_data(T (&arr)[N]) {
    show_data(arr, N);
}

/** \namespace sorting
 * \brief Sorting algorithms
 */
namespace sorting {
/**
 * Optimized algorithm - takes half the time by utilizing
 * Mar
 **/
template <typename T>
void shell_sort(T *arr, size_t LEN) {
    const unsigned int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    const unsigned int gap_len = 8;
    size_t i, j, g;

    for (g = 0; g < gap_len; g++) {
        unsigned int gap = gaps[g];
        for (i = gap; i < LEN; i++) {
            T tmp = arr[i];

            for (j = i; j >= gap && (arr[j - gap] - tmp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = tmp;
        }
    }
}

/** function overload - when input array is of a known length array type
 */
template <typename T, size_t N>
void shell_sort(T (&arr)[N]) {
    shell_sort(arr, N);
}

/** function overload - when input array is of type std::vector,
 * simply send the data content and the data length to the above function.
 */
template <typename T>
void shell_sort(std::vector<T> *arr) {
    shell_sort(arr->data(), arr->size());
}

}  // namespace sorting

using sorting::shell_sort;

/**
 * function to compare sorting using cstdlib's qsort
 **/
template <typename T>
int compare(const void *a, const void *b) {
    T arg1 = *static_cast<const T *>(a);
    T arg2 = *static_cast<const T *>(b);

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;

    //  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    //  return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

/**
 * Test implementation of shell_sort on integer arrays by comparing results
 * against std::qsort.
 */
void test_int(const int NUM_DATA) {
    // int array = new int[NUM_DATA];
    int *data = new int[NUM_DATA];
    int *data2 = new int[NUM_DATA];
    // int array2 = new int[NUM_DATA];
    int range = 1800;

    for (int i = 0; i < NUM_DATA; i++)
        data[i] = data2[i] = (std::rand() % range) - (range >> 1);

    /* sort using our implementation */
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using shell_sort2: " << elapsed_time
              << "s\n";

    /* sort using std::qsort */
    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<int>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using std::qsort: " << elapsed_time
              << "s\n";

    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);  // ensure that our sorting results match
                                      // the standard results
    }

    delete[] data;
    delete[] data2;
}

/**
 * Test implementation of shell_sort on float arrays by comparing results
 * against std::qsort.
 */
void test_f(const int NUM_DATA) {
    // int array = new int[NUM_DATA];
    float *data = new float[NUM_DATA];
    float *data2 = new float[NUM_DATA];
    // int array2 = new int[NUM_DATA];
    int range = 1000;

    for (int i = 0; i < NUM_DATA; i++) {
        data[i] = data2[i] = ((std::rand() % range) - (range >> 1)) / 100.;
    }

    /* sort using our implementation */
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using shell_sort2: " << elapsed_time
              << "s\n";

    /* sort using std::qsort */
    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<float>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using std::qsort: " << elapsed_time
              << "s\n";

    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);  // ensure that our sorting results match
                                      // the standard results
    }

    delete[] data;
    delete[] data2;
}

/** Main function */
int main(int argc, char *argv[]) {
    // initialize random number generator - once per program
    std::srand(std::time(NULL));

    test_int(100);  // test with sorting random array of 100 values
    std::cout << "Test 1 - 100 int values - passed. \n";
    test_int(1000);  // test with sorting random array of 1000 values
    std::cout << "Test 2 - 1000 int values - passed.\n";
    test_int(10000);  // test with sorting random array of 10000 values
    std::cout << "Test 3 - 10000 int values - passed.\n";

    test_f(100);  // test with sorting random array of 100 values
    std::cout << "Test 1 - 100 float values - passed. \n";
    test_f(1000);  // test with sorting random array of 1000 values
    std::cout << "Test 2 - 1000 float values - passed.\n";
    test_f(10000);  // test with sorting random array of 10000 values
    std::cout << "Test 3 - 10000 float values - passed.\n";

    int i, NUM_DATA;

    if (argc == 2)
        NUM_DATA = atoi(argv[1]);
    else
        NUM_DATA = 200;

    // int array = new int[NUM_DATA];
    int *data = new int[NUM_DATA];
    // int array2 = new int[NUM_DATA];
    int range = 1800;

    std::srand(time(NULL));
    for (i = 0; i < NUM_DATA; i++) {
        // allocate random numbers in the given range
        data[i] = (std::rand() % range) - (range >> 1);
    }

    std::cout << "Unsorted original data: " << std::endl;
    show_data(data, NUM_DATA);
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);  // perform sorting
    std::clock_t end = std::clock();

    std::cout << std::endl
              << "Data Sorted using custom implementation: " << std::endl;
    show_data(data, NUM_DATA);

    double elapsed_time = (end - start) * 1.f / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting: " << elapsed_time << "s\n" << std::endl;

    delete[] data;
    return 0;
}
