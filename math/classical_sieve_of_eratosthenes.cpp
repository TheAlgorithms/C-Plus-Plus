/**
 * Classical Sieve of Eratosthenes is an algorithm to find the primes
 * that is between 2 to N (as defined in main) in fastest way.
 *
 * Time Complexity  : O(N * log(log(N)))
 * Space Complexity : O(N)
**/

#include <iostream>

bool* isprime = new bool[100000];

/**
 * This is the function that finds the primes and eliminates
 * the multiples.
**/
void sieve(int N) {
  isprime[0] = true;
  isprime[1] = true;
  for (int i = 2; i * i <= N; ++i) {
    if (!isprime[i]) {
      for (int j = i * i; j <= N; j = j + i) {
        isprime[j] = true;
      }
    }
  }
}

/**
 * This function prints out the primes to STDOUT
**/
void print(int N) {
  for (int i = 1; i <= N; i++) {
    if (!isprime[i]) {
      std::cout << i << ' ';
    }
  }
  std::cout << '\n';
}

int main() {
  int N = 100;
  sieve(N);
  print(N);
  delete[] isprime;
}
