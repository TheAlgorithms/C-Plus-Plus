// C++ program to find LCM(Least Common Multiple) of two numbers 
/*
	suppose we have two numbers a and b.
	Property: Since product of LCM and GCD of two numbers are equal to product of that number itself.
	i.e, LCM(a,b)*GCD(a,b)=a*b.
	So,here we first find the GCD of two numbers and using above property we find LCM of that two numbers.
*/
#include <iostream>  
using namespace std; 

// Recursive function to return gcd of a and b  
int gcd(int a, int b)
{ 
    if (a == 0) 
        return b;  
    return gcd(b % a, a);  
 } 
  
// Function to return LCM of two numbers  
int lcm(int a, int b)  
{  
    return (a*b)/gcd(a, b);  
}  

// Driver program 
int main()  
{  
    int a,b; 
    cout<<"Enter two numbers to find their LCM"<<"\n";
    cin>>a>>b; 
    cout<<"LCM of "<<a<<" and "<<b<<" is "<<lcm(a, b)<<"\n"; 
    return 0;  
}  
/*
Test Case1:
a=15,b=20
LCM(a,b)=60
Test Case2:
a=12,b=18
LCM(a,b)=36
*/
