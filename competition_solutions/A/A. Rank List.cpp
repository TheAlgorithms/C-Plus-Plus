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
\
bool cmp(const pair<ll,ll>&p1,const pair<ll,ll>&p2)
{
    if(p1.first>p2.first)
        return 1;
    else if(p1.first==p2.first)
    {
        return p1.second<p2.second;
    }
    return 0;
}
int main()
{
    FastRead
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#endif

    int t,k,cnet=1;
    cin>>t>>k;
    vector<pair<ll,ll>>v(t);
    for(int i=0; i<t; i++)
    {
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(),v.end(),cmp);
    ll ans=0;
    for(int i=0; i<v.size(); i++)
    {
        if(v[i]==v[k-1])
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}
