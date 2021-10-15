/**
 * @file
 * @brief Optimised way of counting the number of set bits in a number.
 * @details
 * There are multiple ways of counting the number of set bits. One naive approach is to 
 * iterate over all the bits and check if the current bit is set or not.
 * An optimised way to solve the problem is to iterate over ONLY the set bits instead of all the bits.
 * One way to do so is to make use of the mathematical property of BITWISE AND operator.
 * When we do a bitwise AND of a number with it's predecessor, then the right most set bit of the number is unset.
 * We can use this property to find the number of set bits in a number in an optimised manner.
 * @author abhishek vanjani(https://github.com/KillerAV)
 */

#include <iostream> /// For input output
#include <cassert> /// For asserts

/**
 * Function to count number of set bits in a number.
 * @param N: The number whose set bit count is needed to be calculated.
 */ 
int countSetBitsOptimised(int N) {
    int ans=0;

    while(N) {
        // This unsets the right most set bit.
        N=N&(N-1);
        ans++;
    }

    return ans;
}
int main() 
{
    assert(1==countSetBitsOptimised(1));
    assert(1==countSetBitsOptimised(2));
    assert(2==countSetBitsOptimised(3));
    assert(1==countSetBitsOptimised(4));
    assert(2==countSetBitsOptimised(5));
    assert(2==countSetBitsOptimised(6));
    assert(3==countSetBitsOptimised(7));
    assert(1==countSetBitsOptimised(8));
    assert(2==countSetBitsOptimised(9));
    assert(2==countSetBitsOptimised(10));
}
