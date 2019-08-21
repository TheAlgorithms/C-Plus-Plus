//program to check whether a number is an armstrong number or not
#include <iostream.h>
#include <Math.h>
int main()
{
  int n, k, d, s = 0;
  cout << "Enter a number:";
  cin >> n;
  k = n;
  while (k != 0)
  {
    d = k % 10;
    s += (int)pow(d, 3);
    k /= 10;
  }
  if (s == n)
    cout << n << "is an armstrong number";
  else
    cout << n << "is not an armstrong number";
}
