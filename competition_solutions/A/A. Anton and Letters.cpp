
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
    double dp[105][105];
    int n,e,i,j,k;
    while(cin>>n && n!=0)
    {
        cin>>e;
        memset(dp,0,sizeof(dp));
        while(e--)
        {
            ll v,u;
            double c;
            cin>>v>>u>>c;
            dp[v][u]=dp[u][v]=c/100.0;
        }
        for(k=1;k<=n;k++)
        {
            for(i=1;i<=n;i++)
            {
                for(j=1;j<=n;j++)
                {
                    dp[i][j]=max(dp[i][j],dp[i][k]*dp[k][j]);
                }
            }
        }
        cout<<setprecision(6)<<fixed<<dp[1][n]*100<<" percent\n";
    }


    return 0;
}
