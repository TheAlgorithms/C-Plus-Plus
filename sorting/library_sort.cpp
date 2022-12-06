#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>

namespace sorting {
//using array
void librarySort(int *arr, int n) {
    int lib_size, index_pos,
        *gaps,        // gaps
        *library[2];  // libraries

    bool target_lib, *numbered;

    for (int i = 0; i < 2; i++) library[i] = new int[n];

    gaps = new int[n + 1];
    numbered = new bool[n + 1];

    lib_size = 1;
    index_pos = 1;
    target_lib = 0;
    library[target_lib][0] = arr[0];

    while (index_pos < n) {
        // binary search
        int insert = std::distance(
            library[target_lib],
            std::lower_bound(library[target_lib],
                             library[target_lib] + lib_size, arr[index_pos]));

        // if there is no gap to insert a new index ...

        if (numbered[insert] == true) {
            int prov_size = 0, next_target_lib = !target_lib;

            // update library and clear gaps

            for (int i = 0; i <= n; i++) {
                if (numbered[i] == true) {
                    library[next_target_lib][prov_size] = gaps[i];
                    prov_size++;
                    numbered[i] = false;
                }

                if (i <= lib_size) {
                    library[next_target_lib][prov_size] =
                        library[target_lib][i];
                    prov_size++;
                }
            }

            target_lib = next_target_lib;
            lib_size = prov_size - 1;
        } else {
            numbered[insert] = true;
            gaps[insert] = arr[index_pos];
            index_pos++;
        }
    }

    int index_pos_for_output = 0;
    for (int i = 0; index_pos_for_output < n; i++) {
        if (numbered[i] == true) {
            // std::cout << gaps[i] << std::endl;
            arr[index_pos_for_output] = gaps[i];
            index_pos_for_output++;
        }

        if (i < lib_size) {
            // std::cout << library[target_lib][i] << std::endl;
            arr[index_pos_for_output] = library[target_lib][i];
            index_pos_for_output++;
        }
    }
}
//using vector
void librarySort(std::vector<int> *arr) {
    size_t n = arr->size();

    int lib_size, index_pos,
        *gaps,        // gaps
        *library[2];  // libraries

    bool target_lib, *numbered;

    for (int i = 0; i < 2; i++) library[i] = new int[n];

    gaps = new int[n + 1];
    numbered = new bool[n + 1];

    lib_size = 1;
    index_pos = 1;
    target_lib = 0;
    library[target_lib][0] = arr[0][0];

    while (index_pos < n) {
        // binary search
        int insert = std::distance(
            library[target_lib],
            std::lower_bound(library[target_lib],
                             library[target_lib] + lib_size, arr[0][index_pos]));

        // if there is no gap to insert a new index ...

        if (numbered[insert] == true) {
            int prov_size = 0, next_target_lib = !target_lib;

            // update library and clear gaps

            for (int i = 0; i <= n; i++) {
                if (numbered[i] == true) {
                    library[next_target_lib][prov_size] = gaps[i];
                    prov_size++;
                    numbered[i] = false;
                }

                if (i <= lib_size) {
                    library[next_target_lib][prov_size] =
                        library[target_lib][i];
                    prov_size++;
                }
            }

            target_lib = next_target_lib;
            lib_size = prov_size - 1;
        } else {
            numbered[insert] = true;
            gaps[insert] = arr[0][index_pos];
            index_pos++;
        }
    }

    int index_pos_for_output = 0;
    for (int i = 0; index_pos_for_output < n; i++) {
        if (numbered[i] == true) {
            // std::cout << gaps[i] << std::endl;
            arr[0][index_pos_for_output] = gaps[i];
            index_pos_for_output++;
        }

        if (i < lib_size) {
            // std::cout << library[target_lib][i] << std::endl;
            arr[0][index_pos_for_output] = library[target_lib][i];
            index_pos_for_output++;
        }
    }
}
}

void tests() {
    // positive case
    int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
    std::cout << "Test 1... ";
    sorting::librarySort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << '\n';

    // negative case
    int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
    std::cout << "Test 2... ";
    sorting::librarySort(arr2, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "passed" << '\n';

    // mix positive and negative
    int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
    std::cout << "Test 3... ";
    sorting::librarySort(arr3, 8);
    assert(std::is_sorted(arr3, arr3 + 8));
    std::cout << "passed" << '\n';

    // using vector
    std::vector<int> arr4({4, -7, 0, 17, -2, 6, 1, -6});
    std::cout << "Test 4... ";
    sorting::librarySort(&arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;
}

int main() { 
    tests(); 

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter Integer" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::librarySort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}