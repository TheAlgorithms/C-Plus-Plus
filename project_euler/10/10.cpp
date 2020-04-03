#include<iostream>
#include<math.h>
#include<stdint.h>

using namespace std;

void primeLim(size_t lim)
{
    int64_t sum=0;
    int i,j;
    bool* primes = NULL;
    primes  = new bool[lim];
    for(i = 0;i<lim;++i)
    {
        primes[i] = true;
    }
    for(i=2;i<sqrt(lim);++i)
    {
        if(primes[i] == true)
        {
            for(j=i*i;j<lim;j+=i)
            {
                primes[j]=false;
            }
        }
    }
    for(i=0;i<lim;i++)
    {
        if(primes[i] == true)
        {
            sum+=i;
        }
    }
    delete [] primes;
    cout<<sum;
}

int main()
{
    primeLim(2000000);
    return 0;
}
    
