#include<bits/stdc++.h>
#define ll long long
#define mx 1000000
using namespace std;

char prime[mx];
ll arr[mx],k=0;
ll bb[mx],p=0;

void sieve ()
{
    ll i,j;
    prime[0]=prime[1]=1;
    for(i=4;i<=mx;i+=2)prime[i]=1;
    for(i=3;i<=sqrt(mx);i+=2)
    {
        if(prime[i]==0)
        {
            for(j=i*i;j<=mx;j+=i*2)
            {
                prime[j]=1;
            }
        }
    }
    for(i=2;i<=mx;i++)
    {
        if(prime[i]==0)
        {
            arr[k++]=i;
        }

    }

}

bool check(int n)
{
    int i,cnet=0;
    for(i=0;arr[i]<=n;i++)
    {
        if(n%arr[i]==0)
        {
            cnet++;
        }
    }
    if(cnet==2)return  true;
    else return false;
}

int main()
{
    sieve();
    ll n,i,cnet=0,j;
    cin>>n;
    for(i=0;i<=n;i++)
    {
        if(check(i))
        {
            cnet++;
        }

    }
    cout<<cnet<<endl;
    return 0;
}

