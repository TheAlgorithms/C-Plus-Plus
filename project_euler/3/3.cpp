// I know this is a really long program but this will be really usefull for later problems :P
#include<iostream>
#include<cmath>

using namespace::std;

bool isprime(int n)
{   
    bool flag=false;
    for(int i=2;i<=sqrt(n);++i)
    {   if(n%i==0)
        {   flag = true;
            break;
        }
        else if(flag==true)
            break;
    }
    return flag;
}

long nthprime(int n)
{
    int counter=1; // including 2
    long i=3; // starting from 3 to optimise the program    
    while(counter<n)
    {
        if(isprime(i))
        {
            counter++;
        }
        i+=2;
    }
    return i;
}

void hPrimeFactor(long long n)
{
    long nnum = n;
    long hFact = 0;
    // the mathematics is not that complicated
    int counter = 2;
    while (counter<=sqrt(nnum)) {
        if (nnum % counter == 0) {
            nnum = nnum / counter;
            hFact = counter;
        } else {
            counter = (counter == 2) ? 3 : counter + 2;
        }
    }
    if (nnum > hFact) { // the remainder is a prime number
        hFact = nnum;
    }
    cout<<hFact<<endl;
}        


int main()
{   
    hPrimeFactor(600851475143);
    return 0;
}

