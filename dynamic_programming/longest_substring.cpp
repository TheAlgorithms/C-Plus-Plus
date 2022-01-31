/**
 * @file
 * brief implementation to find longest substring without repeating characters
 * 
 * @details
 * [Substring] (https://en.wikipedia.org/wiki/Substring)
 * a substring is a contiguous sequence of characters within a string
 * 
 * @author [Anirudh](https://https://github.com/anirudh343)	
 * 
 * ### Implementation
 * 
 * This problem implements the sliding window technique which is a form of dynamic programming.
 * 
 * 1. Iterate through the string array with the "right" variable until a duplicate character is found.
 * 2. Once a dupllicate is found, iterate the "left" variable until it surpasses the duplicate character
 * 3. update the subtringlength variable each iteration
 * 4. return the final string length
*/
#include <cassert> //for assert function (testing purposes)
#include <unordered_set> //for std::unordered_set
#include <string> //for std::string
#include <iostream>

/**
* @brief Returns size of the longest substring
* @param x string to find subtring from
* @returns @param int size of the longest substring
*/
int lls(std::string x)
{
	if (x.size() == 0)
	{
		return 0;
	}
	//if the length of the string is 0 or 1, return that value
	else if (x.size() == 1) {
		return 1;
	}

	std::unordered_set <char> set; //declare unordered set
	int left = 0, right = 0; //declare and initiliaze right and left variables
	int sublength = 0; //initialize sublength variable (substring length)

	while (right < x.length()) //iterate through string with "right" variable
	{
		if (set.count(x[right]) == 0)
		{
			set.insert(x[right]);  //if character is not duplicate, insert into map
		}
		else
		{
			while (set.count(x[right]) == 1)
			{
				set.erase(x[left]);   //if character is duplicate, iterate "left" variable until it surpasses first instance of duplicate character
				left++;
			}
			set.insert(x[right]);
		}
		if (sublength < (right - left + 1))
		{
			sublength = right - left + 1;   // update value of substring variable
		}
		right++;
	}
	return sublength;   // return final value
}

/**
* @brief tests
* @returns void
*/
void test() 
{
	//largest substring is itself
	assert(lls("abcdefghijklmno") == 15);

	//largest substring is "jefw"
	assert(lls("jefwef") == 4);
	
	//largest substring is "edfjbk"
	assert(lls("edfjbkf") == 6);

	std::cout << "All tests passed" << std::endl;
}

/**
* @brief main
* @returns 0
*/
int main() 
{
	test();  //run the tests
	return 0;
}