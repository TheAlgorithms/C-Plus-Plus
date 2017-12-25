Prime Factorization is a very important and useful technique to factorize any number into its prime factors. It has various applications in the field of number theory.

The method of prime factorization involves two function calls.
First: Calculating all the prime number up till a certain range using the standard
       Sieve of Eratosthenes.

Second: Using the prime numbers to reduce the the given number and thus find all its prime factors.

The complexity of the solution involves approx. O(n logn) in calculating sieve of eratosthenes
O(log n) in calculating the prime factors of the number. So in total approx. O(n logn).

**Requirements: For compile you need the compiler flag for C++ 11**
