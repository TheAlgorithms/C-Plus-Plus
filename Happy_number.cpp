/* A happy number is a number whose sum of digits is calculated until the sum is a single digit,
  and this sum turns out to be 1 */
#include <iostream>
using namespace std;

int main()
{
  int n,k,s=0,d;
  cout << "Enter a number:";
  cin >> n;
  s=0;k=n;
  while(k>9)
  {
    while(k!=0)
    {
      d=k%10;
      s+=d;
      k/=10;
    }
    k=s;
    s=0;
  }
  if(k==1)
   cout << n << " is a happy number" << endl;
  else
   cout << n << " is not a happy number" << endl;
  return 0;
}
