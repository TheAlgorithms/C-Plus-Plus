/**
 * @file
 * @brief Bitmask example
 * @details
 * (Bitmask)[https://blog.bitsrc.io/the-art-of-bitmasking-ec58ab1b4c03] 
 * example with explanation and with example
 * problem solution using bitmask
 * 
 * @author [Yhtyyar Sahatov](https://github.com/Yhtiyar)
 */

#include <iostream>   /// for IO operations
/**
 * @namespace bitmask
 * @brief Bitmask examples
 */ 
namespace bitmask 
{
/**
 * This function returns the bit representation of mask(number) in given length .
 * @param mask the mask
 * @param n lenght of mask
 * @returns returns the bit representation of mask(number) in given length as string.
 */
std::string to_string(int mask, int n);

/**
 * This function demonstrates basics of bitmask.
 */
void example_basic() {
	// Lets assume we have set of n = 5 elements
	int n = 5;
	
	int e = 0;               // Mask that represents empty set. binary : 00000
	int f = (1 << n) - 1;    // Mask that represents full set.  binary : 11111
	
	std::cout << to_string(f, n) << std::endl;
	
	e ^= (1 << 2);			//Flipping 2nd bit of e. 00000 ^ 00100 = 00100
	e ^= (1 << 1);			//Flipping 1st bit of e. 00100 ^ 00010 = 00110
	int t = e & (1 << 2);   //With & we can check if the n'th bit is 1. If t != 0 then 1, othervise 1; 00110 & 00100 =00100 
	
	e ^= (1 << 2); 			//Flipping 2nd bit of e. 00110 ^ 00100 = 00010		
	f &= (f ^ (1 << 3));	//Setting bit to zero.  Will always set n'th bit to 0 despite of current mask 
							// f = 10111	
	f |= (1 << 1);			//Setting bit to one. Will always set n'th bit to 1 despite of current mask
							// f = 10111
	t = f & e;				// Intersection of 2 sets 10111 & 00010 = 00010
	std::cout << to_string(t, n) << std::endl;
	t = f | e;				// Union of 2 sets 10111 | 00010 = 10111 
	std::cout << to_string(t, n) << std::endl;
	t = f ^ e;				// Difference of 2 sets 10111 ^ 00010 = 10101
	std::cout << to_string(t, n) << std::endl;
}

/**
 * This function demonstrates advanced techniques of using bitmask.
 */
void example_advanced() {
	int n = 3;
	
	int mask = (1 << n) -1;   // 111
	int s = 3;				  // 011
	
	// If Y is subset of X, then X ^ Y will give X without Y (diffirence);
	s = mask ^ s;			  //100
	std::cout<<to_string(s, n);
	
	// We can also run through all subsets of the mask by:
	for (int subset = mask; subset > 0; subset = mask & (subset - 1)) {
		std::cout << to_string(subset, n) << std::endl;
	}
	 
}


/**
 * Definition of declared function
 */
std::string to_string(int mask, int n) {
	std::string result = "";
	for (int i = n - 1; i >= 0; i--)
		result += ((mask & (1 <<i)) ? "1" : "0");   // Checking if i'th bit is 1 or 0
	return result;
}


/**
 * @namespace problem_example
 * @brief Example of problem that can be solved with bitmask
 */
namespace problem_example
{
/**
 *  Problem :  You have n elements with given weights. 
 * 			   You also have bags that could carry weight that usnot more that S.
 * 			   Need to find minimum number of bags to carry given elemnts
 * 
 *  Solution : Dynamical programming on subsets. 
 * 			   Idea : We will run through mask's subsets and try to group it, so weight of group <= S
 * 
 *  Time complexity : O(3^n) with (2^n * n) preprocessing
 **/

const int n = 10;									//Number of elements
int S = 15;											//Max number that bag can carry
int weights[] = {1, 7, 2, 14, 4, 3, 15, 11, 7, 6};	//Weight of elements
int dp[1 << n];
int w[1 << n];										//Sum of weights of masks
int group[1 << n];									//We will memorize how we divided set so we will be able to show groups
const int INF = 1e5;								//Infinity, for DP initializing

/**
 * @brief example of problem solution using bitmask
 * @returns void
 */
void solve() {
	//Running through all possible masks' (sets) and memorizing masks' weight sum
	for (int mask = 1; mask < (1 << n); mask ++) {
		dp[mask] = INF;
		for (int j = 0; j < n; j++) {
			if (mask & (1 << j))
				w[mask] += weights[j];
		}
	}
	dp[0] = 0;	//We can carry 0 element with 0 bag :)
	
	// Running through all masks'
	for (int mask = 1; mask < (1 << n); mask++) {
		//Running through all subsets of mask, and if we can group subset in 1 group so grups weight <= S, we will check if it's optimal solution
		for (int y = mask; y > 0; y = mask & (y - 1)) {
			if (w[y] <= S) {
				if (dp[mask] > dp[mask ^ y] + 1) {
					dp[mask] = dp[mask ^ y] + 1;
					group[mask] = y;			
					group[y] = y;
				}
			}
		}
	}
	
	std::cout << dp[(1 << n) - 1] << std::endl;			//Answer
	
	//Printing all groups
	int curr = (1 <<n) - 1;
	while (curr) {
		int y = group[curr];
		for (int i = 0; i < n; i++)
			if (y & ( 1 << i))
				std::cout << weights[i] << " ";
		std::cout << "\n";
		curr ^= y;
	}
	
}
} //namespace problem_example
} //namespace bitmask

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
	bitmask::example_basic();
	bitmask::example_advanced();
	bitmask::problem_example::solve();
}
