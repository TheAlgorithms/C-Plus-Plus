#include<iostream> 
#include<algorithm> 
using namespace std; 
  
int digitGCD(int n) 
{ 
    int gcd = 0; 
    while (n > 0) 
    {         
        gcd = __gcd(n%10, gcd); 
  
        // If at point GCD becomes 1, 
        // return it 
        if (gcd == 1) 
           return 1; 
  
        n = n/10; 
    } 
    return gcd; 
} 
  
// driver code 
int main() 
{ 
    long n = 2448; 
    cout << digitGCD(n); 
    return 0; 
} 
