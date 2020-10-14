/**
 * @file
 * @brief C++ Program for Modular Exponentiation Iteratively.
 * Calculate the value of an integer a raised to an integer exponent b 
 * under modulo c. 
 * @note The time complexity of this approach is O(log b).
 *
 * Example:
 * (4^3) % 5 (where ^ stands for exponentiation and % for modulo)
 * (4*4*4) % 5
 * (4 % 5) * ( (4*4) % 5 )
 * 4 * (16 % 5)
 * 4 * 1
 * 4
 * We can also verify the result as 4^3 is 64 and 64 modulo 5 is 4
 */

#include <iostream> 


/// Iterative Function to calculate a raised to exponent b 
/// under modulo c in O(log b) using modular exponentiation.
int power(int a, unsigned int b, int c) 
{ 
	int ans = 1;	    	/// Initialize the answer to be returned 

	a = a % c;          	/// Update a if it is more than or 
				/// equal to c 

	if (a == 0) 
	{
	    return 0;       	/// In case a is divisible by c; 
	}
	
	while (b > 0) 
	{ 
		/// If b is odd, multiply a with answer 
		if (b & 1) 
		{
			ans = (ans*a) % c; 
		}
		
		/// b must be even now 
		b = b>>1;       // b = b/2 
		a = (a*a) % c; 
	}
	
	return ans; 
} 

/// Main Function
int main() 
{ 	
	/// Give two numbers num1, num2 and modulo m
	int num1 = 2; 
	int num2 = 5; 
	int m = 13; 
	
	std::cout << "The value of "<<num1<<" raised to exponent "<<num2<<" 
	under modulo "<<m<<" is " << power(num1, num2, m); 
	/// std::cout << "The value of "<<num1<<" raised to exponent "<<num2<<" 
	/// under modulo "<<m<<" is " << power(num1, num2, m); 
 
} 

