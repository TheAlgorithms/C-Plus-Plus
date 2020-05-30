#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

// for std::swap
#include <utility>

template <class T>
void show_data(T *arr, size_t LEN) {
    size_t i;

    for (i = 0; i < LEN; i++) std::cout << arr[i] << ", ";
    std::cout << std::endl;
}

template <class T, size_t N>
void show_data(T (&arr)[N]) {
    show_data(arr, N);
}

/**
 * Optimized algorithm - takes half the time by utilizing
 * Mar
 **/
template <class T>
void shell_sort(T *arr, size_t LEN) {
    const unsigned int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    const unsigned int gap_len = 8;
    size_t i, j, g;

    for (g = 0; g < gap_len; g++) {
        unsigned int gap = gaps[g];
        for (i = gap; i < LEN; i++) {
            T tmp = arr[i];

            for (j = i; j >= gap && (arr[j - gap] - tmp) > 0; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = tmp;
        }
    }
}

template <class T, size_t N>
void shell_sort(T (&arr)[N]) {
    shell_sort(arr, N);
}

/**
 * function to compare sorting using cstdlib's qsort
 **/
int compare(const void *a, const void *b) {
    int arg1 = *static_cast<const int *>(a);
    int arg2 = *static_cast<const int *>(b);

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;

    //  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    //  return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

int main(int argc, char *argv[]) {
    int i, NUM_DATA;

    if (argc == 2)
        NUM_DATA = atoi(argv[1]);
    else
        NUM_DATA = 200;

    // int array = new int[NUM_DATA];
    int *data = new int[NUM_DATA];
    int *data2 = new int[NUM_DATA];
    // int array2 = new int[NUM_DATA];
    int range = 1800;

    std::srand(time(NULL));
    for (i = 0; i < NUM_DATA; i++)
        data[i] = data2[i] = (std::rand() % range) - (range >> 1);

    std::cout << "Unsorted original data: " << std::endl;
    show_data(data, NUM_DATA);
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();

    std::cout << std::endl
              << "Data Sorted using custom implementation: " << std::endl;
    show_data(data, NUM_DATA);

    double elapsed_time = (end - start) * 1.f / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting: " << elapsed_time << "s\n" << std::endl;

    start = std::clock();
    qsort(data2, NUM_DATA, sizeof(data2[0]), compare);
    end = std::clock();
    std::cout << "Data Sorted using cstdlib qsort: " << std::endl;
    show_data(data2, NUM_DATA);

    elapsed_time = (end - start) * 1.f / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting: " << elapsed_time << "s\n" << std::endl;

    free(data);
    free(data2);
    return 0;
}
