#include <iostream>
#include <cassert>

/* Double factorial of a non-negative integer n,
is defined as the product of all the integers from 1 to n
that have the same parity (odd or even) as n.
It is also called as semifactorial of a number and is denoted by !! */

unsigned long long double_factorial_iterative(unsigned int n){
  unsigned long long res = 1;
  for(unsigned long long i = n; i >= 0; i -= 2){
    if(i == 0 || i == 1) return res;
    res *= i;
  }
}

/* Recursion can be costly for large numbers */

unsigned long long double_factorial_recursive(unsigned int n){
  if(n <= 1) return 1;
  return n * double_factorial_recursive(n - 2);
}

int main()
{
  int n{};
  std::cin >> n;
  assert(n >= 0);
  std::cout << double_factorial_iterative(n);
}
