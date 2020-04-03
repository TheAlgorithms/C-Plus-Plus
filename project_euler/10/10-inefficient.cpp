#include<iostream>
#include<math.h>
#include<stdint.h>

using namespace std;

bool isprime(int n)
{   
    bool flag=true;
    for(int i=2;i<=sqrt(n);++i)
    {   if(n%i==0)
        {   flag = false;
            break;
        }
    }
    return flag;
}

void sumprime(int64_t n)
{
    int64_t sum=2; // including 2
    int64_t i=3; // starting from 3 to optimise the program    
    while(i<n)
    {
        if(isprime(i))
        {
            sum+=i;
        }
        i+=2;
    }
    cout<<sum;
}

int main()
{
    sumprime(2000000);
    return 0;
}
