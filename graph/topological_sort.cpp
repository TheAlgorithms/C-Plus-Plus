#include<bits/stdc++.h>
using namespace std;
int v,E;
vector <vector <int> > g;
int stacky[10000];
int vis[1000];
int sp=0;
int ans1[100000];
int po=0;
int cur;
int push(int val)
{
	stacky[sp]=val;
	sp++;
}
int pop()
{
	sp--;
}
int dfs()
{
	int p =cur;
	for(int j=0 ; j< g[cur].size() ; j++)
	{
		int k = g[cur][j];
		if(vis[k]==0)
		{
			push(cur);
			cur=k;
			vis[k]=1;
			dfs();
		
		 }
	}

	if(cur==p)
	{	
		if(sp==0)
		{
			return 0;

		}
		else
		{
			ans1[po]=cur;
			po++;
			vis[cur]=2;
			int t = stacky[sp-1];
			pop();
	        cur=t;
	        dfs();
		}
	} 
}
int main ()
{
	cin >> v >> E;
	g.resize(v+1);
	for(int i=0 ; i<E;i++)
	{
		int v1,v2;
		cin >> v1 >> v2;
		if(i==0)
		{
			cur=v1;
		}
		g[v1].push_back(v2);
	}
	
	for(int i=1;i<=v ; i++)
	{
		vis[i]=0;
	}
	
	for(int i=1;i<=v;i++)
	{
		if(vis[i] == 0)
		{
			cur=i;
			vis[i]=1;
			
			dfs();
		
			ans1[po]=i;
			po++;
			vis[cur]=2;
		}
	}
	for(int i= po-1;i>=0 ;i--)
	{
		cout << ans1[i] << " ";
	}
}
