#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll flag=0;
bool comp(pair<ll, ll> a, pair<ll, ll> b)
{	flag++;
	if((double)a.first/(double)a.second > (double)b.first/(double)b.second)
	return 1;
	else return 0;
}
void knapsack(vector < pair<ll,ll> > v, ll n, ll w)
{
	sort(v.begin(), v.end(), comp);
	double cnt=0;
	
	for(int i=0;i<n;i++)
	{
		flag++;
		if(w-v[i].second>=0)
		{
		cnt+=(v[i].first);
		//cout<<cnt<<endl;
		w-=v[i].second;
		if(w-v[i].second==0)
		break;
		}
		else{
			cnt+=((double)v[i].first/(double)v[i].second)*w;
			break;
		}
	}
	cout<<cnt<<endl;
}
int main()
{
	cout<<"enter weight\n";
	ll w; cin>>w;
	cout<<"enter no. of objects\n";
	ll n;
	cin>>n;
	
	vector< pair<ll,ll> >v(n);
	cout<<"enter profit and weights\n";
	for(ll i=0;i<n;i++)
	cin>>v[i].first>>v[i].second;
	
	knapsack(v,n,w); 
	cout<<flag<<endl;
}
