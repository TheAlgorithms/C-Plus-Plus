#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n;
  cin>>n;
  int a[n];
  for(int i=0;i<n;i++)
    cin>>a[i];
  int ans=a[0];
  for(int i=1;i<n;i++)
  ans=__gcd(a[i],ans);
  cout << "GCD of entered n numbers:" << ans;
}
