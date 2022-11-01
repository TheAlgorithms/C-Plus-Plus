#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>>storeEdgeNum;
int edg;

struct disjointSets
{
	int *parent,*rank;
	int n;

	disjointSets(int n)
	{
		this->n=n;
		parent= new int[n+1];
		rank= new int[n+1];

		for(int i=0;i<=n;i++)
		{
			rank[i]=0;
			parent[i]=i;
		}
	}

	int find(int u)
	{
		if(u!=parent[u])
			parent[u]=find(parent[u]);
		return parent[u];
	}

	void merge(int x,int y)
	{
		x=find(x); 
		y=find(y);
		if(rank[x]>rank[y]) 
			parent[y]=x;
		else
			parent[x]=y; 
		if(rank[x]==rank[y]) 
			rank[y]+=1;
	}
};



struct Graph
{
	int v,e;
	vector<pair<int,pair<int,int>>>edges;
	Graph(int v, int e)
	{
		this->v=v;
		this->e=e;
	}

	void addedge(int u, int v, int w)
	{
		edges.push_back({w,{u,v}});
	}

	int mst()
	{
		int wt=0;
		sort(edges.begin(),edges.end());
		disjointSets ds(v);

		int q=0;
		for(auto it:edges)
		{
			int u=it.second.first;
			int v=it.second.second;

			int set_u=ds.find(u);
			int set_v=ds.find(v);

			if(set_u!=set_v)
			{
				cout<<u<<"--"<<v<<" : "<<it.first<<endl;
				storeEdgeNum.push_back({u,v});
				wt+=it.first;
				ds.merge(set_u,set_v);
			}
			q+=1;
		}
		return wt;
	}

	int secmst(int i,vector<pair<int,pair<int,int>>>&temp)
	{
		int wt=0;
		disjointSets dtemp(v);
		for(auto it:edges)
		{
			if(it.second!=storeEdgeNum[i])
			{
				int u=it.second.first;
				int v=it.second.second;
				int set_u=dtemp.find(u);
				int set_v=dtemp.find(v);
				if(set_u!=set_v)
				{
					wt+=it.first;
					dtemp.merge(set_u,set_v);
					edg+=1;
					temp.push_back(it);
				}
			}
			else continue;
		}
		return wt;
	}
};


int main()
{
	cout<<"Enter number of vertices: ";
	int v; cin>>v; cout<<endl;
	cout<<"Enter number of edges: ";
	int e; cin>>e;
	Graph g(v,e); cout<<endl;
	cout<<"Enter from, to vertice and weight of edge :"<<endl;
	for(int i=0;i<e;i++)
	{
		int fr,to,w;
		cin>>fr>>to>>w;
		g.addedge(fr,to,w);
	}
	cout<<endl;
	cout<<"Minimum spanning tree is: "<<endl;

	int wt=g.mst();
	cout<<"Weight of minimum spanning tree is: "<<wt;


	int sec_mst=INT_MAX;
	wt=0;
	vector<pair<int,pair<int,int>>>mst2;

	for(int i=0;i<storeEdgeNum.size();i++)
	{
		edg=0;
		vector<pair<int,pair<int,int>>>temp;
		wt=g.secmst(i,temp);
		if(edg!=v-1)
		{
			wt=0; 
			continue; 
		}
		if(sec_mst>wt)
		{
			sec_mst=wt;
			mst2=temp;
		}
		wt=0;
	}
	cout<<endl<<endl;
	cout<<"2nd best minimum spanning tree is: "<<endl;
	for(auto it:mst2)
	{
		cout<<it.second.first<<"--"<<it.second.second<<" : "<<it.first<<endl;
	}
	cout<<"Weight of minimum spanning tree is: "<<sec_mst;

	return 0;
}

