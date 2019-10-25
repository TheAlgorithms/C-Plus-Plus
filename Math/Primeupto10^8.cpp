#include<iostream>
#include <cstring>
using namespace std;
#define ll long long
char prime[100000000];
void Sieve(ll n) 
{ 
   
 
    memset(prime, '1', sizeof(prime)); //intitize '1' to every index
    prime[0] = '0';  // 0 is not prime
    prime[1] = '0';  // 1 is not prime
    for (int p=2; p*p<=n; p++) 
    { 
        
        if (prime[p] == '1') 
        { 
            
            for (int i=p*p; i<=n; i += p)  // all multiple of p set to false
                prime[i] = '0'; 
        } 
    } 
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
int main()
{
   
    Sieve(100000000);
    ll n;
    cin>>n;   // 10006187 
    
    if(prime[n] == '1')
    cout<<"YES\n";
    else
    cout<<"NO\n";
}
