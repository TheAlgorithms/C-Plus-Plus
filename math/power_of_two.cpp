/**
 * @file
 * @brief Implementation to check whether a number is a power of 2 or not.
 *
 * @details
 * This algorithm uses bit manipulation to check if a number is a power of 2 or
 * not.
 *
 * ### Algorithm
 * Let the input number be n, then the bitwise and between n and n-1 will let us
 * know whether the number is power of 2 or not
 *
 * For Example,
 * If N= 32 then N-1 is 31, if we perform bitwise and of these two numbers then
 * the result will be zero, which indicates that it is the power of 2
 * If N=23 then N-1 is 22, if we perform bitwise and of these two numbers then
 * the result will not be zero , which indicates that it is not the power of 2
 * \note This implementation is better than naive recursive or iterative
 * approach.
 *
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 */

//Added self implementation Cases Contribution

#include <iostream>  /// for std::cout
#include <cassert>   ///for assert


/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Function to test above algorithm
 * @param n description
 * @returns int
 */

int power_of_two(int n) {
    /**
     * This function finds whether a number is power of 2 or not
     * @param n value for which we want to check
     * returns 1 if n is power of 2
     * returns 0 if n is not a power of 2
     */
    /// result stores the
    /// bitwise and of n and n-1
    int result = n & (n - 1);
    
    if(result == 0)  return 1 ; //yes it is
    else return 0; // no it is not

}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {

    std::cout << "First case testing.. \n"; // for n = 32 return 1
    assert(math::power_of_two(32) == 1);
    std::cout << "Passed\n";

    std::cout << "Second case testing.. \n"; // for n = 5 return 0
    assert(math::power_of_two(5) == 0);
    std::cout << "Passed\n";

    std::cout << "Third case testing.. \n"; // for n = 232 return 0
    assert(math::power_of_two(232) == 0);
    std::cout << "Passed\n";

    std::cout << "All test cases passed! \n";
}

/**
 * @brief take user input
 * @returns void
 */

void user_input_test() {

    int n = 0; // input from user
    
    std::cout << "Enter a number " << std::endl;
    std::cin >> n; 

    /// function call with @param n
    int result = math::power_of_two(n);
    if(result == 1) std::cout << "Yes, the number " << n << " is a power of 2 \n"; 
    else std::cout << "No, the number " << n << " is not a power of 2\n";

}


/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    
    test(); //run self-test implementations

    //UN - COMMENT BELOW LINE TO TAKE USER INPUTS
    // user_input_test(); 

    
    return 0;
}
