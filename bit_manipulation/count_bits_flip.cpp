/**
 * @file
 * @brief Implementation to
 * [Count number of bits to be flipped to convert A to B]
 * (https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/)
 * in an integer.
 *
 * @details
 * We are given two numbers A and B. Our task is to count the number of bits
 * needed to be flipped to convert A to B.
 *
 * Explanation:
 *
 * A  = 01010 B  = 10100
 * As we can see, the bits of A that need to be flipped are 01010.
 * If we flipthese bits, we get 10100, which is B.
 *
 * Worst Case Time Complexity: O(log n)
 * Space complexity: O(1)
 * @author [Yash Raj Singh](https://github.com/yashrajyash)
 */
#include <cassert>   /// for assert
#include <cstdint>
#include <iostream>  /// for IO operations
#include <iostream>

class Solution {
public:
    int minBitFlips(int start, int goal) {
        int xor_value = start ^ goal; // Step 1: Find XOR of start and goal
        int res = 0;
        
        // Step 2: Count number of 1s in XOR result
        while (xor_value > 0) {
            res += xor_value & 1; // Increment count if last bit is 1
            xor_value >>= 1;      // Right shift to check next bit
        }
        
        return res; // Return total bit flips required
    }
};

int main() {
    Solution solution;
    int start, goal;
    
    // Taking user input
    std::cout << "Enter start value: ";
    std::cin >> start;
    std::cout << "Enter goal value: ";
    std::cin >> goal;
    
    // Calculating minimum bit flips
    int result = solution.minBitFlips(start, goal);
    
    // Displaying the result
    std::cout << "Minimum bit flips required: " << result << std::endl;

    return 0;
}
