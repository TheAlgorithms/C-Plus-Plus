#include <iostream> 
using namespace std;
 
// Recursive function to return gcd of a and b 
long long gcd(long long int a, long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers 
long long lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}
  
// Driver program to test above function 
int main() 
{ 
    int a = 15, b = 20; 
    cout <<"LCM of " << a << " and "
         << b << " is " << lcm(a, b); 
    return 0; 
} 
