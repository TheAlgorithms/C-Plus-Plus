#include <iostream>
using namespace std;
// Recursive function to return gcd of a and b
class gcd
{
 public : int gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
 }


// Function to return LCM of two numbers
  int lcm(int a, int b)
 {
    return (a*b)/gcd(a, b);
 }
} ;
// Main program to test above function
int main()
{
    gcd g;
    cout<<"Enter the numbers for which you want to find LCM : \n";
    int a,b;
    cin>>a>>b;
    cout<<"\nLCM of "<<a<<" and "<<b<<" is "<<g.lcm(a, b);
    return 0;
}
