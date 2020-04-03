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
 
int nthprime(int n)
{
    int counter=0; // including 2
    long i=2;     
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

int po(int n, int prime)
{
    int count=0;    
    while(n%prime == 0)
    {
        count++;
        n = n/prime;
    }
    return count;
}

int arr[10];

void setprime(int ar[], int num)
{
    for(int i=0;i<num;i++)
    {
        arr[i]= nthprime(i);
    }
}

int ipow(int base, int exp)
{
    int result = 1;
    while (exp != 0)
    {
        if ((exp & 1) == 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

void master(int below)
{
    long long ans=1;
    int i, j=2, nop=8;    
    int power[10]={0,0,0,0,0,0,0,0,0,0}, c=0;
    setprime(arr,10);
    for(i=0;i<10;i++)
    {
        for(j=2;j<=20;++j)
        {
            if(po(j,arr[i])>power[i])            
                power[i]=po(j,arr[i]);
        }
    }
    for(i=0;i<nop;++i) //nop is number of primes below that 20 in this case in future programs we will see how to create the function to count the number of prime
    {
        ans *= ipow(arr[i],power[i]);
    }
    cout<<ans<<endl;
}

int main()
{
    master(20);
    return 0;
}
