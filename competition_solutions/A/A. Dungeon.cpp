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
    #ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
	
	int t;
	cin>>t;
	while(t--)
	{
		ll a,b,c,n=0,flag=0;
		cin>>a>>b>>c;
		if(a==1 || b==1 || c==1)
		{
			cout<<"NO\n";
			continue;
		}
		else
		{
			while(a!=1 && b!=1 && c!=1)
			{
				if(a>1)a--,n++;
				if(b>1)b--,n++;
				if(c>1)c--,n++;
				if(n==7 && (a==1 && b==1 && c==1))
				{
					flag=1;
					break;
				}
				else if(n==7 && (a!=1 || b!=1 || c!=1))
				{
					n=0;
					a--,b--,c--;
				}
			}
			if(flag==1)cout<<"YES\n";
			else cout<<"NO\n";

		}

	}

	return 0;
}
