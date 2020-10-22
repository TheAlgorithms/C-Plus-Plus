/**
 * @file
 * @brief Finding if a number is a power of 2.
 *
 * @details
 * To find if a number is a power of 2, we can check if bitwise AND of number
 * and number - 1 is zero or not. Only for the numbers which are a power of 2,
 * bitwise AND(x, x-1) is zero.
 *
 * @author [Ravishankar Joshi](https://github.com/ravibitsgoa)
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

bool ispower2(int x) { return x > 0 && (x & (x - 1)) == 0; }

int main() {
    vector<int> arr{1, 2, 3, 4, 8, 10};
    for (int x : arr) {
        cout << x << " is " << (ispower2(x) ? "" : "not ") << "a power of 2."
             << endl;
    }
}