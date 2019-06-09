#include<iostream>
using namespace std;
#define PI 3.1415926535897932384626
#define ll long long int
#define N 10000007
#define m 1000000007
ll s[N];

int main()
{
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
	ll i,T,a;
    cin>>T;
    s[0]=s[1]=s[2]=1;
    for(i=3;i<N;i+=2) {
        s[i]=(s[i-1]*i)%m;
        s[i+1]=s[i];
    }
    while(T--) {
        cin>>a;
        cout<<s[a]<<"\n";
    }
    return 0;
}
   
