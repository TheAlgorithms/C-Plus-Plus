#include<bits/stdc++.h>
using namespace std;
#define LL long long
typedef int I;
LL gcd(LL a , LL b)
{
    if(b==0)
       return a;
    else
    {
        return(gcd(b,a%b));
    }
       
}
I main()
{
   LL a,b;
   cin>>a>>b;
   LL k;
   if(a>b)
      k=gcd(a,b);

    else
      k=gcd(b,a);
     
   I lcm;
   lcm =(a*b)/k;
   cout<<"Lcm of "<<a<<" and "<<b<<" is : "<< lcm<<endl;
}