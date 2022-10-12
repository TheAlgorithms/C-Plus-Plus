/**
 * @file
 * @brief Algorithm to find largest x such that p^x divides n! (factorial) using Legendre's Formula.
 * @details Given an integer n and a prime number p, the task is to find the largest x such that 
 * p^x (p raised to power x) divides n! (factorial). This will be done using Legendre's formula:
 * x = [n/(p^1)] + [n/(p^2)] + [n/(p^3)] + \ldots + 1
 * @see more on https://math.stackexchange.com/questions/141196/highest-power-of-a-prime-p-dividing-n
 * @author [uday6670](https://github.com/uday6670)
 */

#include <iostream> /// for std::cin and std::cout
#include <cassert>  /// for assert

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

	/** 
	 * @brief Function to calculate largest power
	 * @param n number
         * @param p prime number
	 * @returns largest power
	 */ 
    uint64_t largestPower(uint32_t n, const uint16_t& p)  
    {  
        // Initialize result  
        int x = 0;  
  
        // Calculate result 
        while (n)  
        {  
            n /= p;  
            x += n;  
        }  
        return x;  
    }

}  // namespace math

/**
 * @brief Function for testing largestPower function.
 * test cases and assert statement.
 * @returns `void`
*/
static void test()
{
	uint8_t test_case_1 = math::largestPower(5,2);
	assert(test_case_1==3);
	std::cout<<"Test 1 Passed!"<<std::endl;
	
	uint16_t test_case_2 = math::largestPower(10,3);
	assert(test_case_2==4);
	std::cout<<"Test 2 Passed!"<<std::endl;
	
	uint32_t test_case_3 = math::largestPower(25,5);
	assert(test_case_3==6);
	std::cout<<"Test 3 Passed!"<<std::endl;
	
	uint32_t test_case_4 = math::largestPower(27,2);
	assert(test_case_4==23);
	std::cout<<"Test 4 Passed!"<<std::endl;
	
	uint16_t test_case_5 = math::largestPower(7,3);
	assert(test_case_5==2);
	std::cout<<"Test 5 Passed!"<<std::endl;
} 

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() 
{ 
    test(); // execute the tests
    return 0;
} 
