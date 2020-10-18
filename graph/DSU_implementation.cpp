// D-S-U -> disjoint set and union.....implementation

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
using ii= pair<ll,ll>;
#define F first
#define S second
#define MP make_pair
#define PB push_back


ll parent[1001];       // parent[i] stores parent of node i
ll size[1001];         // stores size of a component

vector<ii> build;       
vector<ii> demo;      

void make_set(ll v)
{
    parent[v]=v;
    size[v]=1;
}

ll find_set(ll v)         // In find_set(v) we actually find the representative or root of the subtree having node v..
{                         // As an optimization we use...COMPRESSION BY PATH ...where after finding a certain v...we set
    if(parent[v]==v)      // v's parent directly to its representative so as to shorten the path for future find_set calls...
    {
        return v;
    }
    else
    {
        return parent[v]=find_set(parent[v]);    // be ware ...if you write parent[v]=find_set(parent[v])...you may get error/TLE
    }
}


void union_set(ll u,ll v)  // UNION OR MERGING 2 CONNECTED COMPONENTS TOGETHER...
{
    u= find_set(u);
    v= find_set(v);
    
    if(u!=v)
    {
        if(size[u]<size[v])     // UNION BY SIZE OPTIMIZATION-> attach the tree with lower size to the tree with bigger size...
        {                       // So that the size of tree may not grow much
            swap(u,v);
        }
        parent[v]=u;
        size[u]+=size[v];
    }
}




int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	
    ll n;
    cin>>n;
    ll m=n-1;
    
    for(ll i=1;i<=n;i++)
    {
        make_set(i);
    }
    
    while(m--)
    {
        ll a,b;
        cin>>a>>b;
        
        if(find_set(a)==find_set(b))
        {
            demo.PB({a,b});
        }
        else
        {
            union_set(a,b);
        }
    }
    
	for(ll i=2;i<=n;i++)
	{
	    if(find_set(i)!=find_set(1))
	    {
	        build.PB({i,1});
	        union_set(i,1);
	    }
	}
	
	ll x=build.size();
	cout<<build.size()<<"\n";
	
	for(ll i=0;i<x;i++)
	{
	    cout<<demo[i].F<<" "<<demo[i].S<<" "<<build[i].F<<" "<<build[i].S<<"\n";
	}
	
	
}
