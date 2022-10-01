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
	
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vector<int>vc;
		ll arr[n],pos=0,sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>arr[i];
			if(arr[i]%2==0)
			{
				pos=i;
			}
			else
			{
				vc.pb(i);
			}
		}
		if(pos!=0)
		{
			cout<<"1"<<pos<<endl;
		}
		else if(vc.size()>1)
		{
			cout<<"2"<<endl<<vc[0]<<" "<<vc[1]<<endl;
		}
		else
		{
			cout<<"-1"<<endl;
		}
		
		
	}

	return 0;
}
