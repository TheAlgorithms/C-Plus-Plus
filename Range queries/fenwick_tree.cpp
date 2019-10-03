#include <bits/stdc++.h>

using namespace std;
#define ll long long int
#define re1(x) scanf("%lld",&x)
#define re2(x,y) scanf("%lld%lld",&x,&y)
#define re3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define pr(x) printf("%lld\n",x);
#define pb push_back
#define mp make_pair

ll arr[100010];
ll BIT[100100];
ll n,q;
void update(ll index,ll val){
	index=index+1;
	while(index<=n){
		BIT[index]+=val;
		index+=(index&(-index));
		//get the next 
	}
}
ll query(ll index){
	ll sum=0;
	index+=1;
	while(index>0){
		sum+=BIT[index];
		index-=(index&(-index));
	}
	return sum;
}
int main(){
	re1(n);
	for(ll i=0;i<n;i++){
		re1(arr[i]);
	}
	memset(BIT,0,sizeof(BIT));
	for(ll i=0;i<n;i++){
		update(i,arr[i]);
	}
	re1(q);
	for(ll i=0;i<q;i+=1){
		char type;
		cin>>type;
		if(type=='q'){
			ll l,r;
			re2(l,r);
			l-=1;
			r-=1;
			ll ans=query(r)-query(l-1);
			pr(ans);
		}	
		else{
			ll ind,val;
			re2(ind,val);
			update(ind-1,val);
		}
	}
	return 0;
}
