// count_set_bits.cpp
// Author: Abhijeet Kundu
// Description: Counts number of set bits (1s) in the binary representation of an integer
// using Brian Kernighan’s Algorithm.
// Time Complexity: O(k) where k is number of set bits

#include <iostream>
#include <cassert>

int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // clears the least significant set bit
        count++;
    }
    return count;
}

int main() {
    assert(countSetBits(0) == 0);
    assert(countSetBits(5) == 2);   // 101 → 2 set bits
    assert(countSetBits(15) == 4);  // 1111 → 4 set bits

    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;
    std::cout << "Number of set bits: " << countSetBits(n) << "\n";
    return 0;
}
