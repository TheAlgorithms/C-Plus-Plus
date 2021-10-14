#include<bits/stdc++.h>
using namespace std;
#define siz 200000
long long int bit[siz+1];
pair<int,int> a[siz+1];
void upd(int i,int n)
{
    while(i<=n)
    {
        bit[i]+=1;
        i+=i&(-i);
    }
}
long long int que(int i)
{
    long long int ans=0;
    while(i>0)
        ans+=bit[i],i-=i&(-i);
    return ans;
}
int main()
{
    int t,n,r,maxi;
    long long int cnt;
    scanf("%d",&t);
    while(t--)
    {
        cnt=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i].first);
            a[i].second=i;
        }
        sort(a+1,a+n+1,greater<pair<int,int> >());
	    long long int ans=0;
	    for(int i=1;i<=n;i++)
	        cnt+=que(a[i].second),upd(a[i].second,n);
        printf("%lld\n",cnt);
        for(int i=1;i<=n;i++)
            bit[i]=0;
    }
