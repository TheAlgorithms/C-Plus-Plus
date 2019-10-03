#include <bits/stdc++.h>

/*
code credits : ਜ਼ੈਲਦਾਰ
dashan jot singh
*/
using namespace std;
#define ll long long int
#define fast ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL)
#define pb push_back
#define mp make_pair
#define inf LLONG_MAX
#define p pair<ll,ll>
//find
//union 
//createset

int parent[100010];
int rank_set[100010];
vector<int> graph[100010];
int v,e;
int findSet(int r){
	if(parent[r]==-1){
		return r;
	}
	return findSet(parent[r]);
}
void Union(int x,int y){
	int ax=findSet(x);
	int by=findSet(y);
	if(ax==by){
		return;
	}
	if(rank_set[ax]<rank_set[by]){
		parent[ax]=by;
	}
	else if(rank_set[ax]>rank_set[by]){
		parent[by]=ax;
	}
	else{
		parent[ax]=by;
		rank_set[by]++;
	}
}
void  createset(int x){
	parent[x]=-1;
	rank_set[x]=0;
}
bool findCycle(){
	memset(parent,-1,sizeof(parent));
	memset(rank_set,0,sizeof(rank_set));
	for(int i=0;i<v;i++){
		for(auto y:graph[i]){
			int xx=findSet(i);
			int yy=findSet(y);
			if(xx==yy){
				return true;
			}
			Union(xx,yy);
		}
	}
	return false;
}
int main(){
	fast;
	// int v,e;
	cin>>v>>e;
	// for(int i=0;i<v;i++){
	// 	createset(i);
	// }
	for(int i=0;i<e;i++){
		int x,y;
		cin>>x>>y;
		// Union(x,y);
		graph[x].pb(y);
		// graph[y].pb(x);
	}
	for(int i=0;i<v;i++){
		cout<<i<<"-> ";
		for(auto y:graph[i]){
			cout<<", "<<y<<" ";
		}
		cout<<endl;
	}
	if(findCycle()){
		cout<<"Cycle present\n";
	}
	else{
		cout<<"NO CYCLE\n";
	}
	// int q;
	// cin>>q;
	// for(int i=0;i<q;i++){
	// 	int x,y;
	// 	cin>>x>>y;
	// 	int ans=findSet(x);
	// 	int ans2=findSet(y);
	// 	cout<<"Set is "<<ans<<" " <<ans2<<endl;
	// }
	return 0;
}
