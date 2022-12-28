/**
 * @file
@brief This program is use to print the following pattern<pre>
   \*\*
   \*\*
  \*\*\*\*
  \*\*\*\*
 \*\*\*\*\*\*
 \*\*\*\*\*\*
\*\*\*\*\*\*\*\*
********</pre>
where number of pairs line is given by user
*/
#include <iostream>

/** main function */
int main() {
    int l = 0, st = 2, x = 0, r = 0, z = 0, n = 0, sp = 0;
    std::cout << "Enter number of pair - ";
    std::cin >> x;
    z = x;
    for (r = 1; r <= x; r++) {
        z = z - 1;
        for (n = 1; n <= 2; n++) {
            for (sp = 1; sp <= z; sp++) {
                std::cout << " ";
            }
            for (l = 1; l <= st; l++) {
                std::cout << "\\*";
            }
            std::cout << std::endl;
        }
        st = st + 2;
    }
}
