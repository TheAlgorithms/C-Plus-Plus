/**
 * @file
 * @brief Prime factorization of positive integers
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include<utility>

/** Declaring variables for maintaing prime numbers and to check whether a
 * number is prime or not
 */
bool isprime[1000006];

/** list of prime numbers */
std::vector<int> prime_numbers;

/** list of prime factor-pairs */
std::vector<std::pair<int, int> > factors;

/** Prime factorization of a number */
void prime_factorization(int num) {
    int number = num;
    int count = 0;
    while (number % 2 == 0) {   // finding power of 2 in prime factorization
        count ++ ;
        number = number / 2;
    }
    factors.push_back ( std::make_pair ( 2, count) ) ;
    for ( int i = 3 ; i * i <= number ; i = i + 2)   // at this point, only odd primes will be the factors                             
    {
        count = 0;
        while ( number % i == 0 ) 
        {
            count ++ ;
            number = number / i ;
        }
        if ( count > 0 )
            factors.push_back ( std::make_pair ( i , count ) ) ;
    }
    if ( number > 2)
    	factors.push_back ( std::make_pair ( number , 1 ) );
}

/** Main program */
int main() {
    int num;
    std::cout << "\t\tComputes the prime factorization\n\n";
    std::cout << "Type in a number: ";
    std::cin >> num;

    prime_factorization(num);

    // Prime factors with their powers in the given number in new line
    int size = factors.size();
	for(int i=0; i< size; i++){
		std::cout<<factors[i].first<<" "<<factors[i].second<<"\n";
	}
    return 0;
}
