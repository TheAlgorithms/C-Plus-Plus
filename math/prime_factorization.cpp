/**
 * @file
 * @brief Prime factorization of positive integers
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include<utility>


/** Main program */
int main() {
    int num;
    std::cout << "\t\tComputes the prime factorization\n\n";
    std::cout << "Type in a number: ";
    std::cin >> num;

    int count  = 0 ;    // for storing the power of a prime in its prime factorization
    while( num % 2 == 0)
    {
	    count ++;
	    num /= 2;
    }
    std::cout << 2 << " " << count << "\n";
    for( int i = 3; i*i <= num ; i = i + 2)  // at this point, all the prime factors will be odd
    {
	    count = 0;
	    while( num % i == 0){
		    count ++;
		    num /= i;
	    }
	    if(count > 0)
	    {
		    std::cout << i << " " << count << "\n";    // output the prime and its power without storing them. No extra memory needed
	    }
    }
    if( num > 2){
	    std::cout << num << " " << 1 << "\n";  // check if number is a prime, if yes, output the number itself. This handles if the given number itself is a prime
    }
    return 0;
}
