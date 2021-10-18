#include<bits/stdc++.h>
using namespace std;
#define ff              first
#define ss              second
#define lli             long long int
#define ll              long long
#define pb              push_back
#define pob             pop_back
#define pii             pair<int,int>
#define vpii            vector<pair<int,int>>
#define vi              vector<int>
#define vll             vector <ll>
#define mii             map<int,int>
#define mod             1000000007
#define inf1            1e9
#define inf2            1e18
#define N               200005
#define input           int n;cin>>n; int a[n]; loop(i,0,n){ cin>>a[i]; }
#define loop(i,a,b)     for (int i=a;i<b;i++)
#define rloop(i,a,b)    for (int i=a;i>b;i--)
#define PI              3.14159265358979323846
#define np              next_permutation
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(tc)           int tc; cin>>tc; while(tc--)
#define sort(a)         sort(a.begin(),a.end())
#define endl            "\n"

/* int dx[] = {1,-1,0,0} , dy[] = {0,0,1,-1}; */
/* int dx[] = {1,-1,0,0,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1,1,-1}; */
/* int dx[] = {1,-1,1,-1,2,2,-2,-2} , dy[] = {2,2,-2,-2,1,-1,1,-1}; */
/* int dx[] = {2,-2,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1}; */
void bhagg_() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
// ******************************************************************************
vi adj[N] ; int col[N] , vis[N];
bool bipartite (int x , int y) {
	vis[x] = 1;          // visibility
	col[x] = y;          // colour of the particular
	for (auto it : adj[x]) {
		if (vis[it] == 0) {
			if (bipartite(it , y ^ 1) == false )
				return false;                          // checking if the prev vertex has same color or not
		}
		else {
			if (col[x] == col[it])  return false ;     // checking if the child has same color thn FALSE
		}
	}

	return true ;
}

int32_t main() {
	bhagg_();
	int n , m ; cin >> n >> m ;
	while (m--) {
		int x , y; cin >> x >> y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	bool res = bipartite(1, 0);

	cout << (res == 1 ? "true" : "false") << endl;
	return 0;
}
