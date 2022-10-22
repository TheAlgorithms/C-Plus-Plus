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

#include<iostream>  // For standard I/O, in our case printing values of variable 'a' and 'b'
#include<cassert> // For assert

bool bitwiseSwap(int a, int b) {
    /* Explanation of below code is assuming that value of a = 2,
    *  and value of b = 3.
    *  For the test-case #1, value of a and b will be 2 and 3 respectively
    */

    /* XOR bitwise operator compares two corresponding bits and return
    *  value 0 if both are equal and returns 1 if both are not equal
    */

    
    // a = 2; Binary equivalent to 2 is 0010
    // b = 3; Binary equivalent to 3 is 0011

    /* Storing value of a and b in temporary variables to later check if
    *  values did swap or not.
    */
    int temp_a = a;
    int temp_b = b;

    std::cout << "Before swapping" << std::endl;
    std::cout << "A: " << a << ", B: " << b << std::endl;

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

    std::cout << "After swapping" << std::endl;
    std::cout << "A: " << a << ", B: " << b << std::endl;
    std::cout << std::endl; // For better spacing between test-cases

    // Return true if values swapped or else return false
    if(temp_a == b && temp_b == a) {
        return true;
    } else {
        return false;
    }
}

static void test() {
    /* Following tests would check for multiple cases that values of 
    variables do actually swap */
    std::cout << "Test-case: #1" << std::endl;
    assert(bitwiseSwap(2,3) == true); // TC #1
    std::cout << "Test-case: #2" << std::endl;
    assert(bitwiseSwap(0,53) == true); // TC #2
    std::cout << "Test-case: #3" << std::endl;
    assert(bitwiseSwap(622,733) == true); // TC #3
    std::cout << "Test-case: #4" << std::endl;
    assert(bitwiseSwap(-8246,-9357) == true); // TC #4
    std::cout << "Test-case: #5" << std::endl;
    assert(bitwiseSwap(7,7) == true); // TC #5
}

int main() {
    test(); // Run multiple testcases to test our algorithm
}
