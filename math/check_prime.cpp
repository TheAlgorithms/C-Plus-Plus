/**
 *
 *
 * @file
 * A simple program to check if the given number if prime or not.
 *
 * @brief
 * Reduced all possibilities of a number which cannot be prime.
 * Eg: No even number, except 2 can be a prime number, hence we will increment
 * our loop with i+2 jumping on all odd numbers only. If number is <= 1 or if it
 * is even except 2, break the loop and return false telling number is not
 * prime.
 */
#include <cassert>
#include <iostream>
/**
 * Function to check if the given number is prime or not.
 * @param num number to be checked.
 * @return if number is prime, it returns @ true, else it returns @ false.
 */
bool is_prime(int n) {
    // Assumes that n is a positive natural number
    // We know 1 is not a prime number
    if (n == 1) {
        return false;
    }

    int i = 2;
    // This will loop from 2 to int(sqrt(x))
    while (i*i <= n) {
        // Check if i divides x without leaving a remainder
        if (n % i == 0) {
            // This means that n has a factor in between 2 and sqrt(n)
            // So it is not a prime number
            return false;
        }
        i += 1;
    }
    // If we did not find any factor in the above loop,
    // then n is a prime number
    return true;
}

int main() {
  int x;
    cout<<"Enter the number"<<endl;
    cin>>x;
    cout << x << ": " <<  (is_prime(x) ? "true" : "false") << endl;
    // Output: 1000000000: false
   
    return 0;
}
