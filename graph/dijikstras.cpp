#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define w(t)            int t; cin>>t; while(t--)
#define mod 1000000007
#define ld long double
#define F first
#define S second
#define P pair<int,int>
#define pb push_back

void dijkstras_algo(map<int,list<pair<int,int>>>g,int n,int src){

    set<pair<int,pair<int,string>>>s;

    string str = "";

    s.insert({0,{src,str+to_string(src)}});

    map<int,bool>vis;

    while(s.size() != 0){

        auto it = s.begin();
        pair<int,pair<int,string>> p = *it;

        int wsf = p.first;
        int node = p.second.first;
        string psf = p.second.second;

        
        s.erase(it);

        if(vis[node]){
            continue;
        }

        vis[node] = true;

        cout<<node<<" via "<<psf<<" @ "<<wsf<<endl;

        for(auto i:g[node]){
            int nbr = i.first;
            int dis = i.second;
            if(!vis[nbr]){
                s.insert({wsf+dis,{nbr,psf+to_string(nbr)}});
            }
        }

    }
}

int32_t main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif

    int n;
    cin>>n;
    int e;
    cin>>e;

    map<int,list<pair<int,int>>>g;

    for(int i=0;i<e;i++){
        int a,b,d;
        cin>>a>>b>>d;
        g[a].pb(make_pair(b,d));
        g[b].pb(make_pair(a,d));
    }
    int src;
    cin>>src;

    dijkstras_algo(g,n,src);



    return 0;
}