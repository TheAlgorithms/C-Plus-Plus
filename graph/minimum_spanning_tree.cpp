#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define FIO ios::sync_with_stdio(0);
int main() 
{
	FIO;
	ll i,c=0,n,m,x,y,z;
	cin>>n>>m;
	vector<pair<ll,ll>> a[100001];
	vector<ll> vis(100001,0);
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> q;
	pair<ll,ll> p;
	for(i=0;i<m;i++)
	{
		cin>>x>>y>>z;
		a[x].pb(mp(z,y));
		a[y].pb(mp(z,x));
	}
	q.push(mp(0,1));
	while(!q.empty())
	{
		p=q.top();
		q.pop();
		x=p.ss;
		if(vis[x]==1)
			continue;
		vis[x]=1;
		c+=p.ff;
		for(i=0;i<a[x].size();i++)
		{
			if(vis[a[x][i].ss]==0)
				q.push(a[x][i]);
		}
	}
	cout<<c;
	return 0;
}
