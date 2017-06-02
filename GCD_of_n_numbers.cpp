#include <iostream>
using namepsace std;
int main()
{
  cout <<"Enter value of n:"<<endl;
  cin >> n;
  int a[n];
  int i,j,gcd;
  for(i=0;i<n;i++)
    cin >> a[i];
  j=1;
  gcd=a[0];
  while(j<n)
  {
    if(a[j]%gcd==0)
     j++;
    else
     gcd=a[j]%gcd;
  }
  cout << "GCD of entered n numbers:" << gcd;
}
