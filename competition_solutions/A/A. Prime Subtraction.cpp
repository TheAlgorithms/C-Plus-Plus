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
long long dp(long long p)
    {
        long long temp;
        if ( p == 1 ) return 2;
        if ( p % 2 == 0 )
        {
            temp = dp(p/2);
            return (temp * temp) % MOD;
        }
        else
        return (dp(p - 1)*2);
    }
int main ()

{
    int t,i;
    cin>>t;
    for(i=1;i<=t;i++) {
        int n;
        cin>>n;
        cout<<"Case #"<<i<<": ";
        if(n==1)
        cout<<"1"<<endl;
        else
        cout << (((dp(n - 1)%MOD) * (n % MOD)) % MOD) << endl;
    }
return 0;
}