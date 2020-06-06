/** Classical Sieve of Eratosthenes is an algorithm to find the primes
 * that is between 2 to N (as defined in main) in fastest way.
 * Time Complexity  : O(N * log(log(N)))
 * Space Complexity : O(N)
 */

#include <iostream>

/** This is the function that finds the primes and eliminates
 * the multiples.
 */
void sieve(int N, bool *isprime ) {
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

/** This function prints out the primes to STDOUT
 */
void print(int N, bool *isprime ) {
  for (int i = 1; i <= N; i++) {
    if (!isprime[i]) {
      std::cout << i << ' ';
    }
  }
  std::cout << '\n';
}

int main() {
  int N = 100;
  bool *isprime = new bool[N];
  sieve(N, isprime);
  print(N, isprime);
  delete[] isprime;
}
