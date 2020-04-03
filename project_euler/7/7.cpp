#include<iostream>
#include<math.h>

using namespace std;

bool isprime(int n)
{   
    
    for(int i=2;i<=sqrt(n);++i)
    {   if(n%i==0)
        {   return false;
        }
    }
    return true;
}

// nthprime function from problem 3
 
long long nthprime(int n)
{
    int counter=0; // including 2
    long long i=2;     
    while(counter<n)
    {
        i = (i == 2) ? 3 : i+2;
        if(isprime(i))
        {
            counter++;
        }
    }
    return i;
}


int main()
{
    long long prime= nthprime(10001);
    cout<<prime<<endl;
    return 0;
}
