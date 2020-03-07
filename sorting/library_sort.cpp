#include <algorithm>
#include <iostream>

void librarySort(int *index, int n) {
    int lib_size, index_pos,
        *gaps,        // gaps
        *library[2];  // libraries

    bool target_lib, *numbered;

    for (int i = 0; i < 2; i++)
        library[i] = new int[n];

    gaps = new int[n + 1];
    numbered = new bool[n + 1];

    lib_size = 1;
    index_pos = 1;
    target_lib = 0;
    library[target_lib][0] = index[0];

    while (index_pos < n) {
        // binary search
        int insert = std::distance(
            library[target_lib],
            std::lower_bound(library[target_lib],
                             library[target_lib] + lib_size, index[index_pos]));

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
            gaps[insert] = index[index_pos];
            index_pos++;
        }
    }

    int index_pos_for_output = 0;
    for (int i = 0; index_pos_for_output < n; i++) {
        if (numbered[i] == true) {
            // std::cout << gaps[i] << std::endl;
            index[index_pos_for_output] = gaps[i];
            index_pos_for_output++;
        }

        if (i < lib_size) {
            // std::cout << library[target_lib][i] << std::endl;
            index[index_pos_for_output] = library[target_lib][i];
            index_pos_for_output++;
        }
    }
}

int main() {
    // ---example--
    int index_ex[] = {-6, 5, 9, 1, 9, 1, 0, 1, -8, 4, -12};
    int n_ex = sizeof(index_ex) / sizeof(index_ex[0]);

    librarySort(index_ex, n_ex);
    std::cout << "sorted array :" << std::endl;
    for (int i = 0; i < n_ex; i++)
        std::cout << index_ex[i] << " ";
    std::cout << std::endl;

    /* --output--
    sorted array :
    -12 -8 -6 0 1 1 1 4 5 9 9
    */
}
