/**
 * @file
 * @brief Implementation to [swap the values of two variables using bitwise XOR]
 * (https://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/) in an
 * integer.
 *
 * @details
 * We are given two variables let's say num1 and num2.
 * We are supposed to swap OR interchange the values
 * of these two variables using bitwise XOR. 
 * 
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1) 
 * @author [Suyash Mishra](https://github.com/Suyash878)
 */

#include<cassert> // for assert
#include<iostream>  // for I/O operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace swapUsingXOR
 * @brief Function for swapping two variables using bitwise
 * XOR.
 */
namespace swap_using_XOR
{
/**
 * @brief The main function swaps the values of num1 and num2
 * @param num1 is the first number.
 * @param num2 is the number with which num1 will be swapped with.
 * @returns this will return a pair of two integers.
*/
std::pair<std::int64_t, std::int64_t>swapUsingXOR(std ::int64_t num1,
                                                std ::int64_t num2) {  // int64_t is preferred over int so

    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;

    return std::make_pair(num1,num2);
}
}  // namespace swap_Using_XOR
}  // namespace bit_manipulation
/**
 * @brief Self-test implementations
 * @returns void
 */

static void test() {
    // Test cases
    //num1 = 5 and num2 = 4 -->(implementing swap)--> returns num1 = 4 ,num2 = 5 
    auto result1 = bit_manipulation::swap_using_XOR::swapUsingXOR(5, 4);
    assert(result1.first == 4 && result1.second == 5);

    //num1 = 0 and num2 = 0 -->(implementing swap)--> returns num1 = 0 ,num2 = 0
    auto result2 = bit_manipulation::swap_using_XOR::swapUsingXOR(0, 0);
    assert(result2.first == 0 && result2.second == 0);

    //num1 = -1 and num2 = -1 -->(implementing swap)--> returns num1 = -1 ,num2 = -1
    auto result3 = bit_manipulation::swap_using_XOR::swapUsingXOR(-1, -1);
    assert(result3.first == -1 && result3.second == -1);

    //num1 = 123 and num2 = 456 -->(implementing swap)--> returns num1 = 456 ,num2 = 123
    auto result4 = bit_manipulation::swap_using_XOR::swapUsingXOR(123, 456);
    assert(result4.first == 456 && result4.second == 123);

    //num1 = 7 and num2 = 9 -->(implementing swap)--> returns num1 = 9 ,num2 = 7
    auto result5 = bit_manipulation::swap_using_XOR::swapUsingXOR(7, 9);
    assert(result5.first == 9 && result5.second == 7);

    // Add more test cases as needed
    std::cout << "All the test cases successfully passed!" << std::endl;
    
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); //runs self tests.
    return 0;
}



















