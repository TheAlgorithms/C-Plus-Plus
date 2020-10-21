/**
 * @file
 * @brief Algorithm to find sum of binomial coefficients of a given positive integer.
 * @details Given a positive integer n, the task is to find the sum of binomial coefficient i.e
 * nC0 + nC1 + nC2 + ……. + nCn-1 + nCn
 * By induction, we can prove that the sum is equal to 2^n
 * @source https://en.wikipedia.org/wiki/Binomial_coefficient#Sums_of_the_binomial_coefficients
 * @author muskan0719 [https://github.com/muskan0719]
 */
#include<iostream> /// for std::cin and std::cout
#include<cassert>  /// for assert

/** 
 * Function to calculate sum of binomial coefficients
 * @param n number
 * @return Sum of binomial coefficients of number 
 */
int binomialCoeffSum(int n) 
{ 
    //Calculating 2^n  
	return (1 << n); 
}

/**
 * Function for testing binomialCoeffSum function.
 * test cases and assert statement.
 * @returns `void`
*/
static void test()
{
	int test_case_1 = binomialCoeffSum(2);
	assert(test_case_1==4);
	std::cout<<"Test_case_1 Passed!"<<std::endl;
	
	int test_case_2 = binomialCoeffSum(3);
	assert(test_case_2==8);
	std::cout<<"Test_case_2 Passed!"<<std::endl;
	
	int test_case_3 = binomialCoeffSum(4);
	assert(test_case_3==16);
	std::cout<<"Test_case_3 Passed!"<<std::endl;
	
	int test_case_4 = binomialCoeffSum(5);
	assert(test_case_4==32);
	std::cout<<"Test_case_4 Passed!"<<std::endl;
	
	int test_case_5 = binomialCoeffSum(7);
	assert(test_case_5==128);
	std::cout<<"Test_case_5 Passed!"<<std::endl;
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
