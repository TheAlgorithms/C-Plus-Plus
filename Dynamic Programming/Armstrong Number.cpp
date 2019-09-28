//program to check whether a number is an armstrong number or not
#include <iostream>
#include <cmath>
int main()
{
  int n, k, d, s = 0;
  std::cout << "Enter a number:";
  std::cin >> n;
  k = n;
  while (k != 0)
  {
    d = k % 10;
    s += (int)pow(d, 3);
    k /= 10;
  }
  if (s == n)
    std::cout << n << "is an armstrong number";
  else
    std::cout << n << "is not an armstrong number";
}
