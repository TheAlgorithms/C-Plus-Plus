#include <bits/stdc++.h>
using namespace std;
#define int long long
#define beastslayer ios_base::sync_with_stdio(false);cin.tie(NULL);
#define endl "\n"
//typedef pair<int, int> pii;

void prime_sieve(int *p)
{
    //First mark all odd number's prime
    for(int i=3;i<=100000; i+=2){
        p[i]=1;
    }
    //Sieve
    for(int i=3; i<=100000; i+=2){
        //if the current number is not marked (it is prime)
        if(p[i]==1){
            //mark all multiples of i as not prime
            for(int j=i*i; j<=100000; j=j+i){
                p[j]=0;
            }
        }
    }
    //special case of 1,0,2
    p[2] = 1;
    p[1] = p[0] = 0;
}

signed main()
{
    beastslayer;

    int n;
    cin>>n;

    int p[100005]={0};
    prime_sieve(p);

    //lets print primes upto range n
    for(int i=0;i<=n;++i)
    {
        if(p[i]==1)
        {
            cout<<i<<" ";
        }
    }


    return 0;
}
