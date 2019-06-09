#include<iostream>
using namespace std;
#define PI 3.1415926535897932384626
#define ll long long int
#define mod 1000000007
#define fi first
#define se second

int main()
{
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
	ll T,a,b,c,d;
    cin>>T;
    while(T--) {
        cin>>a>>b;
        c=a+b-1;
        d=abs(a-b)+1;
        cout<<c<<" "<<d<<"\n";
    }
    return 0;
}

