#include<bits/stdc++.h>
using namespace std;
          //Welcome To Hridoy's Code
#define   ll                  long long
#define   ull                 unsigned long long
#define   pb                  push_back
#define   em                  emplace_back
#define   ff                  first
#define   ss                  second
#define   endl                "\n"
#define   all(v)              (v.begin(), v.end())
#define   rall(v)             (v.rbegin(), v.rend())
#define   pi                  acos(-1.0)
#define   LCM(LCM_X,LCM_Y)    (LCM_X/__gcd(LCM_X,LCM_Y))*LCM_Y
#define   FastRead   ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
const int MOD = (int)1e9+7;
const int MAX = 1e6;
int main()
{
    FastRead
    ll a=0,b=0,sum=0,n;
    cin>>n;
    ll arr[n];
    for(ll i=0; i<n; i++)
    {
        cin>>arr[i];
        if(arr[i]==100)
            a++;
        else
            b++;
    }
    if(a==0)
    {
        if(b%2==0)
            cout<<"YES\n";
        else
            cout<<"NO\n";
        return 0;
    }
    if(b==0)
    {
        if(a%2==0)
            cout<<"YES\n";
        else
            cout<<"NO\n";
        return 0;
    }
    else
    {
        if(a%2==0 && b%2==0)
            cout<<"YES\n";
        if(a%2==0 && b%2==1)
            cout<<"YES\n";
        if(a%2==1 && b%2==0)
            cout<<"NO\n";
        if(a%2==1 && b%2==1)
            cout<<"NO\n";
    }

    return 0;
}
