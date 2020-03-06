#include <algorithm>
#include <iostream>


int main() {
     int n,                      // the number of length of array
          lib_size, index_pos,
          *index,                 // input (unsorted array)
          *gaps,                  // gaps
          *library[2];            // libraries
     bool target_lib, *numbered;

     std::cout << "Enter the number of length of array : ";
     std::cin >> n;
     index = new int[n];

     for (int i = 0; i < 2; i++) library[i] = new int[n];

     gaps = new int[n + 1];
     numbered = new bool[n + 1];

     std::cout << "Enter any " << n << " Numbers for unsorted array : ";

     for (int i = 0; i < n; i++) std::cin >> index[i];

     lib_size = 1;
     index_pos = 1;
     target_lib = 0;
     library[target_lib][0] = index[0];

     while (index_pos < n) {
     // binary search
          int insert =
               std::distance(library[target_lib],
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

     // output

     std::cout << "Sorted output :" << std::endl;

     for (int i = 0; i < n; i++) {
          if (numbered[i] == true) {
                    std::cout << gaps[i] << std::endl;
          }

          if (i < lib_size) {
                    std::cout << library[target_lib][i] << std::endl;
          }
     }
}
