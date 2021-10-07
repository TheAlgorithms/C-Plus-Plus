#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void count_sort(vector<ll>&p,vector<ll>&c)
{
    ll n=p.size();
    vector<ll>cnt(n);
    for(auto x:c)
    cnt[x]++;
    vector<ll>pos(n),p_new(n);
    pos[0]=0;
    for(ll i=1;i<n;i++)
    pos[i]=pos[i-1]+cnt[i-1];
    for(auto x:p)
    {
        ll i=c[x];
        p_new[pos[i]]=x;
        pos[i]++;
    }
    p=p_new;
}

int main() {
	string s;
	cin>>s;
	s=s+"$";
	ll n=s.size();
	vector<ll> p(n),c(n);
	//k=0
	{
	    std::vector<pair<char,ll>>a(n) ;
	    for(ll i=0;i<n;i++)a[i]={s[i],i};
	    sort(a.begin(),a.end());
	    for(ll i=0;i<n;i++)p[i]=a[i].second;
	    c[p[0]]=0;
	    for(ll i=1;i<n;i++)
	    {
	        if(a[i].first==a[i-1].first)
	        c[p[i]]=c[p[i-1]];
	        else
	        c[p[i]]=c[p[i-1]]+1;
	    }
	}
	ll k=0;
	while((1<<k)<n)
	{
	    for(ll i=0;i<n;i++)
	    {
	        p[i]=(p[i]-(1<<k)+n)%n;
	    }
	    count_sort(p,c);
	    vector<ll>c_new(n);
	    c_new[p[0]]=0;
	    for(ll i=1;i<n;i++)
	    {
	        pair<ll,ll>prev={c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
	        pair<ll,ll>now={c[p[i]],c[(p[i]+(1<<k))%n]};
	        if(now==prev)
	        c_new[p[i]]=c_new[p[i-1]];
	        else
	        c_new[p[i]]=c_new[p[i-1]]+1;
	    }
	    c=c_new;
	    k++;
	}
	for(ll i=0;i<n;i++)
	cout<<p[i]<<' ';
	return 0;
}
