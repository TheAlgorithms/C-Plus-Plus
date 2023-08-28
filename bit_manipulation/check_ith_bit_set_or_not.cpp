#include <iostream>
using namespace std;

/*
 * @file
 * @brief Implementation to
 * [Check ith bit is set or not ]
 *
 *
 * -------------------------------------------------------------------
 * @details
 *
 * We are given two interger N and I , we have to check if ith bit of n is set
or not
 *
 *
 * "set bit" refers to a binary digit (bit) that has a value of 1.
 * Conversely, an "unset bit" refers to a binary digit that has a value of 0.
 *

------------------------------------------------------------------------
 * let's go through the code with an example
 * to make it clearer. We'll use n as 21 (binary: 10101)
 * and i as 4. Our goal is to determine whether the 4th bit
 * (from the right) of the number 21 is set or not.
 *



Explaination

 1. Calculate the Mask:
k is 4, so we calculate the mask by left-shifting 1 by (i - 1) positions

mask = 1 << (4 - 1) = 1 << 3 = 8 (binary: 1000)

2. Bitwise AND Operation:

                n = 21    (binary: 10101)
              & mask = 8  (binary: 01000)
                         ----------------------
                           (binary: 00000) --- Not a set bit



3. Condition Check:
The condition if (n & mask) evaluates to true because the result of the AND
operation is non-zero. if the AND Operation is non - zero then the ith Bit is
Set Bit otherwise not


In above example the result of AND of n = 21 & mask = 8 is 0 hence ith bit is a
not a set bit.


This code is contributed by
@author Gurjot Singh (https://github.com/gurjotsaini53)

*/

void isIthBitSet(int n, int i) {
    int mask = 1 << (i - 1);
    if (n & mask) {
        cout << "SET BIT " << endl;
    } else {
        cout << "NOT SET BIT" << endl;
    }
}
int main() {
    int n = 21, i = 4;

    isIthBitSet(n, i);  // will print NOT SET BIT

    return 0;
}
