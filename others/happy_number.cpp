/* A happy number is a number whose sum of digits is calculated until the sum is a single digit,
  and this sum turns out to be 1 */

// Copyright 2019 TheAlgorithms contributors

#include <iostream>

int main() {
  int n, k, s = 0, d;
  std::cout << "Enter a number:";
  std::cin >> n;
  s = 0;
  k = n;
  while (k > 9) {
    while (k != 0) {
      d = k % 10;
      s += d;
      k /= 10;
    }
    k = s;
    s = 0;
  }
  if (k == 1)
    std::cout << n << " is a happy number" << std::endl;
  else
    std::cout << n << " is not a happy number" << std::endl;
  return 0;
}
