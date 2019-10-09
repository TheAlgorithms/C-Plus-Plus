#include<bits/stdc++.h>
#define INF 1000000000
#define MAXN 10000
#define ll long long int
using namespace std;

map<ll ,ll> t;
 



void build( ll a[],ll  v, ll  tl, ll  tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        ll tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = __gcd(t[v*2], t[v*2+1]);
    }
}

ll  get_gcd(ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    ll tm = (tl + tr) / 2;
    return __gcd(get_gcd(v*2, tl, tm, l, min(r, tm)), 
                   get_gcd(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(ll v, ll tl, ll tr, ll pos, ll new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}



int main(){
	long int t;
	cin>>t;
	while(t--){
//		map<int, int>mp;
//		ll n,q,num,y,s;
//		cin>>n>>q;
//		while(q--){
//			cin>>num;
//			
//			if(num==1){
//				cin>>y;
//				y = s+y;
//				update(1,0,n-1,y,0);
//			}
//			
			
			ll a[7]={2,15,9,7,95,2,56};
			build(a,1,0,6);
				cout<<get_gcd(1,0,6,1,2)<<endl;
		}
	}
	

	
	
	
	//cout<<sum(1,0,6,1,3);

