/**
 * @file
 * @brief Swapping two numbers using Bitwise operator
 * More about it: https://betterexplained.com/articles/swap-two-variables-using-xor
 * @details
 * This program is part of bitwise manipulation programs, this one
 * specifically helps us swap two numbers without using an auxillary
 * variable.
 * @author [Puneet Tripathi](https://github.com/PuneetTri)
 */

#include<iostream>
using namespace std;

int main() {
    int a, b;

    /* XOR bitwise operator compares two corresponding bits and return
    *  value 0 if both are equal and returns 1 if both are not equal
    */

    a=2; // Binary equivalent to 2 is 0010
    b=3; // Binary equivalent to 3 is 0011

    cout << "Before swapping" << endl;
    cout << "A: " << a << ", B: " << b << endl;

    a = a^b; // Binary equivalent to 2^3 is 0001 or in decimal: 1
    b = a^b; // Binary equivalent to 1^3 is 0010 or in decimal: 2(Originally: 3)
    a = a^b; // Binary equivalent to 1^2 is 0011 or in decimal: 3(Originally: 2)
    // Value of 'a' has been swapped with value of 'b'

    /* This happens because bit equivalent to XOR of any two numbers
    *  returns a binary value that is a hybrid of 'a' and 'b', that means
    *  that it stores information from both 'a' and 'b'.
    *  We can access this information by doing a XOR with either
    *  'a' or 'b'. For example: hybrid^a removes information of 'a' from the
    *  hybrid, leaving 'b'. 
    *  Proof:
    *  a = a^b
    *  a = (a^b)^a
    *  a = (a^a)^b --> Order does not matter in case of XOR
    *  a = (0)^b --> XOR of a number with itself, results in 0 (Example: 2^2=0)
    *  a = b --> XOR of any number with 0 results in the number itself
    *  Hence, proved that hybrid or (a^b) stores information from both the variables
    *  and can be accessed by XOR-ing it with the other variable
    */

    cout << "After swapping" << endl;
    cout << "A: " << a << ", B: " << b;
}
