/**
 * @file
 * @brief Algorithms to find divisor of all natural numbers.
 * @author [Tee Chia Suen](https://github.com/ChiaSuen)
 */

#include <cassert>   /// for assert
#include <iostream>
#include <vector> 	//for declaring undefined size array


/**
 * @namespace <check from other files in this repo>
 */
namespace math {



/**
 * @brief Function to calculate the divisors and append it to a vector array
 * @tparam int 
 * @param Number to calculate the divisors
 */
template <typename T>
std::vector< int > Divisors(T n)
{
    
	int divisor = 0;	//divisor 
	std::vector< int > divisors;	//divisor array
	
	for (divisor = 1; divisor * divisor < n; divisor++) {
		if (n % divisor == 0){
			divisors.push_back(divisor);
		}	
	}
	if (divisor - (n / divisor) == 1) {
		divisor--;
	}
	for (int arr_size = int(divisors.size()) - 1; arr_size >= 0; arr_size--) {
		if (n % divisors[arr_size] == 0){
			divisors.push_back(n/divisors[arr_size]);
		}		
	}
	
	return divisors;
}

/**
 * @brief Function to print vector array of divisors
 * @tparam std::vector< int > 
 * @param Vector array of divisors returned from the calculation function
 */
template <typename T>
void printDivisors(T divisors)
{
    for (int arr_size = 0; arr_size <= divisors.size() - 1; arr_size++) {
	    std::cout << divisors[arr_size] << " ";
	}
}
} // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
   	
	int test = 40;  //test number
	std::vector< int > test_case = math::Divisors(test);
	std::vector< int > divisors {1, 2, 4, 5, 8, 10, 20, 40};
	assert(test_case == divisors);
	std::cout<<"Test 1 Passed!"<<std::endl;
    
   	 //2nd test
    	test = 60;  //test number
	test_case = math::Divisors(test);
	divisors = {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60};
	assert(test_case == divisors);
	std::cout<<"Test 2 Passed!"<<std::endl;
    
    	//3rd test
    	test = 50;  //test number
    	test_case = math::Divisors(test);
	divisors = {1, 2, 5, 10, 25, 50};
	assert(test_case == divisors);
	std::cout<<"Test 3 Passed!"<<std::endl;
    
    	//4th test
   	 test = 88;  //test number
    	test_case = math::Divisors(test);
	divisors = {1, 2, 4, 8, 11, 22, 44, 88};
	assert(test_case == divisors);
	std::cout<<"Test 4 Passed!"<<std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

 int main()
{
    test();
	return 0;
}


