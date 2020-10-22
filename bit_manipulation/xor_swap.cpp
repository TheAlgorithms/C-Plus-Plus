/**
 * @file
 * @brief Swapping two integers using xor.
 *
 * @author [Ravishankar Joshi](https://github.com/ravibitsgoa)
 */

#include <iostream>
using std::cout;
using std::endl;

int main() {
    int a = 1, b = 2;
    cout << "a = " << a << ", b = " << b << endl;
    a ^= b;
    b ^= a;
    a ^= b;
    cout << "a = " << a << ", b = " << b << endl;
}