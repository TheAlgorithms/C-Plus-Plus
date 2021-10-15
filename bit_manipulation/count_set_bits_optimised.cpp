#include <iostream>

/**
 * Optimised way of counting the number of set bits in a number.
 * The function iterates over ONLY the set bits.
 * Hence, the complexity of the function is exactly equal to the answer itself.
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
