#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long, int> PII;
#define F(i,n) for(int i=0;i<n;i++)
int main(){
	ll n,e;
	cin>>n>>e;
	vector< pair<ll, ll> > v[n+1];
	F(i,e){
		ll x,y,w;
		cin>>x>>y>>w;
		v[x].push_back({y,w});
	}
	priority_queue<PII, vector<PII>, greater<PII> > q;
	ll dis[n+1];
	F(i,n+1)dis[i]=INT_MAX;
	q.push({0,1});
	dis[1]=0;
	ll vis[n+1]={0};
	while(!q.empty()){
		pair<ll, ll > p = q.top();
		q.pop();
		if(vis[p.second]==1)continue;
		vis[p.second]=1;
		ll dis1=p.first, x = p.second;
		for(int i=0;i<v[x].size();i++){
			if(dis[v[x][i].first]> dis[x] + v[x][i].second){
				dis[v[x][i].first]=dis[x]+v[x][i].second;
				q.push({dis[v[x][i].first],v[x][i].first});
			}
		}
	}
	for(int i=2;i<n+1;i++)cout<<dis[i]<<" ";

}
