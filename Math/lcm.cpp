#include<iostream>
using namespace std;
int gcd(int a, int b)
{
    // Everything divides 0
    if (a == 0)
       return b;
    if (b == 0)
       return a;

    // base case
    if (a == b)
        return a;

    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}
int main()
{
    int a,b;
    int gcd1;
    cout<<"Enter A and B for finding lcm\n";
    cin>>a>>b;
    gcd1 = gcd(a,b);
    int lcm = (a*b)/gcd1;
    cout<<lcm;

}
