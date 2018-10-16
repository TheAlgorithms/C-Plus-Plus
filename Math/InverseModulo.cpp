#include <iostream>
using namespace std;
//Given two integers ‘a’ and ‘m’, find modular multiplicative inverse of ‘a’ under modulo ‘m’

// Function for calculating Inverse modulo and power %mod in O(log(n)) Time Complexity
long long InverseModulo(long long  base,long long p,long long mod)
{
    if(p ==0)
        return 1;
    else if(p&1)
        return (base*InverseModulo(base,p-1,mod))%mod;
    else
    {
        ll k =  InverseModulo(base,p/2,mod);
        return (k*k)%mod;
    }
}

/*
    I added a simple UI.
*/

int main()
{
    //Declarations
    long long num,mod;
    cout << "\t\tComputes the Inverse Modulo\n\n";
	
    // Value of base
    cout << "Input the base: ";
    cin>>num;
	
    // Input for mod
    cout << "Input the value of modulo: ";
    cin>>mod;
	
    //Output
    cout<<"Inverse modulo of num under modulo mod is: "<<InverseModulo(num,mod-2,mod);
    return 0;
}
